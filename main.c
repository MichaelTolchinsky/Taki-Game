/*
 * Michael Tolchinsky 321223950
 * TODO: build this fucking taki game
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // in order to use the "rand" and "srand" functions
#include <time.h>	// in order to use "time" function

#define RED 'R' // 1
#define BLUE 'B' // 2
#define GREEN 'G' // 3
#define YELLOW 'Y' // 4

typedef struct card {
    char value[10]; // (1-9 ,+, STOP, <->,COLOR, TAKI )
    char color;
} Card;

typedef struct player {
    char name[20];
    Card cards[50];
} Player;

void printWelcomeMessage();
int nofPlayersInput();
void playersNameInput(Player *players, int nofPlayers);
int getRandomNumber(int from,int to);

void getStartCard(Card *startCard);

void main() {
    int nofPlayers;
    Player players[10];
    Card upperCard;

    printWelcomeMessage();
    nofPlayers = nofPlayersInput();
    playersNameInput(players,nofPlayers);
    getStartCard(&upperCard);
    //printf("%c %c",upperCard.value[0],upperCard.color);
}

void getStartCard(Card *startCard) {
    int num;
    char cardColor;

    // get card color
    num = getRandomNumber(1,4);
    switch (num) {
        case 1:
            cardColor = RED;
            break;

        case 2:
            cardColor = BLUE;
            break;

        case 3:
            cardColor = GREEN;
            break;

        case 4:
            cardColor = YELLOW;
            break;
    }

    // get card number between 1-9
    num = getRandomNumber(1,9);
    startCard->value[0]=num + '0';
    startCard->color = cardColor;
}

int getRandomNumber(int from,int to) {
    // In order to generate random numbers, we use the srand function only once,
    // and then use the rand function for each random number we want to generate.
    int num;
    // srand(x) function call (for an integer x) is used to set the starting value (seed)
    // for generating a sequence of random integer values.
    // When we use srand(x) (for an integer x), we'll get the same random values
    // in each program run (therefore not so random).
    // srand(time(NULL)) function call makes use of the computer's internal clock
    // to control the choice of the seed. Since time is continually changing,
    // the seed is forever changing. Therefore we'll get different sequence of random
    // values in each program run.
    srand(time(NULL));
    // rand() function call returns a random positive integer
    num = from + rand() % to;
    return num;
}

void playersNameInput(Player *players, int nofPlayers) {
    for (int i = 0; i < nofPlayers; i++) {
        printf("Please enter the first name of player #%d:\n",i+1);
        scanf("%s", (players+i)->name);
    }
}

int nofPlayersInput() {
    int players;
    printf("Please enter the number of players: \n");
    scanf("%d", &players);

    return players;
}

void printWelcomeMessage() {
    printf("************  Welcome to TAKI game !!! *********** \n\n");
}
