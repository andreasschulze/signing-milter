/*
 * signing-milter - ctxdata/setup.c
 * Copyright (C) 2010-2012  Andreas Schulze
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

#include "setup.h"

int ctxdata_setup(CTXDATA* ctxdata, const char* pemfilename) {

    char* chainfilename;
    char* p;

    assert(ctxdata != NULL);
    assert(pemfilename != NULL);

    if (validate_pem_permissions(pemfilename) != 0)
        return(1);

    if ((ctxdata->pemfilename = strdup(pemfilename)) == NULL) {
        logmsg(LOG_ERR, "error: ctxdata_setup: malloc for ctxdata.pemfilename failed: %m", strerror(errno));
        return(2);
    }

    if ((ctxdata->cert = load_pem_cert(ctxdata->pemfilename)) == NULL) {
        logmsg(LOG_ERR, "error: ctxdata_setup: loading certificate %s failed", ctxdata->pemfilename);
        return(3);
    }

    if ((ctxdata->key = load_pem_key(ctxdata->pemfilename, NULL)) == NULL) {
        logmsg(LOG_ERR, "error: ctxdata_setup: loading key %s failed", ctxdata->pemfilename);
        return(4);
    }

    ctxdata->pkcs7flags = PKCS7_DETACHED | PKCS7_NOOLDMIMETYPE | PKCS7_STREAM;

    ctxdata->buffer_len = MAXHEADERLEN;
    if ((ctxdata->buffer = malloc(ctxdata->buffer_len)) == NULL) {
        logmsg(LOG_ERR, "error: ctxdata_setup: allocation of %i byte (MAXHEADERLEN) for header failed", MAXHEADERLEN);
        return(5);
    }

    if ((chainfilename = strdup(pemfilename)) == NULL) {
        logmsg(LOG_ERR, "error: ctxdata_setup: malloc for chainfilename failed: %m", strerror(errno));
        return(6);
    }

    if ((p = strstr(chainfilename, "cert+key.pem")) == NULL) {
        logmsg(LOG_DEBUG, "info: certificate file not named /path/to/foo-cert+key.pem, including chaincerts disabled");
    } else {
        if ((realloc(chainfilename, strlen(pemfilename) - 3) == NULL)) {
            logmsg(LOG_ERR, "error: ctxdata_setup: realloc for ctxdata.chainfilename failed: %m", strerror(errno));
            return(7);
        }
	*p = '\0';
        strcat(p, "chain.pem");
        ctxdata->chain = load_pem_chain(chainfilename);
        logmsg(LOG_INFO, "info: %schaincerts loaded from %s", ctxdata->chain != NULL ? "" : "no ", chainfilename);
    }

    if (chainfilename)
       free(chainfilename);

    return(0);
}
