#include "malloc.h"


void * malloc(size_t size){
	size_t needSpace = size + sizeof(header_t);
//    fprintf(stderr, "====malloc %lu (%lu) space=====.\n", size,needSpace);
//	fprintf(stderr,".");

//	pthread_mutex_lock(&mutex);//lock start

	//use mmap when too big
	if(needSpace > SBRK_BLOCK_SZIE) {
        //fprintf(stderr, "%lu is big.\n",needSpace);
		//or use mmap
		// exit(-1);
		header_t* block = mmap(0, needSpace, PROT_READ | PROT_WRITE,
                   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		assert(block!=MAP_FAILED);

		block->next=NULL;
		block->prev=NULL;
		block->size=needSpace;
		block->isUsed = true; //should be used

		// fprintf(stderr, "mmap address: %p\n", (void *) block);
//		pthread_mutex_unlock(&mutex);//lock end
		return (char *)block + sizeof(header_t);
	} 


	//initial heap with first block
	if(!heap){
		if(!new_block()){
//			pthread_mutex_unlock(&mutex);//lock end
			return NULL; //TODO : set errno to ENOMEM 
		}
	}

	int level = get_level(needSpace);

	header_t *current, *next;

	//can find a x level block in freelist
	if(freelist[level]){
		current = freelist[level];
		next = current->next;

		current->isUsed = true;
		current->next = NULL;
		current->prev = NULL;

		if(next){
			//move up
			freelist[level] = next;
			next->prev = NULL;
		} else {
			freelist[level] = NULL;
		}

		// fprintf(stderr, "===malloc %lu in list===.\n", current->size);
		print_freelist();
		print_block(current);

//		pthread_mutex_unlock(&mutex);//lock end
		return (char *)current + sizeof(header_t);//return pointer of space start
	}

	//no match block, find min-avaiable block to split
	int freeblock_level = level + 1; //??? level?
	while(freeblock_level!=LEVEL+1 && freelist[freeblock_level]==NULL){
		// fprintf(stderr, "freeblock_level:%d\n",freeblock_level);
		// if(freeblock_level==LEVEL+1){ //cation
		// 	break;
		// }
		freeblock_level++;
	}

	//no free block availabe - request new block
	if(freeblock_level == LEVEL+1){ //???level?
		if(!new_block()){
//			pthread_mutex_unlock(&mutex);//lock end
			return NULL; //if fail return NULL;
		} 
		freeblock_level = LEVEL;
	}

	//with min avaialbe level - split the block 

	header_t *cur, *new;
	//keep split the min-available block until equal the level
	while(freeblock_level>level){
		cur = freelist[freeblock_level];
		cur->size /= 2;
		// if(cur->size ==0){
		// 	perror("=====size wrong===\n");
		// 	exit(1);
		// }
		//half the block become new
		new = (header_t *) ((char *)cur + cur->size);//covnert to char
		new = init_block(new,cur->size);
		// new->size = cur->size;

		if(freelist[freeblock_level]->next){
			//move up
			freelist[freeblock_level] = freelist[freeblock_level]->next;
			freelist[freeblock_level]->prev = NULL;
		} else{
			freelist[freeblock_level] = NULL;
		}
		
		//insert into lower level list
		freeblock_level --;
		cur->next = new;
		cur->prev = NULL;
		new->prev = cur;
		freelist[freeblock_level] = cur; //lower level should be empty
	}

	//get fit block now
	header_t *res_block = freelist[level];

	//pop it from list 
	if(freelist[level]->next){
		freelist[level] = freelist[level]->next;
		freelist[level]->prev = NULL;
	} else{
		freelist[level] = NULL;
	}

	//mark block
	res_block->prev = NULL;
	res_block->next = NULL;
	res_block->isUsed = true;

	print_str("===malloc===\n");
	print_freelist();
	print_block(res_block);


//	pthread_mutex_unlock(&mutex);//lock end
	return (char *)res_block + sizeof(header_t);

}	


// bool init_heap(){
// 	heap = sbrk(SBRK_BLOCK_SZIE);
// 	freelist[LEVEL] = (header_t *) heap;
// 	freelist[LEVEL]->isUsed = false;
// 	freelist[LEVEL]->size = SBRK_BLOCK_SZIE;
// 	freelist[LEVEL]->next = NULL;
// 	freelist[LEVEL]->prev = NULL;
	
// 	if(heap){
// 		return true;
// 	}else{
// 		return false;//init fail
// 	}
// }

//request a new full block use sbrk()
//return false if new block fail
bool new_block(){
    pthread_mutex_lock(&mutex_sbrk);
	void * ptr = sbrk(SBRK_BLOCK_SZIE);
	if(!ptr){
		errno = ENOMEM; //set error num
		perror("sbrk error");
	 	return false; //new block error
	}
    pthread_mutex_unlock(&mutex_sbrk);
	header_t * new_block = (header_t*) ptr;
	new_block = init_block(new_block,SBRK_BLOCK_SZIE);
	// print_block2(new_block);
	// fprintf(stderr, "address: %p\n", (void *) new_block);
	if(freelist[LEVEL]){
		// freelist[LEVEL]->next = new_block;
		header_t * b = freelist[LEVEL];
		while(b->next!=NULL){
			b = b->next;
		}
		b->next = new_block;
		b->next->prev = b;
		//???b->level = MAX_INDEX;
	}
	else{
		freelist[LEVEL] = new_block;
	}
	// fprintf(stderr, "header size: 0x%lx\n",sizeof(header_t));
	print_str("add block:\n");
	print_freelist();
	heap = ptr; //mark flag
	return true;
}


//get the min-fitted level for a needed space
int get_level(size_t needSpace){
	int level = 0;
	int space = MIN_BLOCK_SZIE;
	while(needSpace > space){
		space = space*2;
		level++;
	}
	return level;
}

header_t* init_block(void * ptr, size_t size){
	header_t * block =(header_t*) ptr;
	block->next = NULL;
	block->prev = NULL;
	block->isUsed = false;
	block->size = size; 
	return block;
}













