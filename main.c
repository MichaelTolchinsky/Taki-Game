#define _CRT_SECURE_NO_WARNINGS
/*
 * Michael Tolchinsky 321223950
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // in order to use the "rand" and "srand" functions
#include <time.h>	// in order to use "time" function
#include <stdbool.h>

#define RED 'R' // 1
#define BLUE 'B' // 2
#define GREEN 'G' // 3
#define YELLOW 'Y' // 4
#define PLUS '+' // '+' represented by number 10
#define STOP "STOP" // "STOP" represented by number 11
#define CHANGE_DIR "<->" // "<->" represented by number 12
#define TAKI "TAKI" // "<->" represented by number 13
#define COLOR "COLOR" // "<->" represented by number 14

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
void generateRandomCard(Card *card, bool isUpperCard);
void printCard(Card card);

void initGame(Player *players, int nofPlayers, Card *upperCard);

void main() {
    int nofPlayers;
    Player players[10];
    Card upperCard;

    printWelcomeMessage();
    nofPlayers = nofPlayersInput();
    playersNameInput(players,nofPlayers);
    initGame(players,nofPlayers,&upperCard);


}

void initGame(Player *players, int nofPlayers, Card *upperCard) {
    generateRandomCard(upperCard, true);

    for (int i = 0; i < nofPlayers; i++) {
        for (int j = 0; j < 4; j++) {
            generateRandomCard(&((players+i)->cards[j]),false);
        }
    }
}

void printCard(Card card) {

    for (int i = 0; i < 9; i++) {
        printf("*");
    }
    printf("\n");
}

void generateRandomCard(Card *card, bool isUpperCard) {
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

        default:
            break;
    }

    if(isUpperCard){
        // get card number between 1-9
        num = getRandomNumber(1,9);
        card->value[0]= num + '0';
    } else {
        // get card number between 1-14
        num = getRandomNumber(1,14);
        if(num > 9){
            switch (num) {
                case 10:
                    card->value[0] = PLUS;
                    break;
                case 11:
                    strcpy(card->value ,STOP);
                    break;
                case 12:
                    strcpy(card->value,CHANGE_DIR);
                    break;
                case 13:
                    strcpy(card->value,COLOR);
                    break;
                case 14:
                    strcpy(card->value,TAKI);
                    break;
                default:
                    break;
            }
        } else {
            card->value[0]= num + '0';
        }
    }
    if(num == 13){
        card->color = '\0';
    } else {
        card->color = cardColor;
    }
}

int getRandomNumber(int from,int to) {
    int num;
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
