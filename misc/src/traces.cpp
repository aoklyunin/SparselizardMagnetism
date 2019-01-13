#include "../include/traces.h"


static const std::string __color_red = "\x1b[31m";

static const std::string __color_green = "\x1b[32m";

static const std::string __color_yellow = "\x1b[33m";

static const std::string __color_blue = "\x1b[34m";

static const std::string __color_magenta = "\x1b[35m";

static const std::string __color_cyan = "\x1b[36m";

static const std::string __color_gray = "\x1b[90m";

static const std::string __reset_color = "\x1b[0m";


// TODO: syslog

Traces::Traces()
    :
    _errs(true),
    _warns(true),
    _info(true),
    _dbgs(true),
    info_tag(__color_cyan + "[info]" + __reset_color),
    debug_tag(__color_gray + "[debug]" + __reset_color),
    error_tag(__color_red + "[error]" + __reset_color),
    warning_tag(__color_yellow + "[warn]" + __reset_color)
{
}

Traces::~Traces()
{
}

Traces *Traces::instance()
{
    static Traces traces;
    return &traces;
}

void Traces::enable(bool warnings, bool errors, bool info, bool dbgs)
{
    _warns = warnings;
    _errs = errors;
    _info = info;
    _dbgs = dbgs;
}

void Traces::write_stdout(std::string const &s)
{
    write(STDOUT_FILENO, s.data(), s.size());
}

void Traces::write_stderr(std::string const &s)
{
    write(STDERR_FILENO, s.data(), s.size());
}

void Traces::write_stddbg(std::string const &s)
{
    write(STDOUT_FILENO, s.data(), s.size());
}
