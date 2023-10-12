#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        if (clearenv() == 0) {
            printf("All environment variables are cleared.\n");
        } else {
            perror("Error clearing environment variables");
            return 1;
        }
    } else if (argc == 2) {
        const char *variable_name = argv[1];
        if (unsetenv(variable_name) == 0) {
            printf("Variable '%s' is removed from the environment.\n", variable_name);
        } else {
            perror("Error removing environment variable");
            return 1;
        }
    } else {
        printf("Usage:\n");
        printf("To remove a specific variable: %s <variable_name>\n", argv[0]);
        printf("To clear all environment variables: %s\n", argv[0]);
        return 1;
    }

    extern char **environ;
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}