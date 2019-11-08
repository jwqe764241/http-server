#pragma once

#include <string>
#include <exception>

namespace cmd
{
	class option_not_found_exception : public std::exception
	{
	private:
		std::string msg;
		std::string option;

	public:
		option_not_found_exception(const std::string& message, const std::string& option)
			: msg(msg), option(option)
		{
		}

		const char* what() const noexcept
		{
			return msg.c_str();
		}

		const std::string& option() const noexcept
		{
			return option;
		}
	};
}