all: qmem.a output

output: qmem.a qmem.h mainTest.o
	gcc -Wall mainTest.o qmem.a -o testOut
qmem.a: qmem_alloc.o qmem_allocz.o qmem_allocv.o qmem_free.o qmem_cmp.o qmem_cpy.o qmem_scrub.o qmem_scrubv.o qmem_size.o qmem_stats.o
	ar cr qmem.a qmem_alloc.o qmem_allocz.o qmem_allocv.o qmem_free.o qmem_cmp.o qmem_cpy.o qmem_scrub.o qmem_scrubv.o qmem_size.o qmem_stats.o
mainTest.o: mainTest.c qmem.h
	gcc -Wall -c mainTest.c
qmem_alloc.o: qmem_alloc.c qmem.h
	gcc -Wall -c qmem_alloc.c
qmem_allocz.o: qmem_allocz.c qmem.h
	gcc -Wall -c qmem_allocz.c
qmem_allocv.o: qmem_allocv.c qmem.h
	gcc -Wall -c qmem_allocv.c
qmem_free.o: qmem_free.c qmem.h
	gcc -Wall -c qmem_free.c
qmem_cmp.o: qmem_cmp.c qmem.h
	gcc -Wall -c qmem_cmp.c
qmem_cpy.o: qmem_cpy.c qmem.h
	gcc -Wall -c qmem_cpy.c
qmem_scrub.o: qmem_scrub.c qmem.h
	gcc -Wall -c qmem_scrub.c
qmem_scrubv.o: qmem_scrubv.c qmem.h
	gcc -Wall -c qmem_scrubv.c
qmem_size.o: qmem_size.c qmem.h
	gcc -Wall -c qmem_size.c
qmem_stats.o: qmem_stats.c qmem.h
	gcc -Wall -c qmem_stats.c

run:
	./testOut
