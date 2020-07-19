#ifndef _SIGNING_MILTER_H_INCLUDED_
#define _SIGNING_MILTER_H_INCLUDED_

#include <cdb.h>
#include <openssl/x509.h>
#include "config.h"

#define STR_PROGNAME    "signing-milter"
#ifdef NDEBUG
#define STR_PROGVERSION "20110301"
#else
#define STR_PROGVERSION "20110301-debug"
#endif

/*
 * Name of the header added by -x cmdline switch
 */
#define HEADERNAME_XHEADER "X-Signed-by"

/*
 * Name of the header used as signeraddress
 * if opt_signerfromheader is enabled 
 */
#define HEADERNAME_SIGNER "X-Signer"

/* buffer for caching one header */
#define MAXHEADERLEN 4096

/* ======= CDB ======================= */
/* übliche Länge des Speichers der für dict.buffer allokiert wird */
#define DICT_BUFFER_LEN 512

typedef struct DICT {
    char*          name;
    int            flags;
    int            stat_fd;
    time_t         mtime;
    struct cdb     cdb;
    char*          buffer;
    char*          result;
    unsigned       result_len;
} DICT;

#define DICT_FLAG_TRY0NULL      (1<<2)  /* do not append 0 to key/value */
#define DICT_FLAG_TRY1NULL      (1<<3)  /* append 0 to key/value */

/* ======= NODES ======================= */
/*
 * - Zeiger auf den naechsten Knoten
 * - Type des Knoten
 */
struct node_t {
    struct node_t* next;
    char*          headerf;
    char*          headerv;
};
#define NODE struct node_t

/* ======= CALLBACK ================== */
struct ctxdata {
    char*          pemfilename;
    NODE*          headerchain;
    unsigned char* data2sign;
    size_t         data2sign_len;
    X509*          cert;
    EVP_PKEY*      key;
    BIO*           inbio;
    BIO*           outbio;
    PKCS7*         pkcs7;
    int            pkcs7flags;
    int            mailflags;
    char*          buffer;
    size_t         buffer_len;
    char*          queueid;
    int            first_bodychunk_seen;
};
#define CTXDATA struct ctxdata

/* Werte fuer ctxdata.mailflags */
#define MF_TYPE_MIME                   (1<<0)
#define MF_TYPE_MULTIPART              (1<<1)
#define MF_SIGNMODE_OPAQUE             (1<<2)
#define MF_SIGNER_FROM_HEADER          (1<<3)

/*
 * globale Variablen
 * koennen durch Kommandozeienparameter
 * veraendert werden
 */
extern char* opt_clientgroup;
extern int   opt_loglevel;
extern char* opt_group;
extern char* opt_keepdir;
extern char* opt_signingtable;
extern char* opt_modetable;
extern char* opt_miltersocket;
extern int   opt_timeout;
extern char* opt_user;
extern int   opt_addxheader;
extern int   opt_breakheader;
extern int   opt_signerfromheader;

extern struct DICT dict_signingtable;
extern struct DICT dict_modetable;

#endif
