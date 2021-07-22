#ifndef GAMEFIELDGRAPH_LOG_H
#define GAMEFIELDGRAPH_LOG_H

#include "CoutLogPolicy.h"
#include "FileLogPolicy.h"
#include "Logger.h"


namespace DHBW_LOG
{

    template <LogLevel active_log_level> using FileLogger = Logger<FileLogPolicy, active_log_level>;

    template <LogLevel active_log_level = LogLevel::INFO> using CoutLogger = Logger<CoutLogPolicy, active_log_level>;

} // namespace DHBW_LOG

#endif // GAMEFIELDGRAPH_LOG_H
