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
