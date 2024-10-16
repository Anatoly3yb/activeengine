#ifndef SYSLOG_LOGGER_H
#define SYSLOG_LOGGER_H

#ifdef UNIX_ENABLED

#include "core/io/logger.h"

class SyslogLogger : public Logger {
public:
	virtual void logv(const char *p_format, va_list p_list, bool p_err) _PRINTF_FORMAT_ATTRIBUTE_2_0;
	virtual void print_error(const char *p_function, const char *p_file, int p_line, const char *p_code, const char *p_rationale, ErrorType p_type);

	virtual ~SyslogLogger();
};

#endif

#endif // SYSLOG_LOGGER_H
