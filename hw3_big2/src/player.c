#include "player.h"
#include "card.h"

void deal(Player *player, redisContext *c){
    redisReply *reply;
    reply = redisCommand(c, "SPOP game:deck %u", cardNum);
    if(reply->type == REDIS_REPLY_ARRAY){
        for(int j = 0; j < reply->elements; j++){
            char num = atoi(reply->element[j]->str);
            player->hand[j].value = num;
            cardtext(num, player->hand[j].suitName, &player->hand[j].suitNum, &player->hand[j].rankNum);
            redisCommand(c, "ZADD %s %d %s", player->playerName, player->hand[j].rankNum, player->hand[j].suitName); // sorted set
        }
    }
    freeReplyObject(reply);
}

void cardInHand(Player *player, redisContext *c){
    redisReply *reply;
    puts("ZRANGE");
    reply = redisCommand(c, "ZRANGE %s 0 -1 WITHSCORES", player->playerName);
    if(reply->type == REDIS_REPLY_ARRAY){
        for(int j = 0; j < reply->elements; j++){
            printf("%u) %s\n", j, reply->element[j]->str);
        }
    }
    freeReplyObject(reply);
}

void findPair(Player *player, redisContext *c){
    redisReply *reply;
    puts("find pair triple quad");
    for(int j = 1; j < cardNum + 1; j++){
        reply = redisCommand(c, "ZRANGEBYSCORE %s %d (%d", player->playerName, j, j+1);
        if(reply->type == REDIS_REPLY_ARRAY){
            /* find pair */
            if(reply->elements >= PAIR){
                printf("pair : number %d\n", j);
                for(int k = 0; k < reply->elements; k++){
                    printf("%u) %s\t", k, reply->element[k]->str);
                }
                puts("\n");
            }
            /* find triple */
            if(reply->elements >= TRIPLE){
                printf("triple : number %d\n", j);
                for(int k = 0; k < reply->elements; k++){
                    printf("%u) %s\t", k, reply->element[k]->str);
                }
                puts("\n");
            }
            /* find quad */
            if(reply->elements >= QUAD){
                printf("Quad : number %d\n", j);
                for(int k = 0; k < reply->elements; k++){
                    printf("%u) %s\t", k, reply->element[k]->str);
                }
                puts("\n");
            }
        }
    }
    freeReplyObject(reply);
}

void findStraight(Player *player, redisContext *c){
    redisReply *reply, *replyZCOUNT;
    bool isStraight = true;

    puts("find stright");
    for(int j = 1; j < 10; j++){
        reply = redisCommand(c, "ZRANGEBYSCORE %s %d (%d", player->playerName, j, j + 5);
        if(reply->elements >= 5){
            for(int k = j; k < j + 5; k++){
                replyZCOUNT = redisCommand(c, "ZCOUNT %s %d (%d", player->playerName, k, k+1);
                if(!replyZCOUNT->integer){
                    isStraight = false;
                    break;
                }
            }
            if(isStraight){
                printf("straight : number %d\n", j);
                for(int k = 0; k < reply->elements; k++){
                    printf("%u) %s\t", k, reply->element[k]->str);
                }
                puts("\n");
            }
        }
    }
    freeReplyObject(reply);
    freeReplyObject(replyZCOUNT);
}