#include "separate_header.h"

char* separate_header(const char* line, char** headerf) {

    char* p = NULL;
    char* q = NULL;
    char* headerv = NULL;

    if (line == NULL || *line == '\0') {
        return (0);
    }

    if ((p = strchr(line, ':')) != NULL) {
        *p = '\0';
        *headerf = (char*) line;
    }

    /* die trennende \0 überspringen */
    p++;

    /* fuehrende Leerzeichen im headerv überspringen */
    while (*p == ' ')
      p++;

    if ((headerv = malloc(MAXHEADERLEN)) == NULL) {
        logmsg(LOG_ERR, "separate_header: failed to allocate %i byte (MAXHEADERLEN)", MAXHEADERLEN);
        return NULL;
    }

    q = headerv;
    /* abschliessendes \r\n oder \n abschneiden */
    while (*p != '\r' && *p != '\n') {
        *q = *p;
        p++;
        q++;
    }

    *q = '\0';

    return (headerv);
}
