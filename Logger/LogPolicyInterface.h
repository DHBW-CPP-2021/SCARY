#ifndef GAMEFIELDGRAPH_LOGGINGPOLICY_H
#define GAMEFIELDGRAPH_LOGGINGPOLICY_H
#include <string>

class LogPolicyInterface
{
public:
	virtual void open_ostream() const = 0;
	virtual void close_ostream() const = 0;
	virtual void write(std::string const& msg) const = 0;
};

#endif //GAMEFIELDGRAPH_LOGGINGPOLICY_H
