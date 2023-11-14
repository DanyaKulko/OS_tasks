#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *childThreadFunction() {
    for (int i = 1; i <= 10; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    
    pthread_t childThread;

    if (pthread_create(&childThread, NULL, childThreadFunction, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }

    if (pthread_join(childThread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    return 0;
}
