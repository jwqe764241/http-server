#pragma once

#include <iostream>
#include "utils/utils.hpp"

_IMPLEMENT_SCOPE

namespace logger
{
	class Logger
	{
	private:
		std::ostream out_stream;

	public:
		Logger(std::ostream& out_stream)
			:out_stream(out_stream.rdbuf())
		{
		}

		template <typename T> friend Logger& operator<< (Logger& logger, const T& t)
		{
			logger.out_stream << t;
			return logger;
		}

		friend Logger& operator<<(Logger& logger, std::ostream& (*pf)(std::ostream&))
		{
			logger.out_stream << pf;
			return logger;
		}

		void print(std::string log)
		{
			out_stream << "info : " << log << "\n";
		}

		void warning(std::string log)
		{
			out_stream << "warn : " << log << "\n";
		}

		void error(std::string log)
		{
			out_stream << "err : " << log << "\n";
		}
	};
}

_IMPLEMENT_END