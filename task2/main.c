#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMS_COUNT 3

int playOneRound(int bet);

int main() {
    int balance = 1000;

    while (balance > 0) {
        printf("Your balance: %d$\n", balance);

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
        balance -= bet;

        int result = playOneRound(bet);

        if (result > 0) {
            balance += result;
            if (result == bet) {
                printf("You won your bet back(%d$)\n", result);
            } else {
                printf("You won %d$!\n", result);
            }
        } else {
            printf("You lost your bet (%d$)\n", bet);
        }
    }

    printf("Game over! Your final balance: %d$\n", balance);

    return 0;
}


int generateRandomSymbol() {
    return rand() % 10;
}

int isNumbersEqual(int *arr[]) {
    for (int i = 0; i < NUMS_COUNT - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// returns 0 if user lost,
// in other case return bet which user won
int playOneRound(int bet) {
    srand(time(NULL));

    int symbols[NUMS_COUNT];

    printf("Random numbers: ");

    for (int i = 0; i < NUMS_COUNT; i++) {
        symbols[i] = generateRandomSymbol();
        printf("%d ", symbols[i]);
    }

    printf("\n");



    if (isNumbersEqual((int **) &symbols) == 1) {
        if (symbols[0] == 7) {
            printf("Jackpot!\n");
            return bet * 3;
        }
        return bet * 2;
    }

    for (int i = 0; i < NUMS_COUNT; i++) {
        for (int j = i + 1; j < NUMS_COUNT; j++) {
            if (symbols[i] == symbols[j]) {
                return bet * 2;
            }
        }
    }


    for (int i = 0; i < NUMS_COUNT; i++) {
        if (symbols[i] == 7) {
            return bet;
        }
    }

    return 0;
}
