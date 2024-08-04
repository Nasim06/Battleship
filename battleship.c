#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h> 

#define BOARD_SIZE 10

char displayTitle();
void renderBoard(char board[BOARD_SIZE][BOARD_SIZE]);
int placeShip(int shipSize, int x[2], int y[2], char board[BOARD_SIZE][BOARD_SIZE]);


int enemyBoard[BOARD_SIZE][BOARD_SIZE] = {0};

int main(){

    char board[BOARD_SIZE][BOARD_SIZE];
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            board[i][j] = '0';
        }
    }

    //testing placing ships
    int x[2] = {3,2};
    int y[2] = {3,4};

    placeShip(3, x, y, board);

    int x2[2] = {5,4};
    int y2[2] = {9,4};

    placeShip(5, x2, y2, board);

    char wantsToPlay;
    wantsToPlay = displayTitle();
    if(wantsToPlay == 'Y'){
        printf("\nlets play\n\n");
        renderBoard(board);
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


void renderBoard(char board[BOARD_SIZE][BOARD_SIZE]){
    
    char to_red[] = "\033[31m";
    char to_green[] = "\033[32m";
    char to_yellow[] = "\033[33m";
    char to_white[] = "\033[0m";

    printf("   A B C D E F G H I J\n");
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
        printf("\n");
    }
}


int placeShip(int shipSize, int start[2], int end[2], char board[BOARD_SIZE][BOARD_SIZE]){
    
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
                board[x1][y1 + i] = 'S';
            } else{
                board[x1][y1 - i] = 'S';
            }
        }
        if(y1 == y2){
            if(x1 < x2){
                board[x1 + i][y1] = 'S';
            } else{
                board[x1 - i][y1] = 'S';
            }
        }
    }
    return 1;
}

