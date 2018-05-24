#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "stdint.h"
#include "card.h"

#define cardNum 13
#define playerNum 4
#define PAIR 2
#define TRIPLE 3
#define QUAD 4

typedef struct player Player;

struct player{
    char playerName[7];
    Card hand[cardNum];
};

void findPair(void);
void findFullHouse(void);
void findFourOfAKind(void);
void findStraight(void);  //no JQKA2、QKA23、KA234
void findStraightFlush(void);

#endif