#include "card.h"

void createCards(redisContext *c){
    for(int i = 4; i < 56; i++){
        redisCommand(c, "SADD deck %d", i);
    }
}

void checkDeck(redisContext *c){
    redisReply *reply;
    reply = redisCommand(c,"sunionstore game:deck deck");
    printf("sunionstore : %lld\n", reply->integer);
    freeReplyObject(reply);
}

void cardtext(const char cardNum, char *text, char *suitNum, char *rankNum){
    char cx; 

    *suitNum = cardNum % 4;
    if(*suitNum == 0)
        cx = snprintf(text, textSize, "%s", "C");
    else if(*suitNum == 1)
        cx = snprintf(text, textSize, "%s", "D");
    else if(*suitNum == 2)
        cx = snprintf(text, textSize, "%s", "H");
    else if(*suitNum == 3)
        cx = snprintf(text, textSize, "%s", "S");
    
    *rankNum = cardNum / 4;    
    if(*rankNum == 10)
        snprintf(text+cx, textSize, "%s", "J");
    else if(*rankNum == 11)
        snprintf(text+cx, textSize, "%s", "Q");
    else if(*rankNum == 12)
        snprintf(text+cx, textSize, "%s", "K");
    else if(*rankNum == 13)
        snprintf(text+cx, textSize, "%s", "A");
    else
        snprintf(text+cx, textSize, "%d", *rankNum+1);
}
