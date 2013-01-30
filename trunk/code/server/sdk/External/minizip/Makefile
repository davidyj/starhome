# this make is gnu styled,use gmake to make
#

CC=cc
CFLAGS=-O -I ../..

LIB_NAMEE = ../../../lib/libzip.so
OBJS = zip.o unzip.o ioapi.o

.c.o:
	$(CC) -c $(CFLAGS) $*.c

all: $(OBJS)
	 cc -lz -fPIC -shared *.o -o $(LIB_NAMEE)


minizip.o: minizip.c
	$(CC)  $(CFLAGS) -c $< -o $@
zip.o: zip.c
	$(CC)  $(CFLAGS) -c $< -o $@
miniunz.o: miniunz.c
	$(CC)  $(CFLAGS) -c $< -o $@
unzip.o: unzip.c
	$(CC)  $(CFLAGS) -c $< -o $@
ioapi.o: ioapi.c
	$(CC)  $(CFLAGS) -c $< -o $@

test:	miniunz minizip
	./minizip test readme.txt
	./miniunz -l test.zip
	mv readme.txt readme.old
	./miniunz test.zip

clean:
	/bin/rm -f *.o *~ minizip miniunz
