CC=gcc
CFLAGS=-g -O0 -fPIC -std=gnu99
PRE=LD_PRELOAD=./libmalloc.so
#-Werror -Wall

TESTS=t-test1 test1 thread-test simple-test te test
HEADERS= malloc.h

all:	${TESTS} libmalloc.so

clean:
	rm -rf *.o *.so ${TESTS}

libmalloc.so: malloc.o free.o calloc.o realloc.o util.o reallocarray.o
	$(CC) $(CFLAGS) -shared -Wl,--unresolved-symbols=ignore-all $^ -o $@

lib: libmalloc.so

%: %.c
	$(CC) $(CFLAGS) $< -o $@ -lpthread

# For every XYZ.c file, generate XYZ.o.
%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) $< -c -o $@


check1: test2

check: test3 

dist: clean
	dir=`basename $$PWD`; cd ..; tar cvf $$dir.tar ./$$dir; gzip $$dir.tar


#simple test
test1: libmalloc.so te
	LD_PRELOAD=./libmalloc.so ./te

#multi-thread
test2: libmalloc.so t-test1
	LD_PRELOAD=./libmalloc.so ./t-test1

#simple-thread-test
test3: libmalloc.so thread-test
	LD_PRELOAD=./libmalloc.so ./thread-test

test4: libmalloc.so simple-test
	$(PRE) ./simple-test

te: test.c
	$(CC) $(CFLAGS) ./test.c -o te

te2: t-test1.c
	$(CC) $(CFLAGS) ./t-test.c -o t-test1

thread-test: thread-test.c
	$(CC) $(CFLAGS) -pthread ./thread-test.c -o thread-test

# simple-test: simple-test.c
# 	$(CC) $(CFLAGS) -pthread $< -o $@

