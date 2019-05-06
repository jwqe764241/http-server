#pragma once

#include <iostream>

#include "utils/utils.hpp"

_IMPLEMENT_SCOPE

namespace logger
{
	class logger
	{
	private:
		std::ostream out_stream;

	public:
		logger(std::ostream& out_stream)
			:out_stream(out_stream.rdbuf())
		{
		}

		template <typename T> friend logger& operator<< (logger& logger, const T& t)
		{
			logger.out_stream << t;
			return logger;
		}

		friend logger& operator<<(logger& logger, std::ostream& (*pf)(std::ostream&))
		{
			logger.out_stream << pf;
			return logger;
		}

		void info(std::string log)
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