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
}

void cardInHand(Player *player, redisContext *c){
    redisReply *reply;
    printf("Cards in  %s\n", player->playerName);
    reply = redisCommand(c, "ZRANGE %s 0 -1", player->playerName);
    if(reply->type == REDIS_REPLY_ARRAY){
        for(int j = 0; j < reply->elements; j++){
            printf("%u) %s\t", j, reply->element[j]->str);
        }
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
    char Pair[2][4];
    if(reply->type == REDIS_REPLY_ARRAY){
        if(reply->elements >= num){
            uint8_t diff = reply->elements - num;
            for(int i = 0; i < reply->elements; i++){
                printf("%u) %s\t", i, reply->element[i]->str);
                redisCommand(c, "LPUSH CONBI %s", reply->element[i]->str);
            }
            puts("\n");
            if(diff == 1){
                for(int i = 0; i < reply->elements; i++){
                    if(i == reply->elements - 1){
                        findListRangeOne(c, i, Pair[0]);
                        findListRangeOne(c, i - reply->elements + 1, Pair[1]);
                    }
                    else{
                        findListRangeTwo(c, i, Pair[0]);
                    }
                    redisCommand(c, "LPUSH %sPAIR %s\t%s", player->playerName, Pair[0], Pair[1]);
                }
            }
            else if(diff == 2){
                char combination[4][4];
                findListRangeOne(c, 0, combination[0]);
                findListRangeOne(c, 1, combination[1]);
                findListRangeOne(c, 2, combination[2]);
                findListRangeOne(c, 3, combination[3]);
                for(int i = 0; i < reply->elements-1; i++){
                    for(int j = i+1; j < reply->elements; j++){
                        redisCommand(c, "LPUSH %sPAIR %s\t%s", player->playerName, combination[i], combination[j]);
                    }
                }
            }
            else{
                findListRangeTwo(c, 0, Pair[0]);
                redisCommand(c, "LPUSH %sPAIR %s\t%s", player->playerName, Pair[0], Pair[1]);
            }
            redisCommand(c, "DEL CONBI ");
            puts("\n");
        }
    }
}

void findListRangeOne(redisContext *c, const uint8_t num, char *s){
    redisReply *replyLRANGE = redisCommand(c, "LRANGE CONBI %d %d", num, num);
    if(replyLRANGE->type == REDIS_REPLY_ARRAY){
        for(int j = 0; j < replyLRANGE->elements; j++){
            memcpy(s, replyLRANGE->element[j]->str, strlen(replyLRANGE->element[j]->str) + 1);
        }
    }
}

void findListRangeTwo(redisContext *c, const uint8_t num, char *s){
    redisReply *replyLRANGE = redisCommand(c, "LRANGE CONBI %d %d", num, num+1);
    if(replyLRANGE->type == REDIS_REPLY_ARRAY){
        for(int j = 0; j < replyLRANGE->elements; j++){
            memcpy(s + j * 4, replyLRANGE->element[j]->str, strlen(replyLRANGE->element[j]->str) + 1);
        }
    }
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
}

