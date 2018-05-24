#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "stdint.h"
#include "card.h"

#define cardNum 13
#define playerNum 4

typedef struct player Player;

struct player{
    char playerName[7];
    Card hand[cardNum];
    uint8_t MatrixOfPlayerCards[cardNum][playerNum+1];
};

int compareRankNum(const void *a, const void *b);
void setMatrixOfPlayerCards(Player *player);
void findStraight(void);
void findFullHouse(void);
void findFourOfAKind(void);
void findStraightFlush(void);

#endif