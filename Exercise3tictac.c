#include <stdio.h>

void board(int, int);
int checkWin();

char square[3][3] = {{'\40', '\40', '\40'}, {'\40', '\40', '\40'}, {'\40', '\40', '\40'}};
// 40 is octal for 32, which is the ASCII value for blank spaces

int main(){
    int turn = 1, row, col;
    int winCheck = checkWin();
    while(winCheck == 0){
        board(turn, winCheck);
        do{
            printf("Row: ");
            scanf("%i", &row);
        }while(row < 1 || row > 3);
        do{
            printf("Column: ");
            scanf("%i", &col);
        }while(col < 1 || col > 3);
        if(square[row - 1][col - 1] == '\40'){
            if(turn % 2 != 0)
                square[row - 1][col - 1] = 'X';
            else
                square[row - 1][col - 1] = 'O';
            turn++;
            winCheck = checkWin();
        }else{
            printf("(%i, %i) occupied!\n", row, col);
        }
    }
    board(turn, winCheck);
    return 0;
}

void board(int turn, int winCheck){
    printf("\n");
    printf(" %c | %c | %c \n", square[0][0], square[0][1], square[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", square[1][0], square[1][1], square[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", square[2][0], square[2][1], square[2][2]);
    if(winCheck == 0){
        if(turn % 2 != 0)
            printf("X's turn\n\n");
        else
            printf("O's turn\n\n");
    }else if(winCheck == 1){
        if(turn % 2 == 0)
            printf("X wins!\n\n");
        else
            printf("O wins!\n\n");
    }else{
        printf("Draw\n\n");
    }
}

int checkWin(){
    if((square[0][0] == 'X' && square[0][1] == 'X' && square[0][2] == 'X') ||
        (square[0][0] == 'O' && square[0][1] == 'O' && square[0][2] == 'O'))
        return 1;
    else if((square[1][0] == 'X' && square[1][1] == 'X' && square[1][2] == 'X') ||
        (square[1][0] == 'O' && square[1][1] == 'O' && square[1][2] == 'O'))
        return 1;
    else if((square[2][0] == 'X' && square[2][1] == 'X' && square[2][2] == 'X') ||
        (square[2][0] == 'O' && square[2][1] == 'O' && square[2][2] == 'O'))
        return 1;
    else if((square[0][0] == 'X' && square[1][0] == 'X' && square[2][0] == 'X') ||
        (square[0][0] == 'O' && square[1][0] == 'O' && square[2][0] == 'O'))
        return 1;
    else if((square[0][1] == 'X' && square[1][1] == 'X' && square[2][1] == 'X') ||
        (square[0][1] == 'O' && square[1][1] == 'O' && square[2][1] == 'O'))
        return 1;
    else if((square[0][2] == 'X' && square[1][2] == 'X' && square[2][2] == 'X') ||
        (square[0][2] == 'O' && square[1][2] == 'O' && square[2][2] == 'O'))
        return 1;
    else if((square[0][0] == 'X' && square[1][1] == 'X' && square[2][2] == 'X') ||
        (square[0][0] == 'O' && square[1][1] == 'O' && square[2][2] == 'O'))
        return 1;
    else if((square[0][2] == 'X' && square[1][1] == 'X' && square[2][0] == 'X') ||
        (square[0][2] == 'O' && square[1][1] == 'O' && square[2][0] == 'O'))
        return 1;
    else if(square[0][0] != '\40' && square[0][1] != '\40' && square[0][2] != '\40' &&
        square[1][0] != '\40' && square[1][1] != '\40' && square[1][2] != '\40' &&
        square[2][0] != '\40' && square[2][1] != '\40' && square[2][2] != '\40')
        return 2;
    else
        return 0;
}