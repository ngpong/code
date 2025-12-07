#include <pthread.h>
#include <stdio.h>

pthread_key_t key;
pthread_t thid1;
pthread_t thid2;

void str_alloc_destroy_accu(void* accu) {
  printf("Thread %lx: freeing buffer at %p\n", pthread_self(), accu);
}

void* thread2(void* arg) {
  printf("thread:%lu is running\n", pthread_self());

  int key_va = 3;

  pthread_setspecific(key, (void*)key_va);

  printf("thread:%lu return %d\n", pthread_self(), (int)pthread_getspecific(key));
}


void* thread1(void* arg) {
  printf("thread:%lu is running\n", pthread_self());

  int key_va = 5;

  pthread_setspecific(key, (void*)key_va);

  pthread_create(&thid2, NULL, thread2, NULL);

  printf("thread:%lu return %d\n", pthread_self(), (int)pthread_getspecific(key));
}


int main() {
  printf("main thread:%lu is running\n", pthread_self());

  pthread_key_create(&key, str_alloc_destroy_accu);

  pthread_create(&thid1, NULL, thread1, NULL);

  pthread_join(thid1, NULL);
  pthread_join(thid2, NULL);

  int key_va = 1;
  pthread_setspecific(key, (void*)key_va);

  printf("thread:%lu return %d\n", pthread_self(), (int)pthread_getspecific(key));

  pthread_key_delete(key);

  printf("main thread exit\n");
  return 0;
}
