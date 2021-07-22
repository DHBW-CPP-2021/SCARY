#include "FileLogPolicy.h"

std::string const FileLogPolicy::_default_logfile_name = "standard.log";

void FileLogPolicy::open_ostream(std::string const& filename) const
{
	_out->open(filename.c_str(), std::ios_base::binary | std::ios_base::out);
	if (!_out->is_open())
	{
		throw std::runtime_error("FileLogPolicy: Unable to open output stream to file with filename " + filename);
	}
}

void FileLogPolicy::open_ostream() const
{
	open_ostream(_default_logfile_name);
}

void FileLogPolicy::close_ostream() const
{
	if (_out->is_open())
	{
		_out->close();
	}
}

void FileLogPolicy::write(std::string const& msg) const
{
	(*_out) << msg;
}

FileLogPolicy::FileLogPolicy() : _out(std::make_unique<std::ofstream>())
{}
