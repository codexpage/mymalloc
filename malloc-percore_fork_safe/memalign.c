#include "malloc.h"

void *memalign(size_t align, size_t len)
{
	void *mem;
	int ret;
	if ((ret = posix_memalign(&mem, align, len))) {
		errno = ret;
		return 0;
	}
	return mem;
}