#include "malloc.h"


void *calloc(size_t nmemb, size_t size) {
	print_str("===calloc===\n");
  size_t totalSize = nmemb * size;
  void *p = malloc(totalSize);
  if(p == NULL) {
  	return NULL;
  }
  pthread_mutex_lock(&mutex);
  memset(p, 0, totalSize);
  pthread_mutex_unlock(&mutex);
  return p;
}
