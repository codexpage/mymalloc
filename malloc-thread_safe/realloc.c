#include "malloc.h"


void* realloc(void* ptr, size_t size){
	// pthread_mutex_lock(&mutex);//lock start don't add this lock
	print_str("===realloc===\n");
	void * new;

	//size is 0 - free mem
	if(size ==0){
		free(ptr);
		return NULL;
	}


	new = malloc(size);

	//malloc new mem
	if(ptr==NULL) return new;

	header_t * old = (header_t *)((char*) ptr - sizeof(header_t));
	if(old->size==0){ //for debug
		free(old);
		return new;
	}
	size_t old_size = old->size -sizeof(header_t);
	size_t min_size = (size < old_size? size : old_size);
	my_memcpy(new, ptr, min_size);//or my_memcpy

	free(ptr);
	// pthread_mutex_unlock(&mutex);//lock start don't add this lock

	return new;

}

void* my_memcpy(void* dest, const void* src, size_t num_bytes)
{
  char *d = (char *) dest;
  char *s = (char *) src;
  for (int i=0; i<num_bytes; i++) {
    d[i]=s[i];
  }
  return d;
}

