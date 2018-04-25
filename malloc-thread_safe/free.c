#include "malloc.h"


void free(void * ptr){
	if (ptr == NULL) return; //this is important!
//	pthread_mutex_lock(&mutex);//lock start
	print_str("===free===\n");

	header_t * block = (header_t *)((char *)ptr - sizeof(header_t));
	print_block(block);

	if(block->size > SBRK_BLOCK_SZIE){
		print_str("unmap it\n");
		if(munmap(block,block->size)!=0){
			perror("unmap failed");
		}
		print_str("unlock it\n");
//		pthread_mutex_unlock(&mutex);
		return;
	}

	if(block->size == 0){
//		pthread_mutex_unlock(&mutex);
		return; //why 0???
	}


	block->isUsed =false;

	// print_str("===get_buddy===\n");
	header_t * buddy = get_buddy(block);
	//this buddy could be NULL when block is the biggest block

	//merge block
	merge(block, buddy);

	print_str("after freed:\n");
	print_freelist();
	

//	pthread_mutex_unlock(&mutex);//lock start
	return;
}

//get the buddy in the tree
header_t * get_buddy(header_t* ptr){
	//??? do I need this? yes
	if(ptr->size == SBRK_BLOCK_SZIE) return NULL;

	header_t * buddy = NULL;
	size_t buddy_addr = (size_t)ptr ^ ptr->size;
	header_t * other = (header_t *) buddy_addr;

	

	if(other && other->size == ptr->size){
		return other;
	}else{
		return NULL;
	}
}

//keep checking the buddy and merge into to bigger block
//insert into freelist when you can't merge
void merge(header_t* block, header_t *buddy){
	while(buddy && !buddy->isUsed){

		//handle the pointer of linkedlist
		if(buddy->next && buddy->prev){
			buddy->prev->next = buddy->next;
			buddy->next->prev = buddy->prev;
		}else if(buddy->next){
			buddy->next->prev = NULL;
			freelist[get_level(buddy->size)]=buddy->next;//??? do I need this? i think we need
		}else if(buddy->prev){
			buddy->prev->next = NULL;
		}else{
			freelist[get_level(buddy->size)] = NULL;
		}

		//get new block and new buddy
		if(buddy < block){
			block = buddy;
		}
		block->size *= 2; //size could be 0

		buddy = get_buddy(block);
	}

	//put the new block in the freelist
	int level = get_level(block->size);
	if(freelist[level]){
		freelist[level]->prev = block;
		block->next = freelist[level];
	}
	freelist[level] = block;

}
