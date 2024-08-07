#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h> 

#define BOARD_SIZE 10

char displayTitle();
void renderBoard(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]);
int placeShip(int shipSize, int x[2], int y[2], char board[BOARD_SIZE][BOARD_SIZE]);
void setupShips(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]);


int main(){

    char shootingBoard[BOARD_SIZE][BOARD_SIZE];
    char board[BOARD_SIZE][BOARD_SIZE];
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            board[i][j] = '0';
            shootingBoard[i][j] = '0';
        }
    }

    shootingBoard[3][5] = 'M';
    shootingBoard[2][7] = 'H';
    shootingBoard[6][5] = 'M';
    shootingBoard[8][2] = 'H';

    char wantsToPlay;
    wantsToPlay = displayTitle();
    if(wantsToPlay == 'Y'){
        printf("\nlets play\n\n");
        setupShips(board, shootingBoard);
        renderBoard(board, shootingBoard);
    } else{
        printf("No problem");
    }

    return 0;
}


char displayTitle(){
    char answer;
    printf("\n*****************\n");
    printf("   Battleships   ");
    printf("\n*****************\n\n");
    printf("options:\n");
    printf("Yeah sure, lets play (Y)\n");
    printf("No thanks, I'm scared (N)\n");
    scanf(" %c", &answer);
    answer = toupper(answer);
    return answer;
}


void renderBoard(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]){
    
    char to_red[] = "\033[31m";
    char to_green[] = "\033[32m";
    char to_yellow[] = "\033[33m";
    char to_white[] = "\033[0m";

    printf("\n   Your Board                     Battle map\n");
    printf("   A B C D E F G H I J            A B C D E F G H I J\n");
    for(int i = 0; i < BOARD_SIZE; i++){
        if(i == 9){
            printf("%d", i + 1);
        } else{
            printf(" %d", i + 1);
        }
        for(int j = 0; j < BOARD_SIZE; j++){
            char elem = board[j][i];
            if(elem == 'H'){
                printf(" %s%c%s", to_red, elem, to_white);
            }
            if(elem == 'S'){
                printf(" %s%c%s", to_green, elem, to_white);
            }
            if(elem == 'M'){
                printf(" %s%c%s", to_yellow, elem, to_white);
            }
            if(elem == '0'){
                printf(" %c", elem);   
            }
        }

        printf("         ");

        if(i == 9){
            printf("%d", i + 1);
        } else{
            printf(" %d", i + 1);
        }
        for(int j = 0; j < BOARD_SIZE; j++){
            char elem = shootingBoard[j][i];
            if(elem == 'H'){
                printf(" %s%c%s", to_red, elem, to_white);
            }
            if(elem == 'S'){
                printf(" %s%c%s", to_green, elem, to_white);
            }
            if(elem == 'M'){
                printf(" %s%c%s", to_yellow, elem, to_white);
            }
            if(elem == '0'){
                printf(" %c", elem);   
            }
        }

        printf("\n");
    }
}


int placeShip(int shipSize, int start[2], int end[2], char board[BOARD_SIZE][BOARD_SIZE]){
    
    int ship[shipSize][shipSize];
    int dist = 0;
    int x1 = start[0]; int y1 = start[1];
    int x2 = end[0]; int y2 = end[1];

    if(x1 == x2){
        dist = abs(y1 - y2);
    }
    if(y1 == y2){
        dist = abs(x1 - x2);
    }
    if(dist != shipSize - 1){
        return 0;
    }

    for(int i = 0; i < shipSize; i++){
        if(x1 == x2){
            if(y1 < y2){
                ship[i][0] = x1;
                ship[i][1] = y1 + i;
            } else{
                ship[i][0] = x1;
                ship[i][1] = y1 - i;
            }
        }
        if(y1 == y2){
            if(x1 < x2){
                ship[i][0] = x1 + i;
                ship[i][1] = y1;
            } else{
                ship[i][0] = x1 - i;
                ship[i][1] = y1;
            }
        }
    }

    for(int i = 0; i < shipSize; i++){
        if(board[ship[i][0]][ship[i][1]] == 'S'){
            return 0;
        } 
    }
    for(int i = 0; i < shipSize; i++){
        board[ship[i][0]][ship[i][1]] = 'S';
    }

    return 1;
}


void setupShips(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]){
    char startInput[2];
    int start[2];
    char endInput[2];
    int end[2];
    char letter;
    int i = 2;
    int placed;

    printf("Lets put down four ships\n");
    printf("Enter the coordinates for the start and end of each ship\n");
    printf("The coordinates need to be the correct distance apart\n");
    printf("You also need to enter them as letter then number\n");
    printf("For example: a ship of length 3 could have coordinates A1 to A3\n");
    
    while(i<6){
        placed = 0;
        renderBoard(board, shootingBoard);
        printf("For ship of length %d\n", i);

        printf("Enter the start coordinate: ");
        scanf(" %s", startInput);
        letter = startInput[0];
        putchar(letter);
        start[0] = toupper(letter) - 'A';
        putchar(start[0]);
        start[1] = startInput[1] - '0';

        printf("\nEnter the end coordinates: ");
        scanf(" %s", endInput);
        letter = endInput[0];
        putchar(letter);
        end[0] = toupper(letter) - 'A';
        putchar(end[0]);
        end[1] = endInput[1] - '0';

        printf("start:%d,%d  End:%d,%d  i:%d", start[0], start[1], end[0], end[1], i);
        placed = placeShip(i, start, end, board);
        placed ? i++ : printf("\nThere is a problem with the coordinates provided, try again");
    }
} 
