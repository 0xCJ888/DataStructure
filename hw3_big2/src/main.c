#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hiredis.h"
#include "card.h"
#include "player.h"

int main(int argc, char **argv) {
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
        char buf[textSize];
        cardtext(i,buf);
        reply = redisCommand(c, "ZADD deck %d %s", i, buf);
    }
    
    /* check deck */
    reply = redisCommand(c,"sunionstore game:deck deck");
    printf("sunionstore : %lld\n", reply->integer);
    freeReplyObject(reply);

    /* deal */
    for(int i = 0; i < playerNum; i++){
        reply = redisCommand(c, "SPOP game:deck %u", cardNum);
        if (reply->type == REDIS_REPLY_ARRAY) {
            for (int i = 0; i < reply->elements; i++) {

                printf("%u) %s\n", i, reply->element[i]->str);
            }
        }
        freeReplyObject(reply);
    }

    /* sort */

    return 0;
}