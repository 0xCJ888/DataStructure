#include <stdio.h>
#include <stdlib.h>     /* atoi, qsort */
#include <string.h>

#include "hiredis.h"
#include "card.h"
#include "player.h"

int main(int argc, char **argv) {
    Player player[playerNum] = {[0] = { .playerName = 'A'},
                                [1] = { .playerName = 'B'},
                                [2] = { .playerName = 'C'},
                                [3] = { .playerName = 'D'}};
    redisContext *c;
    redisReply *reply;
    const char *hostname = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    /* create cards */
    for(int i = 0; i < 52; i++){
        reply = redisCommand(c, "SADD deck %d", i);
    }
    
    /* check deck */
    reply = redisCommand(c,"sunionstore game:deck deck");
    printf("sunionstore : %lld\n", reply->integer);
    freeReplyObject(reply);

    
    for(int i = 0; i < playerNum; i++){
        /* deal */
        reply = redisCommand(c, "SPOP game:deck %u", cardNum);
        if (reply->type == REDIS_REPLY_ARRAY) {
            for (int j = 0; j < reply->elements; j++) {
                char buf[3];
                char num = atoi(reply->element[j]->str);
                player[i].hand[j].value = num;
                cardtext(num, buf, &player[i].hand[j].suitNum, &player[i].hand[j].rankNum);
            }
        }
        freeReplyObject(reply);

        /* sort */
        qsort(player[i].hand, cardNum, sizeof(Card), compareRankNum);
        for(int j = 0; j < cardNum; j++){
            printf("%u\t", player[i].hand[j].rankNum);
            printf("%u\t", player[i].hand[j].suitNum);
            printf("%u\t", player[i].hand[j].value);
            puts("\n");
        }
        puts("\n");

        /* setPlayerCards */
        setMatrixOfPlayerCards(&(player[i]));
        
        for(int j = 0; j < cardNum; j++){
            for(int k = 0; k < playerNum + 1; k++){
                printf("%u\t", player[i].MatrixOfPlayerCards[j][k]);    
            }
            puts("\n");
        }
            
        puts("\n");
    }

    /* clean all */
    redisCommand(c, "flushall");

    return 0;
}