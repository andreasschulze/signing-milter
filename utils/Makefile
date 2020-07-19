all: utils.a

utils.a: append2buffer.o bio2file.o break_after_semicolon.o delete_marked_headers.o \
         dict_cdb.o dump_mailflags.o dump_pkcs7flags.o headerchain2signingbuffer.o get_num_semicolons.o \
         hdrdup.o is_already_signed.o is_multipart_mime.o linkedlist.o \
         load_pem.o logmsg.o lowercase.o node.o separate_header.o \
         validate_pem_permissions.o usage.o
	$(AR) rv utils.a $?

clean:
	rm -f *.o *.a

.c.o:
	@rm -f $@
	$(CC) $(CFLAGS) -c $*.c
