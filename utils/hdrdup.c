#include "hdrdup.h"

/* Idee: postfix:src/global/lex_822.h */
#define IS_CR_LF(ch)            (ch == '\r' || ch == '\n')
#define IS_NOT_SPACE_TAB(ch)    (ch != ' '  && ch != '\t')

/*
 * hdrdup analog strdup
 * string ist headerf oder headerv
 *
 * Ersetzt \n \r\n und darauffolgende SPACES oder TABS durch genau ein SPACE
 */
char* hdrdup(const char* string) {

    char*  dup;
    char   c;
    char*  p;
    size_t string_len;
    int    skip = 0;

    assert(string != NULL);

    string_len = strlen(string) + 1; /* fuer die abschliessende \0 */
    if ((dup = malloc(string_len)) == NULL)
        return NULL;

    p = dup;
    while ((c = *string) != '\0') {
        string++;

        /*
         * Zeilenumbruch ueberspringen und merken.
         */
        if (IS_CR_LF(c)) {
            skip = 1;
            continue;
        }
        /* erst wenn nach einem Zeilenumbruch kein SPACE oder TAB kommt,
         * ist der Zeilenumbruch beendet
         * -> also ein Leerzeichen einfuegen
         */
        if (skip && IS_NOT_SPACE_TAB(c)) {
            *p = ' ';
            p++;
            skip = 0;
        }

        if (skip)
            continue;

        *p = c;
        p++;
    }
    *p = '\0'; /* String abschliessen */

    return (dup);
}
