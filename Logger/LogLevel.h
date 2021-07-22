#ifndef GAMEFIELDGRAPH_LOGLEVEL_H
#define GAMEFIELDGRAPH_LOGLEVEL_H

#include <array>
#include <string>

enum class LogLevel : short
{
	ERROR,
	WARNING,
	INFO,
	DEBUG,
	TRACE
};
// Kind of const-time lookup table for log level names
static std::array<std::string, 5> logLevelStrings({ "ERROR","WARNING","INFO","DEBUG", "TRACE" });
// Utility methods
template <LogLevel l>
std::string const& toString();
std::string const& toString(LogLevel l);

////////////////////////////
/// Implementation

template <LogLevel l>
std::string const& toString()
{
	return std::get<static_cast<size_t>(l)>(logLevelStrings);
}


#endif //GAMEFIELDGRAPH_LOGLEVEL_H
