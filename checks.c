#define BOARD_SIZE 10


int checkAlive(char board[BOARD_SIZE][BOARD_SIZE]){
    char pos;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            pos = board[i][j];
            if(pos == '2' || pos == '3' || pos == '4' || pos == '5'){
                return 1;
            }
        }
    }
    return 0;
}



int checkShipSunk(char board[BOARD_SIZE][BOARD_SIZE], char hitShip){
    char pos;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            pos = board[i][j];
            if(pos == hitShip){
                return 0;
            }
        }
    }
    return 1;
}