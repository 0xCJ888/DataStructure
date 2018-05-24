#include <stdio.h>
#include <stdlib.h>     /* atoi*/
#include <string.h>
#include <stdbool.h>

#include "hiredis.h"
#include "card.h"
#include "player.h"

int main(int argc, char **argv) {
    Player player[playerNum] = {[0] = { .playerName = "PlayerA"},
                                [1] = { .playerName = "PlayerB"},
                                [2] = { .playerName = "PlayerC"},
                                [3] = { .playerName = "PlayerD"}};
    bool isStright = true;
    bool isStrightFlush = true;
    redisContext *c;
    redisReply *reply, *replyZADD, *replyZCOUNT;
    const char *hostname = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if(c == NULL || c->err){
        if(c){
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        }else{
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
    
    /* create cards */
    for(int i = 4; i < 56; i++){
        reply = redisCommand(c, "SADD deck %d", i);
    }
    
    /* check deck */
    reply = redisCommand(c,"sunionstore game:deck deck");
    printf("sunionstore : %lld\n", reply->integer);
    
    for(int i = 0; i < playerNum; i++){
        /* deal */
        reply = redisCommand(c, "SPOP game:deck %u", cardNum);
        if(reply->type == REDIS_REPLY_ARRAY){
            for(int j = 0; j < reply->elements; j++){
                char num = atoi(reply->element[j]->str);
                player[i].hand[j].value = num;
                cardtext(num, player[i].hand[j].suitName, &player[i].hand[j].suitNum, &player[i].hand[j].rankNum);
                /* sorted Set */
                replyZADD = redisCommand(c, "ZADD %s %d %s", player[i].playerName, player[i].hand[j].rankNum, player[i].hand[j].suitName);
            }
        }
        
        /* Card range */
        puts("ZRANGE");
        reply = redisCommand(c, "ZRANGE %s 0 -1 WITHSCORES", player[i].playerName);
        if(reply->type == REDIS_REPLY_ARRAY){
            for(int j = 0; j < reply->elements; j++){
                //printf("%u) %s\n", j, reply->element[j]->str);
            }
        }
        
        
        puts("find pair triple quad");
        for(int j = 1; j < cardNum + 1; j++){
            reply = redisCommand(c, "ZRANGEBYSCORE %s %d (%d", player[i].playerName, j, j+1);
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
        puts("\n");

        puts("find stright");
        isStright = true;
        isStrightFlush = true;
        for(int j = 1; j < 10; j++){
            reply = redisCommand(c, "ZRANGEBYSCORE %s %d (%d", player[i].playerName, j, j + 5);
            if(reply->elements >= 5){
                for(int k = j; k < j + 5; k++){
                    replyZCOUNT = redisCommand(c, "ZCOUNT %s %d (%d", player[i].playerName, k, k+1);
                    if(!replyZCOUNT->integer){
                        isStright = false;
                        break;
                    }
                }
                if(isStright){
                    /* find stright */
                    printf("stright : number %d\n", j);
                    for(int k = 0; k < reply->elements; k++){
                        if(reply->element[k]->str[0] != reply->element[0]->str[0])
                            isStrightFlush = false;
                        printf("%u) %s\t", k, reply->element[k]->str);
                    }
                    puts("\n");
                    /* find stright flush */
                    if(isStrightFlush){
                        for(int k = 0; k < reply->elements; k++){
                            printf("%u) %s\t", k, reply->element[k]->str);
                        }
                    }
                    puts("\n");
                }
            }
        }
    }

    /* clean all */
    redisCommand(c, "flushall");

    freeReplyObject(reply);
    freeReplyObject(replyZADD);
    freeReplyObject(replyZCOUNT);

    return 0;
}