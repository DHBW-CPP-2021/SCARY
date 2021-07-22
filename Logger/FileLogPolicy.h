#ifndef GAMEFIELDGRAPH_FILELOGPOLICY_H
#define GAMEFIELDGRAPH_FILELOGPOLICY_H
#include "LogPolicyInterface.h"
#include <memory>
#include <fstream>

class FileLogPolicy : public LogPolicyInterface
{
public:
	FileLogPolicy();
	void open_ostream(std::string const& filename) const;
	void open_ostream() const override;
	void close_ostream() const override;
	void write(std::string const& msg) const override;
private:
	std::unique_ptr<std::ofstream> _out;
	static std::string const _default_logfile_name;
};


#endif //GAMEFIELDGRAPH_FILELOGPOLICY_H
