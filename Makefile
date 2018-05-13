GCC		= gcc -g -Wall

LOBJ		= linkedlist.o
LSRCS		= linkedlist.c

SOBJ		= skewheap.o
SSRCS		= skewheap.c

COBJ		= common.o
CSRCS		= common.c

default: common linkedo linked skewo skew

common: ${COBJ}
	${GCC} -c ${CSRCS} -o ${COBJ}

linkedo: ${LOBJ}
	${GCC} -c ${LSRCS} -o ${LOBJ}
 
linked: ${LOBJ}
	${GCC} ${COBJ} ${LOBJ} -o linked

skewo: ${SOBJ}
	${GCC} -c ${SSRCS} -o ${SOBJ}

skew: ${SOBJ}
	${GCC} ${COBJ} ${SOBJ} -o skew

clean:
	-rm -f *.o skew linked
