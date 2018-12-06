

CFLAGS	+= -std=c89

.c.o:	
	$(CC) -c $(CFLAGS) -o $@ $<

OBJ	= printf-extension-c89.o test-c89-complex.o

PROG	= test-c89-complex

$(PROG):	$(OBJ)

