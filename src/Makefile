
CFLAGS	+= -std=c99

.c.o:   
	$(CC) -c $(CFLAGS) -o $@ $<


OBJ	= printf-extension-complex.o test-c99-complex.o

PROG	= test-c99-complex

$(PROG):	$(OBJ)

