#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "card.h"

#define cardNum 13
#define playerNum 4
#define PAIR 2
#define TRIPLE 3
#define QUAD 4
#define ELEMENNT 4

typedef struct player Player;

struct player{
    char playerName[8];
    Card hand[cardNum];
};


void deal(Player *player, redisContext *c);
void cardInHand(Player *player, redisContext *c);
void findList(Player *player, redisReply *reply, redisContext *c, const uint8_t num);
void findListRangeOne(redisContext *c, const uint8_t num, char *s);
void findListRangeTwo(redisContext *c, const uint8_t num, char *s);
void findMultiCards(Player *player, redisContext *c, const uint8_t num);
void findFullHouse(Player *player, redisContext *c);
void findFourOfAKind(Player *player, redisContext *c);
void findStraight(Player *player, redisContext *c);  //no JQKA2、QKA23、KA234
void findStraightFlush(Player *player, redisContext *c);

#endif