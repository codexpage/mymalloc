#include "malloc.h"


/* Print the freelist, for debugging */
void print_freelist() {
//   int size = 4;
//   for (int i=0; i<LEVEL+1; i++) {
//   	int length = (void *) freelist[i] - (void *) freelist[0];
//     fprintf(stderr, "[%d] -> %d: %p %d\n", i, size, (void *) freelist[i], length);
//     size *= 2;
//   }
}

/* Print the metadata for the block of memory, for debugging */
void print_block(header_t *block) {
//   fprintf(stderr, "Printing block data\n");
//   fprintf(stderr, "address: %p\n", (void *) block);
//   fprintf(stderr, "in use: %d\n", block->isUsed);
//   fprintf(stderr, "size: %ld\n", block->size);
//   fprintf(stderr, "next: %p\n", (void *) block->next);
//   fprintf(stderr, "prev: %p\n", (void *) block->prev);
//   fprintf(stderr, "\n");
}

void print_block2(header_t *block) {
  // fprintf(stderr, "Printing block data\n");
  // fprintf(stderr, "address: %p\n", (void *) block);
  // fprintf(stderr, "in use: %d\n", block->isUsed);
  // fprintf(stderr, "size: %ld\n", block->size);
  // fprintf(stderr, "next: %p\n", (void *) block->next);
  // fprintf(stderr, "prev: %p\n", (void *) block->prev);
  // fprintf(stderr, "\n");
}


void print_str(char * str){
//	 fprintf(stderr, str);
}
