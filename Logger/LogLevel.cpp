#include "LogLevel.h"

std::string const& toString(LogLevel l)
{
	static const std::string unknown = "UNKNOWN LOG LEVEL";
	switch (l)
	{
	case LogLevel::ERROR: return toString<LogLevel::ERROR>();
	case LogLevel::WARNING: return toString<LogLevel::WARNING>();
	case LogLevel::INFO: return toString<LogLevel::INFO>();
	case LogLevel::DEBUG: return toString<LogLevel::DEBUG>();
	case LogLevel::TRACE: return toString<LogLevel::TRACE>();
	default: return unknown;
	}
}