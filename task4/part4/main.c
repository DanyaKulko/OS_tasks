#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *username = getenv("USER");
    if (username == NULL) {
        perror("Error getting username");
        return 1;
    }

    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        perror("Error getting home directory");
        return 1;
    }

    const char *user_shell = getenv("SHELL");
    if (user_shell == NULL) {
        perror("Error getting user's shell");
        return 1;
    }

    printf("Information about the current user:\n");
    printf("Username: %s\n", username);
    printf("Home directory: %s\n", home_dir);
    printf("Shell: %s\n", user_shell);

    return 0;
}
