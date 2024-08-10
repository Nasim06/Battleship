#include <time.h>
#define BOARD_SIZE 10

int placeShip(int shipSize, int x[2], int y[2], char board[BOARD_SIZE][BOARD_SIZE]);
void printBoards(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]);


void generateEnemyShips(char enemyBoard[BOARD_SIZE][BOARD_SIZE]){

    time_t t;
    srand(time(&t));
    int direction;
    int start[2];
    int end[2];
    int i = 2;
    int placed = 0;

    while(i < 6){
        start[0] = rand() % BOARD_SIZE;
        start[1] = rand() % BOARD_SIZE;
        direction = rand() % 4;
        placed = 0;

        printf("dir:%d, %d %d\n", direction, start[0], start[1]);

        if(direction == 0){
            end[0] = start[0];
            end[1] = start[1] - (i-1);
            while(end[1] < 0 || end[1] >= BOARD_SIZE){
                start[1] = rand() % BOARD_SIZE;
                end[1] = start[1] - (i-1);
            }
        }
        if(direction == 1){
            end[0] = start[0] + (i-1);
            end[1] = start[1];
            while(end[0] < 0 || end[0] >= BOARD_SIZE){
                start[0] = rand() % BOARD_SIZE;
                end[0] = start[0] + (i-1);
            }
        }
        if(direction == 2){
            end[0] = start[0];
            end[1] = start[1] + (i-1);
            while(end[1] < 0 || end[1] >= BOARD_SIZE){
                start[1] = rand() % BOARD_SIZE;
                end[1] = start[1] + (i-1);
            }
        }
        if(direction == 3){
            end[0] = start[0] - (i-1);
            end[1] = start[1];
            while(end[0] < 0 || end[0] >= BOARD_SIZE){
                start[0] = rand() % BOARD_SIZE;
                end[0] = start[0] - (i-1);
            }
        }
        placed = placeShip(i, start, end, enemyBoard);
        if(placed == 1){
            i++;
        } 
    }
}




void setupShips(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]){
    char startInput[4];
    char endInput[4];
    int start[2];
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
        printBoards(board, shootingBoard);
        printf("For ship of length %d\n", i);

        printf("Enter the start coordinate: ");
        scanf(" %s", startInput);
        letter = startInput[0];
        start[0] = toupper(letter) - 'A';
        if(startInput[1] == '1' && startInput[2] == '0'){
            start[1] = 9;
        } else {
            start[1] = (startInput[1] - '0') - 1;
        }

        printf("\nEnter the end coordinates: ");
        scanf(" %s", endInput);
        letter = endInput[0];
        end[0] = toupper(letter) - 'A';
        if(endInput[1] == '1' && endInput[2] == '0'){
            end[1] = 9;
        } else {
            end[1] = (endInput[1] - '0') - 1;
        }
        
        printf("start:%d,%d  End:%d,%d  i:%d", start[0], start[1], end[0], end[1], i);
        placed = placeShip(i, start, end, board);
        placed ? i++ : printf("\nThere is a problem with the coordinates provided, try again");
    }
} 