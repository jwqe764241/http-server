#pragma once

#include <iostream>
#include <fstream>

namespace logging
{
	enum LEVEL
	{
		INFO = 1,
		DEBUG = 2,
		WARN = 4,
		FATAL = 8,
		ALL = 15
	};

	class logger
	{
	protected:
		int level = 15;

	public:
		logger(int level)
			: level(level)
		{
		}

		virtual void write(std::string message) = 0;
		virtual void write(int level, std::string message) = 0;
	};

	class console_logger : public logger
	{
	private:
		std::ostream& stream = std::cout;

	public:
		console_logger(int level)
			: logger(level)
		{
		}

		virtual void write(std::string message)
		{
			stream << message << std::endl;
		}

		virtual void write(int level, std::string message)
		{
			if ((this->level & level) != 0)
			{
				if (level == LEVEL::DEBUG)
				{
					#ifndef NDEBUG
					write(message);
					#endif
				}
				else
				{
					write(message);
				}
			}
		}
	};

	class file_logger : public logger
	{
	private:
		std::ofstream stream;

	public:
		file_logger(int level, std::string path)
			: logger(level), stream(path, std::ios::app)
		{
		}

		~file_logger()
		{
			stream.close();
		}

		virtual void write(std::string message)
		{
			stream << message << std::endl;
		}

		virtual void write(int level, std::string message)
		{
			if ((this->level & level) != 0)
			{
				if (level == LEVEL::DEBUG)
				{
					#ifndef NDEBUG
					write(message);
					#endif
				}
				else
				{
					write(message);
				}
			}
		}
	};
}