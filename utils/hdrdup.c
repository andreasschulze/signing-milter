/*
 * signing-milter - utils/hdrdup.c
 * Copyright (C) 2010,2011  Andreas Schulze
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; only version 2 of the License is applicable.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Authors:
 *   Andreas Schulze <signing-milter at andreasschulze.de>
 *
 */

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
