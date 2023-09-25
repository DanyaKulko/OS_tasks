#include <stdio.h>

void add_student();
void print_s();

struct sinfo {
    char fname[50];
    char lname[50];
    int age;
} st[55];

int main() {
    int choice;
    while (1) {
        printf("1. Add new Student\n");
        printf("2. Check all students\n");
        printf("3. Exit\n");
        printf("Enter action number: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                print_s();
                break;
            case 3:
                return 0;
        }
    }
}


int i = 0;

void add_student() {
    printf("First name: ");
    scanf("%s", st[i].fname);
    printf("Last name: ");
    scanf("%s", st[i].lname);
    printf("Age: ");
    scanf("%d", &st[i].age);

    i++;
}

void print_s() {
    printf("First name  Last Name   Age\n");
    int j;
    for(j = 0; j < i; j++){
        printf("%5s %11s %9d\n",st[j].fname, st[j].lname,st[j].age);
    }
}
