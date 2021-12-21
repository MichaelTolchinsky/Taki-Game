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
#define COLOR "COLOR" // "<->" represented by number 13
#define TAKI "TAKI" // "TAKI" represented by number 14
#define CARD_COLS 9
#define CARD_ROWS 6

typedef struct card {
    char value[10]; // (1-9 ,+, STOP, <->,COLOR, TAKI )
    char color;
} Card;

typedef struct player {
    char name[20];
    // TODO: change size to 4
    // maybe add int nofCards as logical size??
    Card cards[50];
} Player;

void printWelcomeMessage();
int nofPlayersInput();
void playersNameInput(Player *players, int nofPlayers);
int getRandomNumber(int from,int to);
void generateRandomCard(Card *card, bool isUpperCard);
void printCard(Card card);
void initGame(Player *players, int nofPlayers, Card *upperCard);
char getColor(int num);
void getSpecialCardValue(Card *card, int num);
void playGame(Player *players, int nofPlayers, Card *upperCard);
void printUpperCard(Card *upperCard);


void main() {
    int nofPlayers;
    Player *players = NULL;
    Card upperCard;

    srand(time(NULL));
    printWelcomeMessage();
    nofPlayers = nofPlayersInput();
    players = (Player*)malloc(nofPlayers * sizeof(*players));
    playersNameInput(players,nofPlayers);

    initGame(players,nofPlayers,&upperCard);
    playGame(players,nofPlayers,&upperCard);

    // maybe move to clean function later
    free(players);
}

void playGame(Player *players, int nofPlayers, Card *upperCard) {
    bool isWinner = false;
    int turn = 0,playerAction;

    while(!isWinner){
        printUpperCard(upperCard);
        for (; turn < nofPlayers; turn++) {
            printf("%s's turn:\n\n", (players+turn)->name);
            for (int i = 0; i < 4; i++) {
                printf("Card #%d:\n",i+1);
                printCard((players+turn)->cards[i]);
            }

            // TODO: move this to function
            printf("Please enter 0 if you want to take a card from the deck\n"
                   "or 1-4 if you want to put one of your cards in the middle:\n");
            scanf("%d", &playerAction);

            // TODO: if playerAction == 0 dynamicaly add memory to cards array for new card and check for success, then generate the new card
            // TODO: else check if user can play with chosen card if not show invalid card message
        }



        // TODO change to good logic
        isWinner=!isWinner;
    }
}


void printUpperCard(Card *upperCard) {
    printf("\nUpper card:\n");
    printCard(*upperCard);
}

// TODO improve printing
void printCard(Card card) {
    for (int i = 1; i <= CARD_ROWS; i++)
    {
        for (int j = 1; j <= CARD_COLS; j++)
        {
            if (i==1 || i== CARD_ROWS || j==1 || j== CARD_COLS){
                printf("*");
            } else if(i == 3 && j == 5){
                printf("%s", card.value);
            } else if(i == 4 && j == 5){
                printf("%c", card.color);
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void initGame(Player *players, int nofPlayers, Card *upperCard) {
    generateRandomCard(upperCard, true);

    for (int i = 0; i < nofPlayers; i++) {
        // TODO: for each player malloc size of cards array to 4??
        for (int j = 0; j < 4; j++) {
            generateRandomCard(&(players+i)->cards[j],false);
        }
    }
}

void generateRandomCard(Card *card, bool isUpperCard) {
    int num;

    if(isUpperCard){
        // get card number between 1-9
        num = getRandomNumber(1,9);
        card->value[0]= num + '0';
    } else {
        // get card number between 1-14
        num = getRandomNumber(1,14);
        if(num > 9){
            getSpecialCardValue(card, num);
        } else {
            card->value[0]= num + '0';
        }
    }

    if(num != 13){
        // get card color
        num = getRandomNumber(1,4);
        card->color = getColor(num);
    }
}

void getSpecialCardValue(Card *card, int num) {
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
            card->value[0] = '\0';
            break;
    }
}

char getColor(int num) {
    char cardColor;

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
            cardColor='\0';
            break;
    }

    return cardColor;
}

int getRandomNumber(int from,int to) {
    int num;
//    srand(time(0));
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
    printf("************  Welcome to TAKI game !!! *********** \n");
}
