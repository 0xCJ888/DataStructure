#ifndef __PRICE_H__
#define __PRICE_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "hiredis.h"

typedef struct _priceData PriceData;
typedef struct _streamData StreamData;

struct _priceData{
    char *departure;
    char *destination;
    char *singleJourney;
    char *easyCard;
    char *senior;
};

struct _streamData{
    char fromMark[16];
    char toMark[16];
    char fromNode[16];
    char toNode[16];
};

void setPrice(redisContext *c, FILE *pFILE);
void printPrice(redisContext *c, const char *departure, const char *destination);

#endif //__PRICE_H__