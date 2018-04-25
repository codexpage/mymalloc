#include "malloc.h"


/* Print the freelist, for debugging */
void print_freelist() {
#ifdef PINFO
   int size = 16;
   for (int i=0; i<LEVEL+1; i++) {
//   	int length = (void *) arena->freelist[i] - (void *) arena->freelist[0];
       size_t next = 0x0;
       size_t next2 = 0x0;
       if (arena->freelist[i] && arena->freelist[i]->next){
           next = arena->freelist[i]->next;
           if (arena->freelist[i]->next->next){
               next2=arena->freelist[i]->next->next;
           }
       }
     fprintf(stderr, "[%d] -> %d: %p %p %p\n", i, size, (void *) arena->freelist[i],next,next2);
     size *= 2;
   }
#endif PINFO
}

/* Print the metadata for the block of memory, for debugging */
void print_block(header_t *block) {
#ifdef PINFO
   fprintf(stderr, "Printing block data\n");
   fprintf(stderr, "address: %p\n", (void *) block);
   fprintf(stderr, "in use: %d\n", block->isUsed);
   fprintf(stderr, "size: %ld\n", block->size);
   fprintf(stderr, "next: %p\n", (void *) block->next);
   fprintf(stderr, "prev: %p\n", (void *) block->prev);
   fprintf(stderr, "\n");
#endif PINFO
}

void print_block2(header_t *block) {
#ifdef PINFO
//   fprintf(stderr, "Printing block data\n");
//   fprintf(stderr, "address: %p\n", (void *) block);
//   fprintf(stderr, "in use: %d\n", block->isUsed);
//   fprintf(stderr, "size: %ld\n", block->size);
//   fprintf(stderr, "next: %p\n", (void *) block->next);
//   fprintf(stderr, "prev: %p\n", (void *) block->prev);
//   fprintf(stderr, "\n");
#endif PINFO
}


void print_str(char * str){
#ifdef PINFO
	 fprintf(stderr, str);
#endif PINFO
}
