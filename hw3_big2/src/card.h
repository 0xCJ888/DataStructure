#ifndef __CARD_H__
#define __CARD_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>


#define totalCardNum 52
#define textSize 3

typedef struct card Card;
struct card{
    char suitNum;
    char suitName[3];
    char suitSymbol;
    char value;
    char rankNum;
};

void cardtext(const char cardNum, char *text, char *suitNum, char *rankNum);

#endif