#include "validate_pem_permissions.h"

#include "logmsg.h"

/*
 * prüfen, ob die Datei existiert und ob es eine Datei ist
 * Datei darf nicht zugreifbar für "other" sein
 * Datei darf nicht schreib- oder ausführbar für die aktuelle UID sein
 * Datei muss lesbar für die aktuelle UID sein
 */

int validate_pem_permissions(const char* pemfilename) {

    struct stat st;

    if (stat(pemfilename, &st) < 0) {
        logmsg(LOG_ERR, "pemfilename %s: %m", pemfilename, strerror(errno));
        return 1;
    }
    if (!S_ISREG(st.st_mode)) {
        logmsg(LOG_ERR, "pemfilename %s is not a file", pemfilename);
        return 1;
    }
    if (S_IRWXO & st.st_mode) {
        logmsg(LOG_ERR, "pemfilename %s: file permissions too open: remove any access for other", pemfilename);
        return 1;
    }
    if (access(pemfilename, R_OK|W_OK) == 0) {
        logmsg(LOG_ERR, "pemfilename %s: file permissions too open: remove write access for myself", pemfilename);
        return 1;
    }
    if (access(pemfilename, R_OK) < 0 && errno == EACCES) {
        logmsg(LOG_ERR, "pemfilename %s: file permissions too strong: no read access", pemfilename);
        return 1;
    }

    return 0;
}
