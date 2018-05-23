#include "card.h"
/*
Card* shuffle(void){
    //wchar_t ranksName[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'};
    //wchar_t suitSym[4] = {'\u2660','\u2665','\u2666','\u2663'};
    char suitsName[4] = {'C', 'D', 'H', 'S'};

    srand(time(NULL));
    int j,k;
    Card *card = malloc(totalCardNum*sizeof(Card));
    for(int i = 0; i < totalCardNum; i++){
        card[i].suit = i % 4;
        card[i % 4].suitName = suitsName[i % 4];
        //card[i % 4].suitSymbol = suitSym[i % 4];
        card[i].rankNum  = i / 4 + 1;
        //card[i / 4].rankName = ranksName[i / 4];
    }
    for(int i = 0; i < wishTime; i++){
        j = rand() % totalCardNum;
        k = rand() % totalCardNum;
        swap(card[j],card[k]);
    }
    return card;
}
*/

void cardtext(char card, char* text){
    char suit;
    char num;
    char cx; 

    suit = card % 4;
    if(suit == 0)
        cx = snprintf(text, textSize, "%s", "C");
    else if(suit == 1)
        cx = snprintf(text, textSize, "%s", "D");
    else if(suit == 2)
        cx = snprintf(text, textSize, "%s", "H");
    else if(suit == 3)
        cx = snprintf(text, textSize, "%s", "S");
    
    num = card / 4;
    if(num == 0)
        snprintf(text+cx, textSize, "%s", num+3);
    else if(num == 10)
        snprintf(text+cx, textSize, "%s", "J");
    else if(num == 11)
        snprintf(text+cx, textSize, "%s", "Q");
    else if(num == 12)
        snprintf(text+cx, textSize, "%s", "K");
    else
        snprintf(text+cx, textSize, "%d", num+1);
}
