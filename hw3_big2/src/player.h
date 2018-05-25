#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "card.h"

#define cardNum 13
#define playerNum 4
#define PAIR 2
#define TRIPLE 3
#define QUAD 4

typedef struct player Player;

struct player{
    char playerName[8];
    Card hand[cardNum];
};

void deal(Player *player, redisContext *c);
void cardInHand(Player *player, redisContext *c);
void findPair(Player *player, redisContext *c);
void findFullHouse(Player *player, redisContext *c);
void findFourOfAKind(Player *player, redisContext *c);
void findStraight(Player *player, redisContext *c);  //no JQKA2、QKA23、KA234
void findStraightFlush(Player *player, redisContext *c);

#endif