#define _CRT_SECURE_NO_WARNINGS
/*
 * Michael Tolchinsky 321223950
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> // in order to use the "rand" and "srand" functions
#include <time.h>	// in order to use "time" function

#define RED 'R' // 1
#define BLUE 'B' // 2
#define GREEN 'G' // 3
#define YELLOW 'Y' // 4
#define PLUS '+' // '+' represented by number 10
#define STOP "STOP" // "STOP" represented by number 11
#define CHANGE_DIR "<->" // "<->" represented by number 12
#define COLOR "COLOR" // "COLOR" represented by number 13
#define TAKI "TAKI" // "TAKI" represented by number 14
#define CARD_COLS 9
#define CARD_ROWS 6
#define MAX_NAME_LEN 20

typedef struct card {
    //char value[10]; // (1-9 ,+, STOP, <->,COLOR, TAKI )
    int value;
    char color;
} Card;

typedef struct player {
    char name[MAX_NAME_LEN];
    int nofCards;
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
void printCardValue(Card card);
void playGame(Player *players, int nofPlayers, Card *upperCard);
void printUpperCard(Card *upperCard);
void playerActionInput(int *playerAction, int nofCards, bool *isTaki);
void nextPlayerTurn(int *currentTurn, int nofPlayers, bool isTaki, bool reverse);
void printPlayerHand(Player *player);
void playCard(Player *players, Card *upperCard, int turn, int playerAction);
void checkForWinner(Player *player, bool *isWinner);
void chooseNewColor(char *color);

int cardInput(int nofCards, bool *isTaki);

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

    // move to clean function later if needed
    free(players);
}

// separate to helper functions == make this shorter
void playGame(Player *players, int nofPlayers, Card *upperCard) {
    bool isWinner = false,isValidMove = false,isTaki=false,isReverseTurns = false;
    int turn = 0,playerAction;

    while(!isWinner){
        for (; turn < nofPlayers;) {
            printUpperCard(upperCard);
            printPlayerHand(players + turn);

            while(!isValidMove){
                playerActionInput(&playerAction, (players + turn)->nofCards, &isTaki);
                if(playerAction == 0){
                        generateRandomCard(&((players + turn)->cards[((players + turn)->nofCards)++]), false);
                        nextPlayerTurn(&turn, nofPlayers, isTaki, isReverseTurns);
                        isValidMove = !isValidMove;
                }
                else{
                    if (((players+turn)->cards[playerAction-1].value >= 1 &&
                        (players+turn)->cards[playerAction-1].value <= 9) && (
                        (players+turn)->cards[playerAction-1].color == upperCard->color ||
                        (players+turn)->cards[playerAction-1].value == upperCard->value)){
                        // update cards after validity check
                        playCard(players, upperCard, turn, playerAction);
                        nextPlayerTurn(&turn, nofPlayers, isTaki, isReverseTurns);
                        isValidMove = !isValidMove;
                        // plus
                    } else if((players+turn)->cards[playerAction-1].value == 10 &&
                             (players+turn)->cards[playerAction-1].color == upperCard->color){
                        playCard(players, upperCard, turn, playerAction);

                        if((players+turn)->nofCards == 1){
                            generateRandomCard(&((players+turn)->cards[((players+turn)->nofCards)++]),false);
                        }
                        isValidMove = !isValidMove;
                        // stop card
                    } else if((players+turn)->cards[playerAction-1].value == 11 &&
                            (players+turn)->cards[playerAction-1].color == upperCard->color){
                        if(nofPlayers == 2 && (players+turn)->nofCards == 1){
                            generateRandomCard(&((players+turn)->cards[((players+turn)->nofCards)++]),false);
                        }
                        playCard(players,upperCard,turn,playerAction);
                        turn++;
                        nextPlayerTurn(&turn, nofPlayers, isTaki, isReverseTurns);
                        isValidMove = !isValidMove;
                    }
                    // change-dir
                    else if((players+turn)->cards[playerAction-1].value == 12 &&
                            (players+turn)->cards[playerAction-1].color == upperCard->color){
                        playCard(players,upperCard,turn,playerAction);
                        // TODO: change game direction
                        isReverseTurns = !isReverseTurns;
                        nextPlayerTurn(&turn, nofPlayers, isTaki, isReverseTurns);
                        isValidMove = !isValidMove;
                    }
                    // change color
                    else if((players+turn)->cards[playerAction-1].value == 13){
                        isTaki = false;
                        chooseNewColor(&(players+turn)->cards[playerAction-1].color);
                        playCard(players, upperCard, turn, playerAction);
                        nextPlayerTurn(&turn, nofPlayers, isTaki, isReverseTurns);
                        isValidMove = !isValidMove;
                        // Taki card TODO: needs to be improved
                    }else if ((players+turn)->cards[playerAction-1].value == 14 &&
                            (players+turn)->cards[playerAction-1].color == upperCard->color){
                        isTaki = true;
                        playCard(players, upperCard, turn, playerAction);
                        isValidMove = !isValidMove;
                    }
                    else {
                        printf("Invalid choice! Try again.\n");
                    }
                }
            }
            isValidMove = !isValidMove;
            checkForWinner(players, &isWinner);
        }
    }
}

void chooseNewColor(char *color) {
    int colorNum;
    printf("Please enter your color choice:\n"
           "1 - Yellow\n"
           "2 - Red\n"
           "3 - Blue\n"
           "4 - Green\n");
    scanf("%d",&colorNum);
    *color = getColor(colorNum);
}

void checkForWinner(Player *player, bool *isWinner) {
    if((player)->nofCards == 0){
        printf("The winner is... %s! Congratulations!",(player)->name);
        *isWinner=!isWinner;
    }
}

void playCard(Player *players, Card *upperCard, int turn, int playerAction) {
    *upperCard = (players + turn)->cards[playerAction - 1];
    (players+turn)->cards[playerAction-1] = (players+turn)->cards[(players+turn)->nofCards-1];
    (players+turn)->nofCards--;
}

void printPlayerHand(Player *player) {
    printf("%s's turn:\n\n", (player)->name);
    for (int i = 0; i < (player)->nofCards; i++) {
        printf("Card #%d:\n",i+1);
        printCard((player)->cards[i]);
    }
}

void nextPlayerTurn(int *currentTurn, int nofPlayers, bool isTaki, bool reverse) {
    if(isTaki) return;

    if(reverse){
        if(*currentTurn >= 1){
            *currentTurn -= 1;
        } else {
            *currentTurn = nofPlayers-1;
        }
    } else {
        if(*currentTurn < nofPlayers-1){
            *currentTurn += 1;
        } else {
            *currentTurn = 0;
        }
    }

}

void playerActionInput(int *playerAction, int nofCards, bool *isTaki) {
    int number;
    number = cardInput(nofCards, isTaki);

    while (number < 0 || number > nofCards){
        printf("Invalid choice! Try again.\n");
        number = cardInput(nofCards, isTaki);
    }
    *playerAction = number;
}

int cardInput(int nofCards, bool *isTaki) {
    int number;
    if(!*isTaki){
        printf("Please enter 0 if you want to take a card from the deck\n");
    } else {
        printf("Please enter 0 if you want to finish your turn\n");
    }
    printf("or 1-%d if you want to put one of your cards in the middle:\n", nofCards);
    scanf("%d", &number);

    if(*isTaki && number == 0) {
        *isTaki = !*isTaki;
    }

    return number;
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
                    printCardValue(card);
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
        (players+i)->nofCards = 4;
        // TODO: for each player malloc size of cards array to 4??
        for (int j = 0; j < (players+i)->nofCards; j++) {
            generateRandomCard(&(players+i)->cards[j],false);
        }
    }
}

void generateRandomCard(Card *card, bool isUpperCard) {
    int num;

    if(isUpperCard){
        // get card number between 1-9
        num = getRandomNumber(1,9);
    } else {
        // get card number between 1-14
        num = getRandomNumber(1,14);
    }
    card->value = num;

    if(num != 13){
        // get card color
        num = getRandomNumber(1,4);
        card->color = getColor(num);
    }
}

void printCardValue(Card card) {
    switch (card.value) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            printf("%d", card.value);
            break;
        case 10:
            printf("%c",PLUS);
            break;
        case 11:
            printf(STOP);
            break;
        case 12:
            printf(CHANGE_DIR);
            break;
        case 13:
            printf(COLOR);
            break;
        case 14:
            printf(TAKI);
            break;
        default:
            break;
    }
}

char getColor(int num) {
    char cardColor;

    switch (num) {
        case 1:
            cardColor = YELLOW;
            break;

        case 2:
            cardColor = RED;
            break;

        case 3:
            cardColor = BLUE;
            break;

        case 4:
            cardColor = GREEN;
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
