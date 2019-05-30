#include "http/http_request.hpp"

_IMPLEMENT_SCOPE

namespace http
{
	request::request()
	{
	}

	request::request(const std::string& request_text)
	try
	{
		parse(request_text);
	}
	catch(const parse_exception& e)
	{
		throw e;
	}

	request::~request()
	{
	}

	void request::parse(const std::string& request_text)
	{	
		if(request_text.empty())
		{
			throw parse_exception("HTTP request is empty. Check that request");
		}

		const int request_length = request_text.length();

		//Parse First line
		const int start_offset = request_text.find(character::LINE_CHANGE, 0);
		if(start_offset != std::string::npos)
		{
			std::stringstream start_stream(request_text.substr(0, start_offset));
			
			std::string method;
			std::string url;
			std::string version;

			start_stream >> method;
			start_stream >> url;
			start_stream >> version;

			this->method = method;

			int parameter_offset = url.find('?', 0);
			if (parameter_offset != std::string::npos)
			{
				this->url = url.substr(0, parameter_offset);

				std::string parameter_list = url.substr(parameter_offset + 1, url.length());
				std::replace(parameter_list.begin(), parameter_list.end(), '&', ' ');

				std::stringstream parameter_stream(parameter_list);
				std::string temp;
				while (parameter_stream >> temp)
				{
					int key_offset = temp.find('=', 0);
					if (key_offset != std::string::npos)
					{
						set_header(temp.substr(0, key_offset), temp.substr(key_offset + 1, temp.length()));
					}
					else
					{
						set_header(temp, "");
					}
				}
			}
			else
			{
				this->url = url;
			}

			this->version = version;
		}
		else
		{
			throw parse_exception("Can not resolve HTTP request, check that request");
		}

		//Parse Body
		const int body_offset = request_text.find(character::DIVIDE_BODY, start_offset + 1);
		if(body_offset != std::string::npos)
		{
			body = request_text.substr(body_offset + 2, request_length);
		}
		
		//Additional header string
		std::string data_string = request_text.substr(
			//No First line
			start_offset + 1,
			//Additional header length = Total_length - (Total_length - Start position of boddy - (-1 beacuse of two \n\n to seperate body)) - Start Position
			request_length - (request_length - body_offset + 1) - start_offset
		);

		//Extract key and value with token
		std::istringstream data_stream(data_string);
		for(std::string current_line; getline(data_stream, current_line);)
		{
			int token_offset = current_line.find(character::HEADER_TOKEN, 0);

			//Additional header's token is ':'
			//so if ':' is exist, this line has additional header data
			if(token_offset != std::string::npos)
			{
				utils::strings::delete_string(
					token_offset - 1, token_offset + 1,
					character::WHITESPACE, current_line
				);

				token_offset = current_line.find(character::HEADER_TOKEN, 0);

				set_header(current_line.substr(0, token_offset), current_line.substr(token_offset + 1, current_line.length()));
			}
		}
	}

	void request::set_header(const std::string& key, const std::string& value)
	{
		header[key] = value;
	}

	void request::set_header(const std::map<std::string, std::string>& header)
	{
		this->header = header;
	}

	std::string request::get_header(const std::string& key)
	{
		return header[key];
	}

	const std::map<std::string, std::string>& request::get_header()
	{
		return header;
	}
}

_IMPLEMENT_END