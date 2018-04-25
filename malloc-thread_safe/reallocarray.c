#include "malloc.h"


void * reallocarray(void *ptr, size_t nmemb, size_t size){
	//if (check_mul_overflow_size_t (nmemb, elem_size, &bytes)) //check mul overflow
	size_t bytes = nmemb * size;
	if(nmemb != bytes/size){
		errno = ENOMEM;
		return 0;
	}else{
		return realloc(ptr, bytes);
	}
}