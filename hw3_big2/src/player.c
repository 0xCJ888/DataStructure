#include "player.h"
#include "card.h"

void deal(Player *player, redisContext *c){
    redisReply *reply;
    reply = redisCommand(c, "SPOP game:deck %u", cardNum);
    for(int j = 0; j < reply->elements; j++){
        char num = atoi(reply->element[j]->str);
        player->hand[j].value = num;
        cardtext(num, player->hand[j].suitName, &player->hand[j].suitNum, &player->hand[j].rankNum);
        redisCommand(c, "ZADD %s %d %s", player->playerName, player->hand[j].rankNum, player->hand[j].suitName);
    }
}

void cardInHand(Player *player, redisContext *c){
    redisReply *reply;
    printf("Cards in  %s\n", player->playerName);
    reply = redisCommand(c, "ZRANGE %s 0 -1", player->playerName);
    for(int j = 0; j < reply->elements; j++){
        printf("%u) ", j+1);
        text2Unicode(reply->element[j]->str);
        printf("\t");
    }
    puts("\n");
}

void findMultiCards(Player *player, redisContext *c, const uint8_t num){
    redisReply *reply;
    for(int j = 1; j < cardNum + 1; j++){
        reply = redisCommand(c, "ZRANGEBYSCORE %s %d (%d", player->playerName, j, j+1);
        findList(player, reply, c, num);
    }
}

void findList(Player *player, redisReply *reply, redisContext *c, const uint8_t num){
    char combi[4][4];
    memset(combi, 0, 16);
    
    if(reply->elements >= num){
        for(int i = 0; i < reply->elements; i++){
            memcpy(combi+i, reply->element[i]->str, strlen(reply->element[i]->str) + 1);
        }
        if(num == PAIR){
            for(int i = 0; i < reply->elements-1; i++){
                for(int j = i+1; j < reply->elements; j++){
                    redisCommand(c, "ZADD %s%d %d %s\t%s", player->playerName, num, findcardNum(combi[i]), combi[i], combi[j]);
                }
            }
        }
        else if(num == TRIPLE){
            for(int i = 0; i < reply->elements-2; i++){
                for(int j = i+1; j < reply->elements-1; j++){
                    for(int k = j+1; k < reply->elements; k++){
                        redisCommand(c, "ZADD %s%d %d %s\t%s\t%s", player->playerName, num, findcardNum(combi[i]), combi[i], combi[j], combi[k]);
                    }
                }
            }
        }
        else if(num == QUAD){
            redisCommand(c, "ZADD %s%d %d %s\t%s\t%s\t%s", player->playerName, num, findcardNum(combi[0]), combi[0], combi[1], combi[2], combi[3]);
        }
    }
}

void printList(Player *player, redisContext *c, const uint8_t num){
    redisReply *replyZCARD = redisCommand(c, "ZCARD %s%d", player->playerName, num);
    if(replyZCARD->integer){
        redisReply *replyZRANGE = redisCommand(c, "ZRANGE %s%d %d %d", player->playerName, num, 0, -1);
        for(int i = 0; i < replyZRANGE->elements; i++){
            printf("%d)\t", i+1);
            text2Unicode(replyZRANGE->element[i]->str);
            puts("");
        }
    }
    else{
        puts("Empty");
    }
    puts("");
}

void straightCombination(Player *player, redisContext *c, uint8_t *straightNum){
    uint8_t cardSuit[5];
    uint8_t isStraightFlush = 0;
    redisReply *replyi, *replyj, *replyk, *replym, *replyn;
    for(int i = 0; i < straightNum[0]; i++){
        replyi = redisCommand(c, "RPOPLPUSH %s%d%d %s%d%d", player->playerName, STRAIGHT, 0, player->playerName, STRAIGHT, 0);
        cardSuit[0] = findcardSuit(replyi->str);
        for(int j = 0; j < straightNum[1]; j++){
            replyj = redisCommand(c, "RPOPLPUSH %s%d%d %s%d%d", player->playerName, STRAIGHT, 1, player->playerName, STRAIGHT, 1);
            cardSuit[1] = findcardSuit(replyj->str);
            for(int k = 0; k < straightNum[2]; k++){
                replyk = redisCommand(c, "RPOPLPUSH %s%d%d %s%d%d", player->playerName, STRAIGHT, 2, player->playerName, STRAIGHT, 2);
                cardSuit[2] = findcardSuit(replyk->str);
                for(int m = 0; m < straightNum[3]; m++){
                    replym = redisCommand(c, "RPOPLPUSH %s%d%d %s%d%d", player->playerName, STRAIGHT, 3, player->playerName, STRAIGHT, 3);
                    cardSuit[3] = findcardSuit(replym->str);
                    for(int n = 0; n < straightNum[4]; n++){
                        replyn = redisCommand(c, "RPOPLPUSH %s%d%d %s%d%d", player->playerName, STRAIGHT, 4, player->playerName, STRAIGHT, 4);
                        cardSuit[4] = findcardSuit(replyn->str);
                        for(int z = 1; z < 5; z++){
                            if(cardSuit[z] != cardSuit[0]){
                                isStraightFlush = 0;
                                break;
                            }
                            else
                                isStraightFlush = 1;
                        }
                        redisCommand(c, "ZADD %s%d %d %s\t%s\t%s\t%s\t%s", player->playerName, STRAIGHT, isStraightFlush, replyi->str, replyj->str, replyk->str, replym->str, replyn->str);
                    }
                }
            }
        }
    }
    delStraightCombination(player, c);
}

void delStraightCombination(Player *player, redisContext *c){
    for(int i = 0; i < 5; i++){
        redisCommand(c, "DEL %s%d%d", player->playerName, STRAIGHT, i);
    }
}

void findPair(Player *player, redisContext *c){
    findMultiCards(player, c, PAIR);
}

void findFullHouse(Player *player, redisContext *c){
    redisReply *replyTri, *replyDouble;
    uint8_t TriNum, TriScore = 0, DoubScore = 0;
    findMultiCards(player, c, TRIPLE);
    replyTri = redisCommand(c, "ZCARD %s%d", player->playerName, TRIPLE);
    TriNum = replyTri->integer;
    replyTri = redisCommand(c, "ZRANGE %s%d %d %d WITHSCORES", player->playerName, TRIPLE, 0, -1);
    replyDouble = redisCommand(c, "ZRANGE %s%d %d %d WITHSCORES", player->playerName, PAIR, 0, -1);
    
    if(TriNum){
        for(int i = 0; i < replyTri->elements; i+=2){
            TriScore = atoi(replyTri->element[i+1]->str);
            for(int j = 0; j < replyDouble->elements; j+=2){
                DoubScore = atoi(replyDouble->element[j+1]->str);
                if(TriScore != DoubScore){
                    redisCommand(c, "ZADD %s%d %d %s\t%s", player->playerName, FULLHOUSE, FULLHOUSE, replyTri->element[i]->str, replyDouble->element[j]->str);
                }
            }
        }
    }
}

void findFourOfAKind(Player *player, redisContext *c){
    redisReply *reply, *replyFour;
    uint8_t QuadNum, num;
    findMultiCards(player, c, QUAD);
    reply = redisCommand(c, "ZRANGE %s 0 -1 WITHSCORES", player->playerName);
    replyFour = redisCommand(c, "ZRANGE %s%d 0 -1 WITHSCORES", player->playerName, QUAD);

    for(int i = 0; i < replyFour->elements; i+=2){
        QuadNum = atoi(replyFour->element[i+1]->str);
        for(int j = 0; j < reply->elements; j+=2){
            num = atoi(reply->element[j+1]->str);
            if(num != QuadNum){
                redisCommand(c, "ZADD %s%d %d %s\t%s", player->playerName, FOUROFKIND, num, replyFour->element[i]->str, reply->element[j]->str);
            }
        }
    }
}

void findStraight(Player *player, redisContext *c){
    redisReply *reply, *replyZCOUNT, *replyZRANGE;
    bool isStraight = true;
    uint8_t straightNum[5] = {0};

    for(int j = 1; j < 10; j++){
        reply = redisCommand(c, "ZRANGEBYSCORE %s %d (%d", player->playerName, j, j + 5);
        if(reply->elements >= 5){
            for(int k = j; k < j + 5; k++){
                replyZRANGE = redisCommand(c, "ZRANGEBYSCORE %s %d (%d", player->playerName, k, k+1);
                for(int m = 0; m < replyZRANGE->elements; m++){
                    redisCommand(c, "LPUSH %s%d%d %s", player->playerName, STRAIGHT, k-j, replyZRANGE->element[m]->str);
                }
                replyZCOUNT = redisCommand(c, "ZCOUNT %s %d (%d", player->playerName, k, k+1);
                straightNum[k - j] = replyZCOUNT->integer;
                if(!replyZCOUNT->integer){
                    delStraightCombination(player, c);
                    isStraight = false;
                    break;
                }
            }
            if(isStraight){
                straightCombination(player, c, straightNum);
            }
        }
    }
}

void findStraightFlush(Player *player, redisContext *c){
    uint8_t isStrightFlush;
    redisReply *replyZRANGE = redisCommand(c, "ZRANGE %s%d %d %d WITHSCORES", player->playerName, STRAIGHT, 0, -1);
    for(int i = 0; i < replyZRANGE->elements; i+=2){
        isStrightFlush = atoi(replyZRANGE->element[i+1]->str);
        if(isStrightFlush)
            redisCommand(c, "ZADD %s%d %d %s", player->playerName, STRAIGHTFLUSH, isStrightFlush, replyZRANGE->element[i]->str);
    }
}