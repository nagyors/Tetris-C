#include "Block.h"

bool collision_check(struct block block, int **board){ ///Megnezi hogy erintkezik-e valamivel
    switch(block.type){
    case 0: /// vonal
        if(block.state == left && board[block.d.x][block.d.y+1] == 1)
            return true;
        else{
            if(block.state == normal && (board[block.a.x][block.a.y+1] == 1 || board[block.b.x][block.b.y+1] == 1 ||
                                         board[block.c.x][block.c.y+1] == 1 || board[block.d.x][block.d.y+1] == 1))
                return true;
        }
        return false;
        break;
    case 1: /// Oforma
        if(board[block.c.x][block.c.y+1] == 1 || board[block.d.x][block.d.y+1] == 1)
            return true;
        return false;
        break;
    case 2: /// Lforma
        switch(block.state){
        case normal:
            if(board[block.c.x][block.c.y +1] == 1 || board[block.d.x][block.d.y +1] == 1)
                return true;
            return false;
            break;
        case left:
            if(board[block.a.x][block.a.y +1] == 1 || board[block.b.x][block.b.y +1] == 1 ||
               board[block.d.x][block.d.y +1] == 1)
                return true;
            return false;
            break;
        case right:
            if(board[block.a.x][block.a.y +1] == 1 || board[block.b.x][block.b.y +1] == 1 ||
               board[block.c.x][block.c.y +1] == 1 )
                return true;
            return false;
            break;
        case upsd:
            if(board[block.a.x][block.a.y +1] == 1 || board[block.d.x][block.d.y +1] == 1)
                return true;
            return false;
            break;
        }
        break;
    case 3: /// Jforma
        switch(block.state){
        case normal:
            if(board[block.c.x][block.c.y +1] == 1 || board[block.d.x][block.d.y +1] == 1)
                return true;
            return false;
            break;
        case left:
            if(board[block.a.x][block.a.y +1] == 1 || board[block.b.x][block.b.y +1] == 1 ||
               board[block.c.x][block.c.y +1] == 1)
                return true;
            return false;
            break;
        case right:
            if(board[block.a.x][block.a.y +1] == 1 || board[block.b.x][block.b.y +1] == 1 ||
               board[block.d.x][block.d.y +1] == 1 )
                return true;
            return false;
            break;
        case upsd:
            if(board[block.a.x][block.a.y +1] == 1 || board[block.d.x][block.d.y +1] == 1)
                return true;
            return false;
            break;
        }
        break;
    case 4: /// Tforma
        switch(block.state){
        case normal:
            if(board[block.b.x][block.b.y+1] == 1 || board[block.c.x][block.c.y+1] == 1 ||
               board[block.d.x][block.d.y+1] == 1)
                return true;
            return false;
            break;
        case left:
            if(board[block.a.x][block.a.y+1] == 1 || board[block.d.x][block.d.y+1] == 1)
                return true;
            return false;
            break;
        case right:
            if(board[block.a.x][block.a.y+1] == 1 || board[block.b.x][block.b.y+1] == 1)
                return true;
            return false;
            break;
        case upsd:
            if(board[block.a.x][block.a.y+1] == 1 || board[block.b.x][block.b.y+1] == 1 ||
               board[block.d.x][block.d.y+1] == 1)
                return true;
            return false;
            break;
        }
        break;
    case 5: /// Sforma
        switch(block.state){
        case normal:
            if(board[block.b.x][block.b.y+1] == 1 || board[block.c.x][block.c.y+1] == 1 ||
               board[block.d.x][block.d.y+1] == 1)
                return true;
            return false;
            break;
        case left:
            if(board[block.a.x][block.a.y+1] == 1 || board[block.d.x][block.d.y+1] == 1)
                return true;
            return false;
            break;
        }
        break;
    case 6: /// Zforma
        switch(block.state){
        case normal:
            if(board[block.a.x][block.a.y+1] == 1 || board[block.c.x][block.c.y+1] == 1 ||
               board[block.d.x][block.d.y+1] == 1)
                return true;
            return false;
            break;
        case left:
            if(board[block.b.x][block.b.y+1] == 1 || board[block.d.x][block.d.y+1] == 1)
                return true;
            return false;
            break;
        }
        break;
    }
}

void blocktozero(struct block *block, int **board){ ///A tombben forma koordinatait 0ra allitja
    board[block->a.x][block->a.y] = 0;
    board[block->b.x][block->b.y] = 0;
    board[block->c.x][block->c.y] = 0;
    board[block->d.x][block->d.y] = 0;
}

void blocktoone(struct block *block, int **board){ ///A tombben forma koordinatait 1re allitja
    board[block->a.x][block->a.y] = 1;
    board[block->b.x][block->b.y] = 1;
    board[block->c.x][block->c.y] = 1;
    board[block->d.x][block->d.y] = 1;
}

void linerotater(struct block *block, int **board){ ///vonal format forgat
    switch(block->state){
    case normal: ///vizszintes
        if(board[block->c.x][block->c.y-2] == 0 && board[block->c.x][block->c.y-1] == 0 &&
           board[block->c.x][block->c.y+1] == 0){
            block->a.x = block->c.x;
            block->b.x = block->c.x;
            block->d.x = block->c.x;

            block->a.y = block->c.y - 2;
            block->b.y = block->c.y - 1;
            block->d.y = block->c.y + 1;

            block->state = left;
        }
        break;
    case left: /// fuggoleges
        if(board[block->c.x-2][block->c.y] == 0 && board[block->c.x-1][block->c.y] == 0 &&
           board[block->c.x+1][block->c.y] == 0){
            block->a.y = block->c.y;
            block->b.y = block->c.y;
            block->d.y = block->c.y;

            block->a.x = block->c.x - 2;
            block->b.x = block->c.x - 1;
            block->d.x = block->c.x + 1;

            block->state = normal;
        }
        break;
    }
}

void Lrotater(struct block *block, int **board){ ///L format forgat
    switch(block->state){
    case normal:
        if(board[block->a.x+1][block->a.y] == 0 && board[block->a.x+1][block->a.y] == 0 &&
           board[block->a.x+1][block->a.y+1] == 0)
        {
            block->b.x = block->a.x;
            block->c.x = block->b.x - 1;
            block->a.x = block->a.x + 1;
            block->d.x = block->c.x;

            block->b.y = block->a.y;
            block->c.y = block->a.y;
            block->d.y = block->a.y + 1;

            block->state = left;

        }
        break;
    case left:
        if(board[block->b.x][block->b.y+1] == 0 && board[block->b.x][block->b.y+2] == 0)
        {
            block->a.x = block->b.x;
            block->c.x = block->b.x;

            block->b.y = block->b.y + 1;
            block->a.y = block->b.y + 1;
            block->d.y = block->d.y - 1;

            block->state = upsd;
        }
        break;
    case upsd:
        if(board[block->b.x-1][block->b.y] == 0 && board[block->b.x+1][block->b.y] == 0 &&
           board[block->b.x+1][block->b.y-1] == 0)
        {
            block->a.x = block->b.x - 1;
            block->c.x = block->b.x + 1;
            block->d.x = block->b.x + 1;

            block->a.y = block->b.y;
            block->c.y = block->b.y;
            block->d.y = block->b.y -1;

            block->state = right;
        }
        break;
    case right:
        if(board[block->b.x][block->b.y-1] == 0 && board[block->b.x][block->b.y+1] == 0 &&
           board[block->b.x+1][block->b.y+1] == 0)
        {
            block->a.x = block->b.x;
            block->c.x = block->b.x;
            block->d.x = block->b.x + 1;

            block->a.y = block->b.y - 1;
            block->c.y = block->b.y + 1;
            block->d.y = block->b.y + 1;

            block->state = normal;
        }
        break;
    }
}

void Jrotater(struct block *block, int **board){ ///J forma forgat
    switch(block->state){
    case normal:
        if(board[block->b.x-1][block->b.y] == 0 && board[block->b.x+1][block->b.y] == 0 &&
           board[block->b.x-1][block->b.y-1] == 0)
        {
            block->a.x = block->b.x + 1;
            block->c.x = block->b.x - 1;
            block->d.x = block->b.x - 1;

            block->a.y = block->b.y;
            block->c.y = block->b.y;
            block->d.y = block->b.y - 1;

            block->state = left;
        }
        break;
    case left:
        if(board[block->b.x][block->b.y+1] == 0 && board[block->b.x][block->b.y-1] == 0 &&
           board[block->b.x+1][block->b.y-1] == 0)
        {
            block->a.x = block->b.x;
            block->c.x = block->b.x;
            block->d.x = block->b.x +1;

            block->a.y = block->b.y + 1;
            block->c.y = block->b.y - 1;
            block->d.y = block->b.y - 1;

            block->state = upsd;
        }
        break;
    case upsd:
        if(board[block->b.x-1][block->b.y] == 0 && board[block->b.x+1][block->b.y] == 0 &&
           board[block->b.x+1][block->b.y+1] == 0)
        {
            block->a.x = block->b.x - 1;
            block->c.x = block->b.x + 1;
            block->d.x = block->b.x + 1;

            block->a.y = block->b.y;
            block->c.y = block->b.y;
            block->d.y = block->b.y + 1;

            block->state = right;
        }
        break;
    case right:
        if(board[block->b.x][block->b.y-1] == 0 && board[block->b.x][block->b.y+1] == 0 &&
           board[block->b.x-1][block->b.y+1] == 0)
        {
            block->a.x = block->b.x;
            block->c.x = block->b.x;
            block->d.x = block->b.x - 1;

            block->a.y = block->b.y - 1;
            block->c.y = block->b.y + 1;
            block->d.y = block->b.y + 1;

            block->state = normal;
        }
        break;
    }
}

void Trotater(struct block *block, int **board){ ///T forma forgat
    switch(block->state){
    case normal:
        if(board[block->c.x][block->c.y+1] == 0)
        {
            block->a.x = block->c.x + 1;
            block->b.x = block->c.x;
            block->d.x = block->c.x;

            block->a.y = block->c.y;
            block->b.y = block->c.y - 1;
            block->d.y = block->c.y + 1;

            block->state = left;
        }
        break;
    case left:
        if(board[block->c.x-1][block->c.y] == 0)
        {
            block->a.x = block->c.x;
            block->b.x = block->c.x + 1;
            block->d.x = block->c.x - 1;

            block->a.y = block->c.y + 1;
            block->b.y = block->c.y;
            block->d.y = block->c.y;

            block->state = upsd;
        }
        break;
    case upsd:
        if(board[block->c.x][block->c.y-1] == 0)
        {
            block->a.x = block->c.x - 1;
            block->b.x = block->c.x;
            block->d.x = block->c.x;

            block->a.y = block->c.y;
            block->b.y = block->c.y + 1;
            block->d.y = block->c.y - 1;

            block->state = right;
        }
        break;
    case right:
        if(board[block->c.x+1][block->c.y] == 0)
        {
            block->a.x = block->c.x;
            block->b.x = block->c.x - 1;
            block->d.x = block->c.x + 1;

            block->a.y = block->c.y - 1;
            block->b.y = block->c.y;
            block->d.y = block->c.y;

            block->state = normal;
        }
        break;
    }
}

void Srotater(struct block *block, int **board){ ///S forma forgat
    switch(block->state){
    case normal:
        if(board[block->c.x][block->c.y-1] == 0 && board[block->d.x][block->d.y+1] == 0)
        {
            block->b.x = block->a.x;
            block->d.x = block->c.x;

            block->a.y = block->d.y + 1;
            block->b.y = block->d.y;
            block->c.y = block->d.y - 1;

            block->state = left;
        }
        break;
    case left:
        if(board[block->b.x][block->b.y-1] == 0 && board[block->b.x+1][block->b.y-1] == 0)
        {
            block->b.x = block->a.x + 1;
            block->d.x = block->c.x + 1;

            block->a.y = block->b.y - 1;
            block->b.y = block->a.y;
            block->c.y = block->d.y;

            block->state = normal;
        }
        break;
    }
}

void Zrotater(struct block *block, int **board){ ///Z forma forgat
    switch(block->state){
    case normal:
        if(board[block->d.x][block->d.y-1] == 0 && board[block->c.x][block->c.y+1] == 0)
        {
            block->b.x = block->d.x;
            block->a.x = block->d.x;
            block->d.x = block->c.x;

            block->a.y = block->d.y - 1;
            block->b.y = block->d.y;
            block->d.y = block->c.y + 1;

            block->state = left;
        }
        break;
    case left:
        if(board[block->c.x][block->c.y-1] == 0 && board[block->c.x-1][block->c.y-1] == 0)
        {
            block->b.x = block->c.x;
            block->d.x = block->c.x + 1;
            block->a.x = block->c.x - 1;

            block->b.y = block->c.y - 1;
            block->d.y = block->c.y;

            block->state = normal;
        }
        break;
    }
}



