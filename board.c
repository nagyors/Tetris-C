#include "board.h"

void rowdeleter(int **board,int row, int width, int *score, int multipler){
    for(int i = 1; i < width-1; i++){
        board[i][row] = 0;
        econio_gotoxy(i,row);
        printf(" ");
    }

    *score += 100 * multipler;
}

void fall_one(int **board,int row, int width){
    for(int i = row; i > 2; i--){
        for(int j = 1; j < width-1; j++){
            if(board[j][i] == 1){
                econio_gotoxy(j,i);
                printf(" ");
            }
            board[j][i] = board[j][i-1];
        }
    }
}
