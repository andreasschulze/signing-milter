#include "bio2file.h"

int bio2file(BIO *b, const char* prefix, const char* queueid) {

    BIO*     biofile;
    BUF_MEM* pp;
    char*    bio_filename;
    char*    p;

    assert(prefix != NULL);
    assert(queueid != NULL);

    if ((bio_filename = malloc(strlen(opt_keepdir) + strlen(prefix) + strlen(queueid + 1) + 100)) == NULL) {
        logmsg(LOG_ERR, "bio2file: malloc for bio_filename failed: %m", strerror(errno));
        return(1);
    }

    sprintf(bio_filename, "%s/%s-%s", opt_keepdir, prefix, queueid);

    BIO_get_mem_ptr(b, &pp);
    p = pp->data;

    biofile = BIO_new_file(bio_filename, "w");
    if (!biofile) {
        logmsg(LOG_ERR, "bio2file: BIO_new_file failed");
        BIO_free_all(biofile);
        BUF_MEM_free(pp);
        return(2);
    }

    BIO_puts(biofile, pp->data);

    BIO_free(biofile);
    free(bio_filename);

    return(0);
}
