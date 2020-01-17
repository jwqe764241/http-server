#pragma once

#include <iostream>
#include <fstream>

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
	int level;
	std::shared_ptr<logger> next;
	std::ostream& stream;

protected:
	virtual void write(std::string message) = 0;

public:
	logger(int level, std::ostream& stream)
		: level(level), stream(stream)
	{
	}

	logger* set_next(std::shared_ptr<logger> next)
	{
		logger* last_logger = this;

		while (last_logger->next != nullptr)
		{
			last_logger = last_logger->next.get();
		}

		last_logger->next = next;

		return this;
	}

	void log(int level, std::string message)
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

		if (next != nullptr)
		{
			this->next->log(level, message);
		}
	}
};

class console_logger : public logger
{
private:
	std::string tag;

private:
	virtual void write(std::string message)
	{
		stream << tag << " " << message;
	}

public:
	console_logger(int level, std::string tag)
		: logger(level, std::cout), tag(tag)
	{
	}

	console_logger(int level)
		: logger(level, std::cout)
	{
	}
};

class file_logger : public logger
{
private:
	std::string tag;

private:
	virtual void write(std::string message)
	{
		stream << tag << " " << message;
	}

public:
	file_logger(int level, std::string tag, std::ofstream stream)
		: logger(level, stream), tag(tag)
	{
	}

	file_logger(int level, std::ofstream stream)
		: logger(level, stream)
	{
	}
};