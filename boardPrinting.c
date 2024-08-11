#define BOARD_SIZE 10


void printBoards(char board[BOARD_SIZE][BOARD_SIZE], char shootingBoard[BOARD_SIZE][BOARD_SIZE]){
    
    char to_red[] = "\033[31m";
    char to_green[] = "\033[32m";
    char to_yellow[] = "\033[33m";
    char to_white[] = "\033[0m";

    printf("\n   Your Board                     Shooting Board\n");
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
            if(elem == '2' || elem == '3' || elem == '4' || elem == '5'){
                printf(" %s%c%s", to_green, 'S', to_white);
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



void printSingleBoard(char board[BOARD_SIZE][BOARD_SIZE]){

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
            if(elem == 'M'){
                printf(" %s%c%s", to_yellow, elem, to_white);
            }
            if(elem != 'H' && elem != 'S' && elem != 'M'){
                printf(" %c", elem);   
            }
        }
        printf("\n");
    }

}