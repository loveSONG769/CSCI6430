OSHCC = oshcc
CFLAGS = 
all: openSh

openShmem: openSh.c
	${OSHCC} ${CFLAGS} -o openSh openSh.c

clean:
	rm openSh
	rm *~
