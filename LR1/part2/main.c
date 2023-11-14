#include <pthread.h>
#include <stdio.h>

typedef struct {
    char *name;
    char *str;
    int num;
} ThreadParam;

void *threadFunction(void *arg) {
    ThreadParam *param = (ThreadParam *)arg;

    for (int i = 1; i <= param->num; i++) {
        printf("Thread %s. %s %d\n", param->name, param->str, i);
    }

    return NULL;
}

int main() {
    pthread_t threads[4];
    ThreadParam params[4] = {
            {"1", "String1", 5},
            {"2", "String2", 5},
            {"3", "String3", 5},
            {"4", "String4", 5}
    };

    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i], NULL, threadFunction, (void *)&params[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }

    return 0;
}
