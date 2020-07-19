#include "delete_marked_headers.h"

int delete_marked_headers(SMFICTX* ctx, CTXDATA* ctxdata) {

    if ((ctxdata->mailflags & MF_TYPE_MIME) == 0) {

        /* einfachster Fall:
         * plain text, Body ist implizit 7bit Ascii
         * die Headerchain ist leer, da es keine MIME-Header gibt
         */
        assert(ctxdata->headerchain == NULL);
    }
    else {

        NODE* n;

        /*
         * irgendwelche MIME-Mail es MUSS Header geben
         */
        assert(ctxdata->headerchain != NULL);

        n = ctxdata->headerchain;
        while (n != NULL) {
            if (smfi_chgheader(ctx, n->headerf, 1, NULL) != MI_SUCCESS) {
                logmsg(LOG_ERR, "%s: error: delete_marked_headers: delete_header %s failed", ctxdata->queueid, n->headerf);
                return (1); /* wird in der aufrufenden Funktion zu SMFIS_TEMPFAIL */
            }
            n = n->next;
        }
    }

    return(0);
}

