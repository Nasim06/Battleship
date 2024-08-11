#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h> 
#include <unistd.h>
#include "boardPrinting.c"
#include "setup.c"
#include "checks.c"

#define BOARD_SIZE 10

void displayTitle();
void printBoards(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]);
void printSingleBoard(char board[BOARD_SIZE][BOARD_SIZE]);
int placeShip(int shipSize, int x[2], int y[2], char board[BOARD_SIZE][BOARD_SIZE]);
void setupShips(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]);
void generateEnemyShips(char enemyBoard[BOARD_SIZE][BOARD_SIZE]);
int checkAlive(char board[BOARD_SIZE][BOARD_SIZE]);
int checkShipSunk(char board[BOARD_SIZE][BOARD_SIZE], char hitShip);
int fireShot(char enemyboard[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE], char board[BOARD_SIZE][BOARD_SIZE]);
int enemyShoot(char board[BOARD_SIZE][BOARD_SIZE]);


int main(){

    char enemyBoard[BOARD_SIZE][BOARD_SIZE];
    char shootingBoard[BOARD_SIZE][BOARD_SIZE];
    char board[BOARD_SIZE][BOARD_SIZE];
    char wantsToPlay;
    int win = 0;
    int lose = 0;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            board[i][j] = '0';
            shootingBoard[i][j] = '0';
            enemyBoard[i][j] = '0';
        }
    }

    generateEnemyShips(enemyBoard);
    displayTitle();
    setupShips(board, shootingBoard);
    printBoards(board, shootingBoard);
    
    while(!win && !lose){
        lose = enemyShoot(board);
        win = fireShot(enemyBoard, shootingBoard, board);
    }
    if(win){
        printf("\nWell done Player, you have sunk all of the enemies ships");
        printf("\nYou are clearly a brilliant strategist\n");
    }
    if(lose){
        printf("\nUnfortunately the enemy has sunk all of your ships");
        printf("\nYou have lost to a computer, how very sad, \"Alexa play Despacito\"");
    }

    return 0;
}



void displayTitle(){
    char answer;
    printf("\n*****************\n");
    printf("   Battleships   ");
    printf("\n*****************\n\n");
    printf("The tabletop strategy game, brought to you through the power of electricity\n");
    printf("Press a key to play");
    getchar();
}



int fireShot(char enemyboard[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE],
            char board[BOARD_SIZE][BOARD_SIZE]){

    int x, y;
    char pos[4];
    int valid = 0;
    printBoards(board, shootingBoard);
    while(!valid){
        printf("Enter the coordinates of where you want to shoot: ");
        scanf("%s", pos);
        x = toupper(pos[0]) - 'A';
        if(pos[1] == '1' && pos[2] == '0'){
            y = 9;
        } else {
            y = (pos[1] - '0') - 1;
        }

        if(x >= 0 && x <= 9 && y >= 0 && y <= 9){
            valid = 1;
        }else{
            printf("The coordinates you entered are invalid\n");
        }
    }

    char elem = enemyboard[x][y];
    if(elem == '2' || elem == '3' || elem == '4' || elem == '5'){
        enemyboard[x][y] = 'H';
        shootingBoard[x][y] = 'H';
        printf("It's a hit\n");
        int sunk = checkShipSunk(enemyboard,elem);
        if(sunk){
            printf("You have sunk ship %d\n", (elem - '0'));
            return !checkAlive(enemyboard);
        }
    } else{
        if(elem == 'H' || elem == 'M'){
            printf("You've already hit this point, silly billy\n");
        } else{
            printf("That's a miss, chief. Better luck next time\n");
            shootingBoard[x][y] = 'M';
        }
    }
    return 0;
}



int enemyShoot(char board[BOARD_SIZE][BOARD_SIZE]){
    int x, y;
    time_t t;
    srand(time(&t));
    x = rand() % BOARD_SIZE;
    y = rand() % BOARD_SIZE;

    char elem = board[x][y];
    printf("The enemy has fired at [%c, %d]\n", (x + 'A'), (y + 1));
    if(elem == '2' || elem == '3' || elem == '4' || elem == '5'){
        board[x][y] = 'H';
        printf("It's a hit\n");
        int sunk = checkShipSunk(board,elem);
        if(sunk){
            printf("Your ship %d, has been sunk :(\n", (elem - '0'));
            return !checkAlive(board);
        }
    } else{
        if(elem = '0'){
            board[x][y] = 'M';
        }
        printf("The enemy has missed\n");
    }
    return 0;
}