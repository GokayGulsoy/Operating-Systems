#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep()
#include <pthread.h>

int i = 20;

void *threadFunc(void *prm) {

  sleep(3);
  printf("I am a thread !\n");

  i = i*2;

  sleep(7);

  pthread_exit(&i);
}

int main() {
  pthread_t t_1;
  printf("Before Thread\n");

  pthread_create(&t_1, NULL, threadFunc, NULL);

  int* ptr;

  pthread_join(t_1, (void**)&ptr);

  sleep(3);

  printf("After Thread\n");

  printf("Value from the thread: %d\n", *ptr);

  // pthread_exit(NULL);
  return 0;
}
