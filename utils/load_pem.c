/*
 * signing-milter - utils/load_pem.c
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

#include "load_pem.h"

/* 
 * laed eine X509 Zertifikat aus der PEM-Datei "file"
 */
X509* load_pem_cert(const char* file) {

    BIO*  bio  = NULL;
    X509* cert = NULL;

    if ((bio=BIO_new(BIO_s_file())) == NULL)
        goto end;

    if (BIO_read_filename(bio,file) <= 0)
        goto end;

    if ((cert=PEM_read_bio_X509(bio, NULL, NULL, NULL)) == NULL)
        goto end;

end:
    if (bio != NULL)
        BIO_free(bio);

    return (cert);
}

EVP_PKEY* load_pem_key(const char* file, const char* pass) {

    BIO*      bio  = NULL;
    EVP_PKEY* pkey = NULL;

    if ((bio=BIO_new(BIO_s_file())) == NULL)
        goto end;

    if (BIO_read_filename(bio,file) <= 0)
        goto end;

    if ((pkey=PEM_read_bio_PrivateKey(bio, NULL, NULL, (void*) pass)) == NULL)
        goto end;

end:
    if (bio != NULL)
        BIO_free(bio);

    return(pkey);
}
