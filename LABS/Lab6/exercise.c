#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int* fibo_array;  // [1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...]

void* func(void* p) {

  int* thread_val = (int*)p;

  printf("THREAD %d\n", *thread_val);

  if ((*thread_val+1) == 0 || (*thread_val+1) == 1) {

    printf("Location %d of the fibo_array: %d\n\n", *thread_val, fibo_array[0]);

  } else {

    int itr = 2;
    while(itr < *thread_val+1){

      fibo_array[itr] = fibo_array[itr-1] + fibo_array[itr-2];

      itr++;
    }

    printf("Location %d of the fibo_array: %d\n\n", *thread_val, fibo_array[itr-1]);

  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

  int n = atoi(argv[argc-1]);

  printf("You entered %d\n\n", n);

  fibo_array = (int*)malloc((n+2)*sizeof(int));
  fibo_array[0] = 1;
  fibo_array[1] = 1;

  pthread_t thread_array[n];

  for(int i=0; i<=n; i++) {
    printf("i: %d\n", i);

    pthread_create(&(thread_array[i]), NULL, func, &i);

    sleep(0.01);  // What happens when you remove this line???
  }

  for(int i=0; i<=n; i++) {
    pthread_join(thread_array[i], NULL);
  }

  pthread_exit(NULL);

  //return 0;
}
