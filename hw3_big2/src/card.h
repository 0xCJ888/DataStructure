#ifndef __CARD_H__
#define __CARD_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>


#define totalCardNum 52
#define wishTime 10000
#define textSize 3

#define swap(a,b)            \
    do{                      \
        Card tmp;            \
        tmp = a;             \
        a = b;               \
        b = tmp;             \
    }while(0)

typedef struct card Card;
struct card{
    char suit;
    char suitName;
    char suitSymbol;
    char rankNum;
    char rankName;
};

Card* shuffle(void);
void cardtext(char card, char* text);

#endif