#include "malloc.h"

//per thread
//__thread void * heap;
//__thread header_t ** freelist; //pointer of the start of freelist


__thread int arena_index=-1;
__thread arena_t* arena=NULL;
//global variable
arena_t arena_list[40];
size_t arena_num=0;
size_t  thread_count=0;
pthread_mutex_t mutexes[40];
pthread_mutex_t mutex_arenalist = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_sbrk = PTHREAD_MUTEX_INITIALIZER;



//void init_arena(){}
//void end_arena(){}

void init_arena(){

    if(arena==NULL){ //only the first time for a thread call malloc

        //init the area_list
        pthread_mutex_lock(&mutex_arenalist);
        if(arena_num==0){
            int num_cpus = sysconf( _SC_NPROCESSORS_ONLN );
            arena_num = num_cpus;
            //all mutex init
            for(int i=0;i<num_cpus;i++){
                pthread_mutex_init(&mutexes[i], NULL);
            }
            pthread_atfork(prepare, afterfork, afterfork);//register atfork

        }
        arena_index = thread_count % arena_num;
//        fprintf(stderr,"%d %d\n",thread_count,arena_index);
        thread_count++;
        pthread_mutex_unlock(&mutex_arenalist);

    }

    pthread_mutex_lock(&mutexes[arena_index]);
//    fprintf(stderr,"arena lock\n");
    arena = &arena_list[arena_index];
//    fprintf(stderr,"%d %d get\n",thread_count-1,arena_index);

//    freelist= arena->freelist; //(never change)
//    heap = arena->heap;




}

void end_arena(){
//    pthread_mutex_lock(&mutex_arena); //do I need this?
//    arena->isUsed=false;
//    pthread_mutex_unlock(&mutex_arena);
//    sem_post(&sem);
    pthread_mutex_unlock(&mutexes[arena_index]);
//    fprintf(stderr,"arena unlock\n");
}


void malloc_stats() {

    int totalsize =0;
    int i=0;
    for(i=0;i<arena_num;i++){
        totalsize+= arena_list[i].stat.totalsize;
    }
    printf("\t----------- Malloc stats -----------\n");

    printf("\tTotal Size : %d\n", totalsize);
    printf("\tNumber of Arenas: %d\n", arena_num);

    for(i=0;i<arena_num;i++){
        printf("\t===Arena %d===\n",i);
        printf("\tAllocated Blocks: %lld\n",arena_list[i].stat.alloctimes);
        printf("\tFreed Blocks: %lld\n",arena_list[i].stat.freetimes);
        printf("\tmmap Times: %lld\n",arena_list[i].stat.mmaptimes);
//        printf("\tmmap total size: %d\n",arena_list[i].stat.mmapsize);
        printf("\tAllocated size: %lld\n",arena_list[i].stat.usedsize);
//        printf("\tFree size: %lld\n",arena_list[i].stat.totalsize - arena_list[i].stat.usedsize);
    }
    printf("\t------------------------------------\n");

}


void prepare()
{
    pthread_mutex_lock(&mutex_sbrk);
    pthread_mutex_lock(&mutex_arenalist);
    int i =0;
    for(i=0;i<arena_num;i++){
        pthread_mutex_lock(&mutexes[i]);
    }
}

void afterfork()
{
    int i =0;
    for(i=arena_num-1;i>=0;i--){
        pthread_mutex_unlock(&mutexes[i]);
    }
    pthread_mutex_unlock(&mutex_arenalist);
    pthread_mutex_unlock(&mutex_sbrk);

}
