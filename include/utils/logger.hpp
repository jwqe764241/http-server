#pragma once

#include <iostream>

namespace logger{

	class Logger
	{
	private:
		std::ostream mOutStream;
		
	public:
		Logger(std::ostream os);
		Logger(std::ostream && os);
		virtual ~Logger();
		
		void log();
	};
	
	enum class level
	{
		PRINT,
		WARNING,
		ERROR
	};

}