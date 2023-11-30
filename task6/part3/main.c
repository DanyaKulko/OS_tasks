#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum) {
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Використання: %s <секунди> <повідомлення>\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);
    char *message = argv[2];

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        signal(SIGALRM, alarm_handler);
        alarm(seconds);
        pause();

        printf("Будильник: %s\n", message);
    } else {
        printf("Будильник встановлено на %d секунд.\n", seconds);
        exit(0);
    }

    return 0;
}