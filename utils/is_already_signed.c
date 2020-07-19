#include "is_already_signed.h"

/* TODO: diese Funktion geht davon aus, dass in einer Mail die 
 *       Header immer aus kleinbuchstaben bestehen
 */
int is_already_signed(char* headerf, char* headerv) {

    if (strcasecmp(headerf, "content-type"))
        return (0);

    if (strstr(headerv, "multipart/signed") == NULL)
        return (0);

    if (strstr(headerv, "pkcs7-signature") == NULL)
        return (0);

    logmsg(LOG_DEBUG, "is_already_signed: header indicates message already signed");
    return (1);
}
