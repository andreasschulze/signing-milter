#include "headerchain2signingbuffer.h"

int headerchain2signingbuffer(SMFICTX* ctx, CTXDATA* ctxdata) {

    NODE*          n;

    if ((ctxdata->mailflags & MF_TYPE_MIME) == 0) {

        /* einfachster Fall:
         * plain text, Body ist implizit 7bit Ascii
         * die Headerchain ist leer, da es keine MIME-Header gibt
         */
        ctxdata->pkcs7flags |= PKCS7_TEXT;
    }
    else {

        ctxdata->pkcs7flags |= PKCS7_BINARY;

        /*
         * irgendwiegeartete MIME-Mail
         * es MUSS Header geben
         */
        assert(ctxdata->headerchain != NULL);

        /*
         * wenn es MIME-Header gibt, diese in den inBIO schreiben
         * damit diese mitsigniert werden.
         * ( den MIME-Version: 1.0 jedoch nicht in den Body kopieren )
         */
        n = ctxdata->headerchain;
        while (n != NULL) {
            append2buffer(&(ctxdata->data2sign), &(ctxdata->data2sign_len), n->headerf, strlen(n->headerf));
            append2buffer(&(ctxdata->data2sign), &(ctxdata->data2sign_len), ": ", 2);
            append2buffer(&(ctxdata->data2sign), &(ctxdata->data2sign_len), n->headerv, strlen(n->headerv));
            append2buffer(&(ctxdata->data2sign), &(ctxdata->data2sign_len), "\r\n", 2);
            n = n->next;
        }
        /*
         * und eine weitere Leerzeile als Trenner zw. MIME-Header und Body
         */
        append2buffer(&(ctxdata->data2sign), &(ctxdata->data2sign_len), "\r\n", 2);
    }

    return(0);
}
