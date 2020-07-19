#include "get_num_semicolons.h"

/*
 * Anzahl der Semikolons in einem String zählen
 *
 * Argument: Zeiger auf ein nullterminierter String
 * Rückgabe: Anzahl der Semikolons
 *           -1, wenn das Argument ein NULL-Zeiger ist
 * BUGS    : Integerüberlauf, wenn in Sting mehr als sizeof(int)/2 - 1
 *           Semikolons vorkommen
 */
int get_num_semicolons(char* string) {

    int num_semicolon = 0;
    char* p;

    if (string == NULL) {
        logmsg(LOG_ERR, "FATAL: get_num_semikolons failed: got empty string");
        return(-1);
    }

    p = string;
    while (*p) { /* bis \0 */
        if (*p == ';')
            num_semicolon++;
        p++;
    }
    logmsg(LOG_DEBUG, "get_num_semicolons: %i Semicolon in ->%s<-", num_semicolon, string);
    return(num_semicolon);
}
