#ifndef DECK_H
#define DECK_H
#include <vector>
using namespace std;
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

class Deck
{
    struct card //creates a struct class for card
    {
        char suite; //suite of the card
        int cardNum; //number of the card

        char getSuite() //returns cards suite
        {
            return suite;
        }

        int getNum() //returns cards number 
        {
            return cardNum;
        }
    };
    private:
        vector<card> deck;

    public:
     //creates functions for Deck
    Deck();
    vector<card> getDeck(); // returns the deck
    void setDeck(vector<card> d); // sets the deck (meant for when the deck is shuffled)
    void shuffle(); //shuffles the deck
    char getCardSuite(int i); //gets the card's suite
    int getCardNum(int i); //gets the card's Number/Rank 1 = A 11 = j 12 = Q 13 = K
    void printCard(char s, int n); //prints the card 
    void removeCard(int i); //removes a card from the deck
    int getNumOfCardsInDeck(); //returns number of cards in deck (for testing)

};
#endif

