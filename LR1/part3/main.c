#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    char *str;
    int count;
} TextParam;

typedef struct {
    int rangeMin;
    int rangeMax;
    int target;
    int count;
} NumberParam;

void *textThreadFunction(void *arg) {
    TextParam *param = (TextParam *)arg;
    for (int i = 0; i < param->count; i++) {
        printf("Text Thread: %s\n", param->str);
        sleep(1);
    }
    return NULL;
}

void *numberThreadFunction(void *arg) {
    NumberParam *param = (NumberParam *)arg;
    srand(time(NULL));

    for (int i = 0; i < param->count; i++) {
        int num = rand() % (param->rangeMax - param->rangeMin + 1) + param->rangeMin;
        printf("Number Thread: %d\n", num);
        if (num == param->target) {
            printf("Number Thread: Target number %d found, exiting.\n", param->target);
            return NULL;
        }
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t textThread, numberThread;
    TextParam textParam = {"Example string", 10};
    NumberParam numberParam = {1, 50, 25, 15};

    pthread_create(&textThread, NULL, textThreadFunction, (void *)&textParam);
    pthread_create(&numberThread, NULL, numberThreadFunction, (void *)&numberParam);

    pthread_join(textThread, NULL);
    pthread_join(numberThread, NULL);

    printf("Main Thread: All child threads have completed.\n");

    return 0;
}
