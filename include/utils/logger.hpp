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
	};

	enum class level
	{
		PRINT,
		WARNING,
		ERROR
	};
}

_IMPLEMENT_END