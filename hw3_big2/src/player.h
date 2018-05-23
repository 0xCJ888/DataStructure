#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "card.h"

#define cardNum 13
#define playerNum 4

typedef struct player Player;

struct player{
    char playerName;
    char NumOfCardInHand;
    Card poker[cardNum];
};

#endif