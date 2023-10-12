#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <variable_name> <variable_value>\n", argv[0]);
        return 1;
    }

    const char *variable_name = argv[1];
    const char *variable_value = argv[2];

    if (setenv(variable_name, variable_value, 1) == 0) {
        printf("Variable '%s' is set to '%s'\n", variable_name, variable_value);
    } else {
        perror("Error setting environment variable");
        return 1;
    }

    char *environment_value = getenv(variable_name);
    if (environment_value != NULL) {
        printf("Variable '%s' is currently set to '%s'\n", variable_name, environment_value);
    } else {
        printf("Variable '%s' is not found in the environment.\n", variable_name);
    }

    return 0;
}
