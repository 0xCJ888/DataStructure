#ifndef __CARD_H__
#define __CARD_H__

#include <stdlib.h>
#include <stdio.h>
#include "hiredis.h"

#define totalCardNum 52
#define textSize 3

typedef struct card Card;
struct card{
    char suitNum;
    char suitName[4];
    char suitSymbol;
    char value;
    char rankNum;
};

void createCards(redisContext *c);
void checkDeck(redisContext *c);
void cardtext(const char cardNum, char *text, char *suitNum, char *rankNum);
uint8_t findcardNum(char *text);
uint8_t findcardSuit(char *text);

#endif