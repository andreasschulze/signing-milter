#include "lowercase.h"

/* postfix/src/utils/sys_defs.h */
#define _UCHAR_(c)   ((unsigned char)(c))
#define ISASCII(c)   isascii(_UCHAR_(c))
#define ISUPPER(c)   (ISASCII(c) && isupper((unsigned char)(c)))
#define TOLOWER(c)   (ISUPPER(c) ? tolower((unsigned char)(c)) : (c))

char *lowercase(char *string)
{
    char   *cp;
    int     ch;

    for (cp = string; (ch = *cp) != 0; cp++)
	if (ISUPPER(ch))
	    *cp = TOLOWER(ch);
    return (string);
}
