#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_environment() {
    extern char **environ;
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

void print_help() {
    printf("Usage: environ [options]\n");
    printf("Options:\n");
    printf("  -h, --help                  Display this help message\n");
    printf("  -i, --info <variable>       Display the value of the specified variable\n");
    printf("  -s, --set <variable=value>  Set the specified variable to the given value\n");
    printf("  -a, --assign <variable>     Assign a new value to the specified variable\n");
    printf("  -v, --value <value>         Value to assign when using -a option\n");
    printf("  -d, --del <variable>        Delete the specified variable\n");
    printf("  -c, --clear                 Clear the entire environment\n");
}

void get_variable_value(const char *variable) {
    char *value = getenv(variable);
    if (value) {
        printf("%s=%s\n", variable, value);
    } else {
        printf("Variable '%s' not found in the environment.\n", variable);
    }
}

void set_variable_value(const char *variable, const char *value) {
    if (setenv(variable, value, 1) == 0) {
        printf("Set %s=%s\n", variable, value);
    } else {
        perror("Error setting environment variable");
    }
}

void assign_variable_value(const char *variable, const char *value) {
    if (value == NULL) {
        value = "";
    }

    if (variable != NULL) {
        if (setenv(variable, value, 1) == 0) {
            printf("Assigned %s=%s\n", variable, value);
        } else {
            perror("Error assigning environment variable");
        }
    } else {
        printf("Variable name is missing. Assignment not performed.\n");
    }
}

void delete_variable(const char *variable) {
    if (unsetenv(variable) == 0) {
        printf("Deleted variable: %s\n", variable);
    } else {
        perror("Error deleting environment variable");
    }
}

void clear_environment() {
    extern char **environ;
    char **env = environ;

    while (*env) {
        char *variable = *env;
        char *equal_sign = strchr(variable, '=');

        if (equal_sign != NULL) {
            *equal_sign = '\0';
            unsetenv(variable);
        }

        env++;
    }

    printf("Environment cleared.\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_environment();
    } else if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_help();
        } else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--clear") == 0) {
            clear_environment();
        } else {
            fprintf(stderr, "Invalid option. Use -h or --help for usage information.\n");
            return 1;
        }
    } else if (argc == 3) {
        if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0) {
            get_variable_value(argv[2]);
        } else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--del") == 0) {
            delete_variable(argv[2]);
        } else if ((strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--set") == 0) && strchr(argv[2], '=') != NULL) {
            char *variable = strtok(argv[2], "=");
            char *value = strtok(NULL, "=");
            printf("\n\n%s=%s\n\n", variable, value);
            set_variable_value(variable, value);
        } else {
            fprintf(stderr, "Invalid option. Use -h or --help for usage information.\n");
            return 1;
        }
    } else if (argc == 4) {
         if ((strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--assign") == 0) && strcmp(argv[2], "-v") == 0) {
            assign_variable_value(argv[3], NULL);
        } else {
            fprintf(stderr, "Invalid option. Use -h or --help for usage information.\n");
            return 1;
        }
    } else if (argc == 5) {
        if ((strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--assign") == 0) && strcmp(argv[3], "-v") == 0) {
            assign_variable_value(argv[2], argv[4]);
        } else {
            fprintf(stderr, "Invalid option. Use -h or --help for usage information.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid usage. Use -h or --help for usage information.\n");
        return 1;
    }

    return 0;
}
