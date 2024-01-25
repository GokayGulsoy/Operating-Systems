#include <stdio.h>
#include <string.h>
#include <pthread.h>

int i = 20;

void* func(void* p) {
    int* a = (int*)p;

    i = i * (*a);

    pthread_exit(&i);
}

int main(void) {

    pthread_t t_1;

    int j = 10;
    pthread_create(&t_1, NULL, func, &j);

    int* ptr;

    pthread_join(t_1, (void**)&ptr);

    printf("Value received from the thread: ");
    printf("%i\n", *ptr);
}
