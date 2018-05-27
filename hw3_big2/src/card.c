#include "card.h"

void createCards(redisContext *c){
    for(int i = 4; i < 56; i++){
        redisCommand(c, "SADD deck %d", i);
    }
}

void unionDeck(redisContext *c){
    redisCommand(c,"sunionstore game:deck deck");
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

uint8_t findcardNum(char *text){
    return (text[1] == 'A') ? 13
         : (text[1] == 'K') ? 12
         : (text[1] == 'Q') ? 11
         : (text[1] == 'J') ? 10
         : (text[1] == '1') ? 9
         : (int)text[1] - '0' - 1;
}

uint8_t findcardSuit(char *text){
    return (text[0] == 'C') ? 1
         : (text[0] == 'D') ? 2
         : (text[0] == 'H') ? 3
         : (text[0] == 'S') ? 4
         : 0;
}

void text2Unicode(char *text){
    char *pText = text;
    do{
        if(*pText == 'C')
            printf("%s", "\e[3;30;47m♣\e[0m");
        else if(*pText == 'D')
            printf("%s", "\e[2;31;47m♦\e[0m");
        else if(*pText == 'H')
            printf("%s", "\e[2;31;47m♥\e[0m");
        else if(*pText == 'S')
            printf("%s", "\e[2;30;47m♠\e[0m");
        else if(*pText == '\t')
            printf("%c", '\t');
        else
            printf("\e[3;30;47m%c\e[0m", *pText);
    }while(*++pText);
}