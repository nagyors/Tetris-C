#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

#include "Block.h"
#include "econio.h"
#include "board.h"
#include "debugmalloc.h"


typedef struct Toplist{ //toplista
    char name[51];
    int rank;
    int score;
}Toplist;

void display(int **board, int width, int height);//ha a board tombben 0 van akkor az kocka ures, ha egy akkor ott van egy forma
void blockspawn(int **board, struct block *block); //egy block tipust spawnol a palyara
void show_nextblock(struct block block, int width, int height); //a kovetkezo blockot kiirja a kepernyore
void show_nextblock_clear(int width, int height); //eltorli az elozo kovetkezo blockot a kepernyorol

void makeboarder(int width, int height){ //megcsinalja a palya keretet
    for(int i = 1; i < width-1; i++){
        econio_gotoxy(i,0);
        printf("-");
        econio_gotoxy(i,height-1);
        printf("-");
    }
    for(int i = 1; i < height-1; i++){
        econio_gotoxy(0,i);
        printf("|");
        econio_gotoxy(width-1,i);
        printf("|");
    }
}

void make_nextblock_boarder(int width, int height){ //megcsinalja a nextblock helysegnek a keretet
    for(int i = width+10; i < width+14; i++){
        econio_gotoxy(i,4);
        printf("-");
        econio_gotoxy(i,8);
        printf("-");
    }
    for(int i = 5; i < 8; i++){
        econio_gotoxy(width+9,i);
        printf("|");
        econio_gotoxy(width+14,i);
        printf("|");
    }
}

int main()
{
    int timeoflevel=100; //mennyit alszik a ciklus(minel kevesebb annal gyorsabb az eses)
    int kbhitfreq=5; //milyen gyakran nezze meg, hogy van-e gomb lenyova
    int width=14;
    int height=18;

    printf("[S]:START\n");
    printf("[H]:help\n");
    printf("[E]:exit\n");//kezdo kepernyo

    bool game=false;
    int key;
    bool help=false;
    econio_rawmode();
    while(1){
        if(econio_kbhit()){
            key = econio_getch();

            if(key == 101) //kilepes
                system("taskkill/IM cb_console_runner.exe");

            if(key == 104){ // sugo
                econio_clrscr();
                help = true;
                break;
            }

            if(key == 115){ //start
                econio_clrscr();
                game=true;
                break;
            }
        }
    }

    printf("The game uses the WASD keys.\n");
    printf("The W key rotates the blocks with 90 degrees, the S key makes");
    printf("them fall faster and the A and the D moves them to the left and the right.\n");
    printf("If you press r during the game, it will restart.\n");
    printf("[S]:Press s to start\n");

    while(help){
        if(econio_kbhit()){
            key=econio_getch();
            if(key == 115){
                econio_clrscr();
                game=true;
                break;
            }
        }
    }

    econio_clrscr();

    int **board = (int**)malloc(sizeof(int*) * width);
	for (int i = 0; i < width; i++)
		board[i] = (int*)malloc(sizeof(int*) * height);
restart:
	for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            if(i == 0 || j == 0 || i == width-1 || j == height-1)
                board[i][j]=1;
            else
                board[i][j]=0;
        }
	}

    makeboarder(width,height);
    make_nextblock_boarder(width,height);
    econio_gotoxy(width,4);
    printf("NEXTBLOCK:");

    struct block block;
    block.type = rand() % 7;
    blockspawn(board, &block);

    blocktoone(&block,board);

    struct block nextblock;
    nextblock.state=normal;

    do{
        nextblock.type = rand() %7;
    }while(nextblock.type == block.type);

    int blockcounter=0;
    int level=1;
    int score=0;

    econio_gotoxy(width,height);
    printf("r to restart");

    while(game){
        display(board,width,height);
        show_nextblock(nextblock,width,height);

        econio_gotoxy(width,1);
        printf("LEVEL: %d",level);
        econio_gotoxy(width,2);
        printf("SCORE: %d",score);

        for(int i = 0; i < timeoflevel; i++){
            if(econio_kbhit()){
                key=econio_getch();

                blocktozero(&block,board);

                econio_gotoxy(block.a.x,block.a.y);
                printf(" ");
                econio_gotoxy(block.b.x,block.b.y);
                printf(" ");
                econio_gotoxy(block.c.x,block.c.y);
                printf(" ");
                econio_gotoxy(block.d.x,block.d.y);
                printf(" ");

                if(key == 97 || key == 65){// balra mogatas
                    if(board[block.a.x-1][block.a.y] == 0 && board[block.b.x-1][block.b.y] == 0 &&
                       board[block.c.x-1][block.c.y] == 0 && board[block.d.x-1][block.d.y] == 0)
                    {
                        block.a.x--;
                        block.b.x--;
                        block.c.x--;
                        block.d.x--;
                    }
                }
                if(key == 100 || key == 68){//jobbra mozgatas
                    if(board[block.a.x+1][block.a.y] == 0 && board[block.b.x+1][block.b.y] == 0 &&
                       board[block.c.x+1][block.c.y] == 0 && board[block.d.x+1][block.d.y] == 0){
                        block.a.x++;
                        block.b.x++;
                        block.c.x++;
                        block.d.x++;
                    }
                }
                if(key == 115 || key == 83){//lefele gyorsit
                    if(board[block.c.x][block.c.y+1] == 0 && board[block.c.x][block.c.y+2] == 0){
                        block.a.y++;
                        block.b.y++;
                        block.c.y++;
                        block.d.y++;

                        score +=2;
                    }
                }
                if(key == 87 || key == 119){//forgatas
                    switch(block.type){
                    case 0: ///Vonal forma
                        linerotater(&block,board);
                        break;
                    case 2: ///L forma
                        Lrotater(&block,board);
                        break;
                    case 3: ///J forma
                        Jrotater(&block,board);
                        break;
                    case 4: ///T forma
                        Trotater(&block,board);
                        break;
                    case 5: ///S forma
                        Srotater(&block,board);
                        break;
                    case 6: ///Z forma
                        Zrotater(&block,board);
                        break;
                    }
                }

                if(key == 27)//kilepes
                    goto finally;

                if(key == 114){//ujrakezd
                    econio_clrscr();
                    goto restart;
                }

                blocktoone(&block,board);
                display(board,width,height);

            }
            Sleep(kbhitfreq);
        }
        if(collision_check(block,board)){ // ha leesik a block ez fog tortenni
                if(block.a.y < 4)
                    game=false;
                if(level != 15){
                    if(blockcounter == 4){
                        blockcounter=0;
                        timeoflevel -=10;
                        level++;
                    }
                }

                blockcounter++;

                block = nextblock;
                blockspawn(board, &block);
                do{
                nextblock.type = rand() %7;
                }while(nextblock.type == block.type);

                int multipler = 1; //szorzo, egyszeri tobb sor eltuntetese eseten a tobb pontot kap a felhasznalo
                for(int i = 1; i < height-1; i++){
                    bool ok=true;
                    for(int j = 1; j < width-1; j++){
                        if(board[j][i] == 0)
                            ok=false;
                    }
                    if(ok){
                        rowdeleter(board,i,width,&score,multipler);
                        fall_one(board,i,width);
                        multipler++;
                    }
                }

                display(board,width,height);
        }
        else{
            econio_gotoxy(block.a.x,block.a.y);
            printf(" ");
            econio_gotoxy(block.b.x,block.b.y);
            printf(" ");
            econio_gotoxy(block.c.x,block.c.y);
            printf(" ");
            econio_gotoxy(block.d.x,block.d.y);
            printf(" ");

            blocktozero(&block,board);

            block.a.y++;
            block.b.y++;
            block.c.y++;
            block.d.y++;

            blocktoone(&block,board);
        }

        show_nextblock_clear(width,height);
    }

    FILE *fp;
    fp = fopen("toplist.txt", "r");

    if(fp == NULL){
        perror("Fájl megnyitása sikertelen");
        return;
    }
    econio_clrscr();

    Toplist tp[10];
    for(int i = 0; i < 10;i++){
        fscanf(fp,"%d %s %d" ,&tp[i].rank, tp[i].name, &tp[i].score);
    }

    if(score>= tp[9].score){ //hozza adja az uj eredmeny a toplistahoz
        char s[21];
        printf("Your name:");
        scanf("%s",s);
        int i=8;
        while(score > tp[i].score && i != 0)
            i--;
        i++;
        for(int j = 9; j >= i; j--){
            tp[j].score=tp[j-1].score;
            strcpy(tp[j].name,tp[j-1].name);
        }
        tp[i].score=score;
        tp[i].rank= i+1;
        strcpy(tp[i].name,s);
    }

    printf("Your score: %d\n", score);
    printf("Toplist:\n");
    for(int i = 0; i < 10; i++)
        printf("%d. %s's score: %d\n", tp[i].rank, tp[i].name, tp[i].score);

    fclose(fp);

    fp = fopen("toplist.txt", "wt");
    if(fp == NULL){
        perror("Fájl megnyitása sikertelen");
        return;
    }

    for(int i = 0; i < 10; i++)
        fprintf(fp,"%d %s %d\n" , tp[i].rank, tp[i].name, tp[i].score);

    fclose(fp);

finally:
    for (int i = 0; i < width; i++)
		free(board[i]);
	free(board);

    return 0;
}


void display(int **board, int width, int height){
    for(int i = 1; i < width-1; i++){
        for(int j = 1; j < height-1; j++){
            if(board[i][j] == 1){
                char kocka=254;
                econio_gotoxy(i,j);
                printf("X");
            }
        }
    }
}

void blockspawn(int **board, struct block *block){
    switch(block->type){
        case 0: ///vonal
            block->a.x=5;
            block->a.y=1;
            block->b.x=6;
            block->b.y=1;
            block->c.x=7;
            block->c.y=1;
            block->d.x=8;
            block->d.y=1;
            break;
        case 1: ///Oforma
            block->a.x=6;
            block->a.y=1;
            block->b.x=7;
            block->b.y=1;
            block->c.x=6;
            block->c.y=2;
            block->d.x=7;
            block->d.y=2;
            break;
        case 2: ///Lforma
            block->a.x=7;
            block->a.y=1;
            block->b.x=7;
            block->b.y=2;
            block->c.x=7;
            block->c.y=3;
            block->d.x=8;
            block->d.y=3;
            break;
        case 3: ///Jforma
            block->a.x=7;
            block->a.y=1;
            block->b.x=7;
            block->b.y=2;
            block->c.x=7;
            block->c.y=3;
            block->d.x=6;
            block->d.y=3;
            break;
        case 4: ///Tforma
            block->a.x=7;
            block->a.y=1;
            block->b.x=6;
            block->b.y=2;
            block->c.x=7;
            block->c.y=2;
            block->d.x=8;
            block->d.y=2;
            break;
        case 5: ///Sforma
            block->a.x=7;
            block->a.y=1;
            block->b.x=8;
            block->b.y=1;
            block->c.x=6;
            block->c.y=2;
            block->d.x=7;
            block->d.y=2;
            break;
        case 6: ///Zforma
            block->a.x=6;
            block->a.y=1;
            block->b.x=7;
            block->b.y=1;
            block->c.x=7;
            block->c.y=2;
            block->d.x=8;
            block->d.y=2;
            break;
    }

    block->state = normal;
}

void show_nextblock(struct block block, int width, int height){
    switch(block.type){
    case 0: ///vonal
        econio_gotoxy(width+10, 6);
        printf("X");
        econio_gotoxy(width+11, 6);
        printf("X");
        econio_gotoxy(width+12, 6);
        printf("X");
        econio_gotoxy(width+13, 6);
        printf("X");
        break;
    case 1: ///O forma
        econio_gotoxy(width+11, 6);
        printf("X");
        econio_gotoxy(width+12, 6);
        printf("X");
        econio_gotoxy(width+11, 7);
        printf("X");
        econio_gotoxy(width+12, 7);
        printf("X");
        break;
    case 2: ///L  forma
        econio_gotoxy(width+11, 5);
        printf("X");
        econio_gotoxy(width+11, 6);
        printf("X");
        econio_gotoxy(width+11, 7);
        printf("X");
        econio_gotoxy(width+12, 7);
        printf("X");
        break;
    case 3: ///J forma
        econio_gotoxy(width+12, 5);
        printf("X");
        econio_gotoxy(width+12, 6);
        printf("X");
        econio_gotoxy(width+12, 7);
        printf("X");
        econio_gotoxy(width+11, 7);
        printf("X");
        break;
    case 4: ///T forma
        econio_gotoxy(width+12, 6);
        printf("X");
        econio_gotoxy(width+11, 7);
        printf("X");
        econio_gotoxy(width+12, 7);
        printf("X");
        econio_gotoxy(width+13, 7);
        printf("X");
        break;
    case 5: ///S forma
        econio_gotoxy(width+11, 6);
        printf("X");
        econio_gotoxy(width+12, 6);
        printf("X");
        econio_gotoxy(width+10, 7);
        printf("X");
        econio_gotoxy(width+11, 7);
        printf("X");
        break;
    case 6: ///Z forma
        econio_gotoxy(width+10, 6);
        printf("X");
        econio_gotoxy(width+11, 6);
        printf("X");
        econio_gotoxy(width+11, 7);
        printf("X");
        econio_gotoxy(width+12, 7);
        printf("X");
        break;
    }
}

void show_nextblock_clear(int width, int height){
    for(int i = width+10; i < width + 14; i++){
        for(int j = 5; j < 8; j++){
            econio_gotoxy(i,j);
            printf(" ");
        }
    }
}


