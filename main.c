/*
 * Michael Tolchinsky 321223950
 * TODO: build this fucking taki game
 */

#include <stdio.h>
#include <string.h>

#define RED 'R'
#define BLUE 'B'
#define GREEN 'G'
#define YELLOW 'Y'

typedef struct card {
    char color;
} Card;

typedef struct player {
    char name[20];
    Card cards[50];
} Player;

void printWelcomeMessage();
int nofPlayersInput();
void playersNameInput(Player *players, int nofPlayers);

void main() {
    int nofPlayers;
    Player players[10];
    Card upperCard;

    printWelcomeMessage();
    nofPlayers = nofPlayersInput();
    playersNameInput(players,nofPlayers);
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
