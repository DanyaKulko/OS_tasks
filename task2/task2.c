#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMS_COUNT 3

int playOneRound(int bet);
int generateRandomSymbol();

int main() {
    srand(time(NULL));

    int balance = 1000;

    while (balance > 0) {
        printf("Your balance: %d\n", balance);

        int bet;
        printf("Make a bet (or 0 to exit):");
        scanf("%d", &bet);

        if (bet == 0) {
            break;
        }

        if (bet > balance) {
            printf("Your bet is bigger than balance, try again.\n");
            continue;
        }

        int result = playOneRound(bet);

        if (result > 0) {
            balance += result;
            printf("You won %d!\n", result);
        } else {
            balance -= bet;
            printf("You lost your bet.\n");
        }
    }

    printf("Game over!\n");

    return 0;
}


int generateRandomSymbol() {
    return rand() % 10;
}

int playOneRound(int bet) {
    int symbols[NUMS_COUNT];

    printf("Random numbers: ");

    for (int i = 0; i < NUMS_COUNT; i++) {
        symbols[i] = generateRandomSymbol();
        printf("%d ", symbols[i]);
    }

    printf("\n");


    if (symbols[0] == symbols[1] && symbols[1] == symbols[2]) {
        if (symbols[0] == 7) {
            return bet * 3;
        }
        return bet * 2;
    }

    for (int i = 0; i < NUMS_COUNT; i++) {
        if (symbols[i] == 7) {
            return bet;
        }
    }


    for (int i = 0; i < NUMS_COUNT; i++) {
        for (int j = i + 1; j < NUMS_COUNT; j++) {
            if (symbols[i] == symbols[j]) {
                return bet;
            }
        }
    }

    return 0;
}
