#include "player.h"
#include "card.h"

int compareRankNum(const void *a, const void *b){
    return (((Card*)a)->value - ((Card*)b)->value); 
}

void setMatrixOfPlayerCards(Player *player){
    for(int i = 0; i < cardNum; i++){
        for(int j = 0; j < playerNum + 1;j++){
            player->MatrixOfPlayerCards[i][j] = 0;
        }
    }

    for(int i = 0; i < cardNum; i++){
        uint8_t suitNum = player->hand[i].suitNum;
        uint8_t rankNum = player->hand[i].rankNum;
        player->MatrixOfPlayerCards[rankNum][suitNum] = 1;
        player->MatrixOfPlayerCards[rankNum][playerNum]++;
    }
}