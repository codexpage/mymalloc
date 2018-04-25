#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* another()
{
  fprintf(stderr,"subthread\n");
//  pthread_mutex_lock(&mutex);
  while(1){
    void* p = malloc(1);
    free(p);
    fprintf(stderr,"run\n");
    sleep(1);
  }
//  pthread_mutex_unlock(&mutex);
}


int main(int argc, char **argv)
{
  fprintf(stderr,"start\n");
  pthread_t id;
  pthread_create(&id, NULL, another, NULL);
  fprintf(stderr,"main\n");
  int pid = fork();
  fprintf(stderr,"forked\n");

  if(pid > 0)
  {
    pthread_join(id, NULL);
//    pthread_mutex_destroy(&mutex);
    return 1;
  }
  else if(pid == 0)//子进程
  {
    sleep(1);
    fprintf(stderr,"子进程， 获取锁\n");
    /*
    子进程从父进程继承了互斥锁mutex的状态，
    该互斥锁处于锁住状态，
    这是由父进程中的子线程执行pthread_mutex_lock引起
    因此，下面这句加锁会一直阻塞
    */
    fprintf(stderr,"stucked\n");
    void * p = malloc(1);
    fprintf(stderr,"stucked2\n");
    free(p);
    fprintf(stderr,"stucked3\n");
//    pthread_mutex_lock(&mutex);
//    printf("阻塞了。。。。\n");
//    pthread_mutex_unlock(&mutex);
    exit(0);
  }

//  size_t size = 12;
//  void *mem = malloc(size);
//  printf("Successfully malloc'd %zu bytes at addr %p\n", size, mem);
//  assert(mem != NULL);
//  free(mem);
//  printf("Successfully free'd %zu bytes from addr %p\n", size, mem);
  return 0;
}