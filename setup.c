#include <time.h>
#define BOARD_SIZE 10


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
        if(board[ship[i][0]][ship[i][1]] != '0'){
            return 0;
        } 
    }

    for(int i = 0; i < shipSize; i++){
        board[ship[i][0]][ship[i][1]] = shipSize + '0';
    }

    return 1;
}





void generateEnemyShips(char enemyBoard[BOARD_SIZE][BOARD_SIZE]){

    time_t t;
    srand(time(&t));
    int direction;
    int start[2];
    int end[2];
    int i = 2;
    int placed = 0;

    while(i < 6){

        end[0] = -1;
        end[1] = -1;
        direction = rand() % 4;
        placed = 0;
        
        switch(direction){
            case 0:
                while(end[1] < 0 || end[1] >= BOARD_SIZE){
                    end[0] = start[0] = rand() % BOARD_SIZE;
                    start[1] = rand() % BOARD_SIZE;
                    end[1] = start[1] - (i-1);
                }
                break;
            case 1:
                while(end[0] < 0 || end[0] >= BOARD_SIZE){
                    end[1] = start[1] = rand() % BOARD_SIZE;
                    start[0] = rand() % BOARD_SIZE;
                    end[0] = start[0] + (i-1);
                }
                break;
            case 2:
                while(end[1] < 0 || end[1] >= BOARD_SIZE){
                    end[0] = start[0] = rand() % BOARD_SIZE;
                    start[1] = rand() % BOARD_SIZE;
                    end[1] = start[1] + (i-1);
                }
                break;
            case 3:
                while(end[0] < 0 || end[0] >= BOARD_SIZE){
                    end[1] = start[1] = rand() % BOARD_SIZE;
                    start[0] = rand() % BOARD_SIZE;
                    end[0] = start[0] - (i-1);
                }
                break;
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
    int error = 0;

    printf("\n\nLets put down four ships\n");
    printf("Enter the coordinates for the start and end of each ship\n");
    printf("The coordinates need to be the correct distance apart\n");
    printf("You also need to enter them as letter then number\n");
    printf("For example: a ship of length 3 could have coordinates A1 to A3\n");
    
    while(i<6){
        placed = 0;
        printBoards(board, shootingBoard);

        if(error == 1){
            printf("\nThere is a problem with the coordinates provided, try again\n");
        }
        error = 0;
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

        printf("Enter the end coordinates: ");
        scanf(" %s", endInput);
        letter = endInput[0];
        end[0] = toupper(letter) - 'A';
        if(endInput[1] == '1' && endInput[2] == '0'){
            end[1] = 9;
        } else {
            end[1] = (endInput[1] - '0') - 1;
        }
        
        placed = placeShip(i, start, end, board);
        placed ? i++ : (error = 1); 
    }
} 