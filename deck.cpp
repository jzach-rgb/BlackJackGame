#include <iostream>
using namespace std;
#include "deck.h"
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <codecvt>


    Deck::Deck()
    {
        int j = 1; // creates int j used to set values of the cards 
        for(int i = 0; i < 13; i++) //makes the first 13 all diamonds 
        {
            
            card c;
            c.suite = 'D';
            c.cardNum = j;
            deck.push_back(c);
            j++; //increaments j accordingly
        }

        j = 1; // resets j back to 1 for the next batch
        for(int i = 13; i < 26; i++) //makes the next 13 all Hearts 
        {
            card c;
            c.suite = 'H';
            c.cardNum = j;
            deck.push_back(c);
            j++;
        }

        j = 1;
        for(int i = 26; i < 39; i++) //makes the next 13 all Clubs 
        {
            card c;
            c.suite = 'C';
            c.cardNum = j;
            deck.push_back(c);
            j++;
        }

        j = 1;
        for(int i = 39; i < 52; i++) //makes the last 13 all Spades
        {
            card c;
            c.suite = 'S';
            c.cardNum = j;
            deck.push_back(c);
            j++;
        }
    }


    void Deck::shuffle()
    {
        vector<card> shuffledDeck; //creates a new vector called shuffled deck
        while(deck.size() > 0) // loops through all of the original shuffledDeck
        {
            int randNum = (rand() % deck.size()); //creates a random number from 1 - however many cards are in the unshuffled deck
            shuffledDeck.push_back(deck[randNum]); //adds the card with the index of the random number
            deck.erase(deck.begin() + randNum); //gets rid of that card
        }

         deck = shuffledDeck; //sets deck to be shuffled deck  
    }

    char Deck::getCardSuite(int i)
    {
        return deck[i].getSuite();
    }

    int Deck::getCardNum(int i)
    {
        return deck[i].getNum();
    }


    vector<Deck::card> Deck::getDeck()
    {
        return deck;
    }

    void Deck::setDeck(vector<Deck::card> d)
    {
        deck = d;
    }

    void Deck::printCard(char s, int n) //prints out deck of cards
    {
        const char d[] = "\xe2\x99\xa6";
        const char h[] = "\xe2\x99\xa5";
        const char sp[] = "\xe2\x99\xa0";
        const char c[] = "\xe2\x99\xa3";
         
        cout << " _____________" << endl; 
        cout << "|             |" << endl;

        if(n > 9) //if number has 2 digits fix spacing
        {
            //prints out Jack, Queen, and King
            if(n == 11)
                cout << "|  " << 'J' <<"          |" << endl;
            else if(n == 12)
                cout << "|  " << 'Q' <<"          |" << endl;
            else if(n == 13)
                cout << "|  " << 'K' <<"          |" << endl;
            else
                cout << "| " << n <<"          |" << endl;
        }else
        {
            if(n == 1)
                cout << "| " << 'A' <<"           |" << endl; // prints out Ace
            else
                cout << "| " << n <<"           |" << endl; // prints out other numbers (less than 10)
        }

        cout << "|             |" << endl;

        // prints out symbols for heart, Diamond, spades, and clubs
        if(s == 'H')
            cout << "|      "<< h <<"      |" << endl;
        else if(s == 'D')
            cout << "|      "<< d <<"      |" << endl;
        else if(s == 'S')
            cout << "|      "<< sp <<"      |" << endl;
        else 
            cout << "|      "<< c <<"      |" << endl;

        cout << "|             |" << endl;
        cout << "|             |"  << endl;

        if(n > 9)
        {
            if(n == 11)
                cout << "|          " << "J" << "  |" << endl;
            else if(n == 12)
                cout << "|          " << "Q" << "  |" << endl;
            else if(n == 13)
                cout << "|          " << "K" << "  |" << endl;
            else
                cout << "|         " << n << "  |" << endl;
        }
        else
        {
            if(n == 1)
                cout << "|        " << "A" << "    |" << endl;
            else
                cout << "|          " << n << "  |" << endl;
        }

        cout << "|_____________|";
        
    }

    void Deck::removeCard(int i)
    {
        deck.erase(deck.begin() + i);
    }

    int Deck::getNumOfCardsInDeck()
    {
        return deck.size();
    }
