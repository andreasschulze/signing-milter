#include "logmsg.h"

void logmsg(int priority, const char *fmt, ...) {

    char    buf[LOG_MAXLOGBUF];
    va_list ap;

    if (priority <= opt_loglevel || priority <= LOG_WARNING) {

        /* Format message */
        va_start(ap, fmt);
        (void) vsnprintf(buf, sizeof(buf), fmt, ap);
        va_end(ap);

        /* Write message to syslog */
        syslog(priority, "%s", buf);

        /* Print message to terminal */
        if (opt_loglevel >= LOG_DEBUG || priority <= LOG_WARNING) {
            fprintf(stdout, "%s\n", buf);
        }
    }
}
