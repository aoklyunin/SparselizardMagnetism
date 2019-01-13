#pragma once

#include <sstream>
#include <ostream>
#include <tuple>
#include <vector>
#include <array>
#include <stdexcept>
#include <unistd.h>
#include <cstdio>

#include "user_time.h"
#include "formatting.h"


class Traces
{
private:
    bool _errs;
    bool _warns;
    bool _info;
    bool _dbgs;

    Traces();

public:
    ~Traces();

    static Traces *instance();
    void enable(bool warnings, bool errors, bool info, bool dbgs);

    inline bool warnings_enabled()
    { return _warns; }
    inline bool errors_enabled()
    { return _errs; }
    inline bool info_enabled()
    { return _info; }
    inline bool debugs_enabled()
    { return _dbgs; }

    void write_stdout(std::string const &s);
    void write_stderr(std::string const &s);
    void write_stddbg(std::string const &s);

    const std::string info_tag;
    const std::string debug_tag;
    const std::string error_tag;
    const std::string warning_tag;
};

template<class ... Args>
inline void info_msg(Args ... args)
{
    auto traces = Traces::instance();
    if (!traces->info_enabled())
        return;

    std::stringstream ss;
    //__print(ss, traces->info_tag, " at ", format_time(epoch_usec()), ": ", args..., "\n");
    __print(ss, traces->info_tag, args..., "\n");
    traces->write_stdout(ss.str());
}

template<class ... Args>
inline void warn_msg(Args ... args)
{
    auto traces = Traces::instance();
    if (!traces->warnings_enabled())
        return;

    std::stringstream ss;
   // __print(ss, traces->warning_tag, " at ", format_time(epoch_usec()), ": ", args..., "\n");
    __print(ss, traces->warning_tag, args..., "\n");
    traces->write_stderr(ss.str());
}

template<class ... Args>
inline void err_msg(Args ... args)
{
    auto traces = Traces::instance();
    if (!traces->errors_enabled())
        return;

    std::stringstream ss;
    //__print(ss, traces->error_tag, " at ", format_time(epoch_usec()), ": ", args..., "\n");
    __print(ss, traces->error_tag, args..., "\n");
    traces->write_stderr(ss.str());
}

template<class ... Args>
inline void dbg_msg(Args ... args)
{
    auto traces = Traces::instance();
    if (!traces->debugs_enabled())
        return;

    std::stringstream ss;
    //__print(ss, traces->debug_tag, " at ", format_time(epoch_usec()), ": ", args..., "\n");
    __print(ss, traces->debug_tag, args..., "\n");
    traces->write_stddbg(ss.str());
}

template<class ... Args>
inline void print_msg(Args ... args)
{
    auto traces = Traces::instance();
    std::stringstream ss;
    __print(ss, args...);
    traces->write_stdout(ss.str());
}
