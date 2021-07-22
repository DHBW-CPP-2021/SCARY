#ifndef GAMEFIELDGRAPH_COUTLOGPOLICY_H
#define GAMEFIELDGRAPH_COUTLOGPOLICY_H

#include "LogPolicyInterface.h"

class CoutLogPolicy : public LogPolicyInterface
{
public:
	void open_ostream() const override;
	void close_ostream() const override;
	void write(std::string const& msg) const override;
};


#endif //GAMEFIELDGRAPH_COUTLOGPOLICY_H
