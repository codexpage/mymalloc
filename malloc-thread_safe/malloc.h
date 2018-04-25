#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

#include <stdio.h>
//#include <string.h>
#include <unistd.h>
//#include <assert.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <sys/mman.h>
#include <assert.h>

//1M
#define SBRK_BLOCK_SZIE 0x1000
// #define SBRK_BLOCK_SZIE 0
//1 page = 4096
#define MIN_BLOCK_SZIE 0x10

//from level 0 to LEVEL
#define LEVEL 8


typedef struct header
{
	bool isUsed;
	size_t size;
	struct header* next;
	struct header* prev;
} header_t;




//global variables

static __thread void * heap;

static __thread header_t * freelist[LEVEL+1];
//level size(Byte)
//0		4K		16 0x10
//1		8K		32
//2		16K		64
//3		32K		128
//4		64K		256
//5		128K	512
//6 	256K	1024
//7 	512K	2048
//8		1M		4096 0x1000

static __thread pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_sbrk = PTHREAD_MUTEX_INITIALIZER;




void* malloc(size_t size);

void free(void * ptr);

void * calloc(size_t nmemb, size_t size);

void * realloc(void* ptr, size_t size);

void * reallocarray(void *ptr, size_t nmemb, size_t size);

int posix_memalign(void **memptr, size_t alignment, size_t size);

void *memalign(size_t alignment, size_t size);


// bool init_heap();
bool new_block();
int get_level(size_t needSpace);
header_t * get_buddy(header_t* ptr);
void merge(header_t* block, header_t *buddy);
void print_freelist();
void print_block(header_t *block);
void* my_memcpy(void* dest, const void* src, size_t num_bytes);
void print_str(char * str);
header_t* init_block(void * ptr, size_t size);
void print_block2(header_t *block);





#endif 
