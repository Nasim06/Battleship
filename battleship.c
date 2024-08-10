#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h> 
#include <unistd.h>
#include "consoleOutput.c"
#include "setup.c"

#define BOARD_SIZE 10

char displayTitle();
void printBoards(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]);
int placeShip(int shipSize, int x[2], int y[2], char board[BOARD_SIZE][BOARD_SIZE]);
void setupShips(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]);
void generateEnemyShips(char enemyBoard[BOARD_SIZE][BOARD_SIZE]);
void printSingleBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void clearScreen();



int main(){

    char enemyBoard[BOARD_SIZE][BOARD_SIZE];
    char shootingBoard[BOARD_SIZE][BOARD_SIZE];
    char board[BOARD_SIZE][BOARD_SIZE];
    char wantsToPlay;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            board[i][j] = '0';
            shootingBoard[i][j] = '0';
            enemyBoard[i][j] = '0';
        }
    }

    generateEnemyShips(enemyBoard);
    printSingleBoard(enemyBoard);
    wantsToPlay = displayTitle();

    if(wantsToPlay == 'Y'){
        printf("\nlets play\n\n");
        setupShips(board, shootingBoard);
        printBoards(board, shootingBoard);
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

