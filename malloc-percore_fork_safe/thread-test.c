/**
 * Test file for checking threads' requests for memory
 */

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

//#include "malloc.h"

void *func() {
	printf("Inside thread 1\n");
	void *p = malloc(50);
	printf("allocated 1\n");
	void *p1 = realloc(p, 100);
	printf("re-allocated 1\n");
	free(p);
	printf("-----Thread 1 Done----\n");
	return NULL;
}

void *func1() {
	printf("Inside thread 2\n");
	// void *pt = malloc(0x100001); //too big test
	void *p = malloc(50);
	fprintf(stderr, "p:%p\n",p);
	// printf("allocated 2\n");
	void *p1 = malloc(200);
	fprintf(stderr, "p1:%p\n",p1);
	void *p2 = malloc(200);
	fprintf(stderr, "p2:%p\n",p2);
	void *p3 = malloc(5000);
	fprintf(stderr, "p3:%p\n",p3);
	// printf("allocated 2-other\n");
	void *p4 = realloc(p2, 300);
	fprintf(stderr, "p4:%p\n",p4);

	void *p5 = malloc(0x100001);
	fprintf(stderr, "p5:%p\n",p5);
	// printf("re-allocated 2\n");
	free(p5);
	free(p4);
	printf("-----Thread 2 Done----\n");
	return NULL;
}

int main() {
	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, func,  NULL);
	pthread_create(&t2, NULL, func1, NULL);
	pthread_create(&t3, NULL, func,  NULL);
	//func1();

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	fprintf(stderr, "Multi-thread test succeeded.");
	//malloc_stats();
	return 0;
}