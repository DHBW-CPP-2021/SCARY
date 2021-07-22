#ifndef GAMEFIELDGRAPH_LOGGER_H
#define GAMEFIELDGRAPH_LOGGER_H
#include "LogLevel.h"
#include "LogPolicyInterface.h"
#include <iomanip>
#include <iostream>
#include <mutex>
#include <ostream>
#include <sstream>


namespace DHBW_LOG
{

    template <typename LogPolicy, LogLevel active_log_level = LogLevel::INFO> class Logger
    {
        static_assert(std::is_convertible<LogPolicy *, LogPolicyInterface *>::value,
                      "LogPolicy must implement LogPolicyInterface");

    public:
        template <typename... LogPolicyParams> Logger(LogPolicyParams... params);

        virtual ~Logger();

        template <LogLevel l, typename... Args> void log(Args... args) const;

        template <typename... Args> inline void error(Args... args) const
        {
            log<LogLevel::ERROR>(args...);
        }

        template <typename... Args> inline void warning(Args... args) const
        {
            log<LogLevel::WARNING>(args...);
        }

        template <typename... Args> inline void info(Args... args) const
        {
            log<LogLevel::INFO>(args...);
        }

        template <typename... Args> inline void debug(Args... args) const
        {
            log<LogLevel::DEBUG>(args...);
        }

        template <typename... Args> inline void trace(Args... args) const
        {
            log<LogLevel::TRACE>(args...);
        }

        // Log the return value of a callable. The callable is only called if and only if the log level is active.
        template <LogLevel l, typename Callable, typename... Args>
        inline void log_callable(Callable &callable, Args... args) const;

        template <typename Callable, typename... Args> inline void errorlog_callable(Callable &callable, Args... args) const
        {
            log_callable<LogLevel::ERROR, Callable>(callable, args...);
        }

        template <typename Callable, typename... Args>
        inline void warninglog_callable(Callable &callable, Args... args) const
        {
            log_callable<LogLevel::WARNING, Callable>(callable, args...);
        }

        template <typename Callable, typename... Args> inline void infolog_callable(Callable &callable, Args... args) const
        {
            log_callable<LogLevel::INFO, Callable>(callable, args...);
        }

        template <typename Callable, typename... Args> inline void debuglog_callable(Callable &callable, Args... args) const
        {
            log_callable<LogLevel::DEBUG, Callable>(callable, args...);
        }

        template <typename Callable, typename... Args> inline void tracelog_callable(Callable &callable, Args... args) const
        {
            log_callable<LogLevel::TRACE, Callable>(callable, args...);
        }

    private:
        mutable std::mutex _log_mutex;
        LogPolicy _log_policy;
        mutable std::stringstream _log_stream;

        template <typename First, typename... Rest> void build_stringstream(First first, Rest... rest) const;

        template <typename First> void build_stringstream(First first) const;
    };

    /////////////////////////////
    /// Implementation

    template <typename LogPolicy, LogLevel active_log_level>
    template <typename... LogPolicyParams>
    Logger<LogPolicy, active_log_level>::Logger(LogPolicyParams... params) : _log_mutex(), _log_policy(), _log_stream()
    {
        _log_policy.open_ostream(std::forward<LogPolicyParams>(params)...);
    }

    template <typename LogPolicy, LogLevel active_log_level> Logger<LogPolicy, active_log_level>::~Logger()
    {
        _log_policy.close_ostream();
    }

    template <typename LogPolicy, LogLevel active_log_level>
    template <LogLevel l, typename... Args>
    void Logger<LogPolicy, active_log_level>::log([[maybe_unused]] Args... args) const
    {
        // following commented lines should be obsolete as we are setting the CMake version to 17 in the main cmake
        //# if __cplusplus > 201402L
        if constexpr (static_cast<short>(l) <= static_cast<short>(active_log_level))
        //#else
        //        if (static_cast<short>(l) <= static_cast<short>(active_log_level))
        //#endif
        {
            _log_mutex.lock();

            // Add prefix
            _log_stream << toString<l>() << " ";
            // build content stream
            build_stringstream(args...);
            _log_stream << "\n";
            // log content
            _log_policy.write(_log_stream.str());
            // clear stringstream
            _log_stream.str(std::string());

            _log_mutex.unlock();
        }
    }

    template <typename LogPolicy, LogLevel active_log_level>
    template <typename First, typename... Rest>
    void Logger<LogPolicy, active_log_level>::build_stringstream(First first, Rest... rest) const
    {
        _log_stream << first << " ";
        build_stringstream(rest...);
    }

    template <typename LogPolicy, LogLevel active_log_level>
    template <typename First>
    void Logger<LogPolicy, active_log_level>::build_stringstream(First first) const
    {
        _log_stream << first;
    }

    template <typename LogPolicy, LogLevel active_log_level>
    template <LogLevel l, typename Callable, typename... Args>
    void Logger<LogPolicy, active_log_level>::log_callable(Callable &callable, Args... args) const
    {
        using LogLevelType = typename std::underlying_type<LogLevel>::type;
#if __cplusplus > 201402L
        if constexpr (static_cast<LogLevelType>(l) <= static_cast<LogLevelType>(active_log_level))
#else
        if (static_cast<LogLevelType>(l) <= static_cast<LogLevelType>(active_log_level))
#endif
        {
            log<l>(callable(args...));
        }
    }

} // namespace DHBW_LOG

#endif // GAMEFIELDGRAPH_LOGGER_H
