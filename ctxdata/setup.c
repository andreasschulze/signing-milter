#include "setup.h"

int ctxdata_setup(CTXDATA* ctxdata, const char* pemfilename) {

    assert(ctxdata != NULL);
    assert(pemfilename != NULL);

    if (validate_pem_permissions(pemfilename) != 0 )
        return(1);

    if ((ctxdata->pemfilename = strdup(pemfilename)) == NULL) {
        logmsg(LOG_ERR, "error: callback_envfrom: malloc for ctxdata.pemfilename failed: %m", strerror(errno));
        return(2);
    }

    if ((ctxdata->cert = load_pem_cert(ctxdata->pemfilename)) == NULL) {
        logmsg(LOG_ERR, "error: callback_envfrom: loading certificate %s failed", ctxdata->pemfilename);
        return(3);
    }

    if ((ctxdata->key = load_pem_key(ctxdata->pemfilename, NULL)) == NULL) {
        logmsg(LOG_ERR, "error: callback_envfrom: loading key %s failed", ctxdata->pemfilename);
        return(4);
    }

    ctxdata->pkcs7flags = PKCS7_DETACHED | PKCS7_NOOLDMIMETYPE | PKCS7_STREAM;

    ctxdata->buffer_len = MAXHEADERLEN;
    if ((ctxdata->buffer = malloc(ctxdata->buffer_len)) == NULL) {
        logmsg(LOG_ERR, "error: callback_envfrom: allocation of %i byte (MAXHEADERLEN) for header failed", MAXHEADERLEN);
        return(5);
    }

    return(0);
}
