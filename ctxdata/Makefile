all: ctxdata.a

ctxdata.a: cleanup.o create.o free.o setup.o
	$(AR) rv ctxdata.a $?

clean:
	rm -f *.o *.a

.c.o:
	@rm -f $@
	$(CC) $(CFLAGS) -c $*.c
