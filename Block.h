#ifndef Block
#define Block

#include <stdio.h>
#include <stdbool.h>

struct point{
	int x;
	int y;
};

typedef enum Rotation{
    normal, //normalis, ahogy spawnol
    right, //jobbra forgatva 90 fokkal
    left, //balra forgatva 90 fokkal
    upsd //fejjel lefele, 180 fokkal forgatva
}Rotation;

struct block{
    //A formanak a 4 negyzetje az a, b, c, d, ezek point tipisuak, hogy legyen x es y valtozojuk
    struct point a;
    struct point b;
    struct point c;
    struct point d;

    int type;
    Rotation state; //forgatas allapota

};

bool collision_check(struct block block, int **board);
void blocktozero(struct block *block, int **board);
void blocktoone(struct block *block, int **board);
void linerotater(struct block *block, int **board);
void Lrotater(struct block *block, int **board);
void Jrotater(struct block *block, int **board);
void Trotater(struct block *block, int **board);
void Srotater(struct block *block, int **board);
void Zrotater(struct block *block, int **board);

#endif // Block
