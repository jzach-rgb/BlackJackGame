/*
TO DO:
Implement betting???
*/

#include <iostream>
using namespace std;

#include <string>

#include <stdio.h>
#include <stdlib.h>

#include "deck.h"

#include <chrono> //just to slow down the game a bit
#include <thread>

struct card //creates a struct class for card for main classes so I can use it for vectors in the players struct
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

    int getCardScore() //returns card Score (taking in account the face cards)
    {
        if(cardNum == 1)
        {
            return 11;
        }else if(cardNum == 11 || cardNum == 12 || cardNum == 13)
        {
            return 10;
        }
        return cardNum; 
    }
};

struct players
{
    int playerNum = 0;
    int totalScore = 0;
    bool isIn = true;
    vector<card> cardsInHand;

    bool busted()
    {
        if(totalScore > 21)
        {
            return true;
        }
        return false;
    }

    bool switchValue() //this function subtracts 10 from the total (imitating switching from Ace value from 11 to 1)
    {
        for(int i = 0; i < cardsInHand.size(); i++)
        {
            if(cardsInHand[i].getNum() == 1)
            {
                cardsInHand.erase(cardsInHand.begin() + i);
                totalScore -=  10;
                return true;
            }
        }
        return false;
    }

    bool houseHits() //if the houses total score is less than 17 they must hit otherwise they stand
    {
        if(totalScore < 17)
        {
            return true;
        }
        return false;
    }
};

bool checkInput(string input) //checks every combination of correct inputs and returns accordingly
{
    if(input == "y" || input == "Y")
    {
        return true;
    }else if(input == "n" || input == "N")
    {
        return true;
    }

    return false;
}

bool validHoS(string input) //this function is for the Hit or Stand option, makes sure the input is valid
{
    if(input == "h" || input == "H")
    {
        return true;
    }else if(input == "s" || input == "S")
    {
        return true;
    }
    return false;
}

bool checkIfMaxScore(int score) //checks to see if the player has the max score of 21
{
    if(score == 21)
    {
        cout << "Nice! You got a 21!" << endl;
        return true;
    }
    return false;
}


int main()
{
    cout << "Welcome to Black Jack! Would you like to play (Y or N): "; // Prints welcome message
    string userInput; // variable for user input to choose whether they want to play or not (capitlization doesn't matter)
    cin >> userInput;
    cout << endl;
    while(!checkInput(userInput)) // If user doesn't select either y or n they are prompted again to select correctly
    {
        cout << "Please Enter A Valid Response." << endl;
        cout << "Welcome to Black Jack! Would you like to play (Y or N): ";
        cout << endl;
        cin >> userInput;
    }

    while(userInput == "Y" || userInput == "y") // If input is yes then play other wise end the program
    {
        cout << "How Many Players Are Playing? (1-7 excluding the house): "; // asks how many players are playing
        char num[1000]; //creates numPlayers as a char in case user inputs in a random string
        cin >> num;
        cout << endl;

        while(atoi(num) <= 0 || atoi(num) > 7) //takes in input and checks if it matches the specs otherwise prompts user to try again
        {
            cout << "***Number of Players invalid, please try again.*** " << endl;
            cout << endl;
            cout << "How Many Players Are Playing? (1-7 excluding the house): ";
            cin >> num;
            cout << endl;
        }

        int round = 1;
        string roundInput = "Y";
        
        while(roundInput == "y" || roundInput == "Y")
        {
            this_thread::sleep_for(chrono::seconds(1));

            cout << "Round: " << round << endl << endl;
            Deck d; //create the deck
            d.shuffle(); //shuffle the deck


            players house; //creates the house;

            int playerNum = atoi(num); //creates the number of player variables (created after the check that user entered in ONLY an int 0 < x < 8)
            players playerList[playerNum]; //make a fixed size array of size playerNum (number of players)


            d.shuffle(); //shuffles deck
            
            card c; //Puts down the first card of House
            c.cardNum = d.getCardNum(0);
            c.suite = d.getCardSuite(0);
            d.removeCard(0);

            cout << "First card of House is: " << endl << endl;
            d.printCard(c.getSuite(), c.getNum());
            house.totalScore += c.getCardScore();
            
            this_thread::sleep_for(chrono::seconds(1));
            
            cout << endl << endl << "House Score: " << house.totalScore << endl << endl;

            for(int i = 0; i < playerNum; i++) //gives players 2 cards each
            {
                card c; //creates a variable c of struct c and fills it with the information of the top card 
                c.cardNum = d.getCardNum(0);
                c.suite = d.getCardSuite(0);
                playerList[i].cardsInHand.push_back(c); //puts the card into the players hand 
                d.removeCard(0); //removes the card after
                playerList[i].totalScore += c.getCardScore(); //gets the card score

                c.cardNum = d.getCardNum(0); //do this twice to get two cards
                c.suite = d.getCardSuite(0);
                playerList[i].cardsInHand.push_back(c);
                d.removeCard(0);
                playerList[i].totalScore += c.getCardScore();

                playerList[i].playerNum = i + 1; //sets their player number
            }
            
            string HoS; //creates the string variable HoS for when asking for input about whether a player wants to hit or stand
            int i = 0;
            while(i < playerNum) //iterate through all the players and use an arbitrary int variable i in order to traverse through the players
            {
                    cout << "*It is Player " << playerList[i].playerNum << "'s turn: " << endl;
                    cout << "You currently have in your hand: " << endl << endl;

                    this_thread::sleep_for(chrono::seconds(1));

                    for(int j = 0; j < playerList[i].cardsInHand.size(); j++) //prints out all the cards the player has
                    {
                        d.printCard(playerList[i].cardsInHand[j].getSuite(), playerList[i].cardsInHand[j].getNum());
                        cout << endl;
                    }

                    cout << "You have: " << playerList[i].totalScore << " points." << endl;
                    cout << "Would you like to hit (h) or stand (s)? ";
                    cin >> HoS; //gets input from user about whether or not they want to hit or stand
                    while(!validHoS(HoS)) //check if the user put in a valid input
                    {
                        cout << "***Please enter a valid input***" << endl;

                        this_thread::sleep_for(chrono::seconds(1));

                        cout << "*It is Player " << i << "'s turn: " << endl << "Would you like to hit (h) or stand (s)? ";
                        cin >> HoS; 
                    }

                    while(playerList[i].isIn && (HoS == "h" || HoS == "H")) //if they hit then they draw a card
                    {
                        card c;
                        c.suite = d.getCardSuite(0);
                        c.cardNum = d.getCardNum(0);
                        d.removeCard(0);

                        cout << "You got: " << endl << endl; //prints out new card

                        d.printCard(c.getSuite(), c.getNum()); 
                        cout << endl;

                        this_thread::sleep_for(chrono::seconds(1));

                        playerList[i].cardsInHand.push_back(c); //the card is added to their hand
                        playerList[i].totalScore += c.getCardScore(); //score is updated
                        
                        cout << "Your score is: " << playerList[i].totalScore << endl;

                        checkIfMaxScore(playerList[i].totalScore); //checks if they are at the max score

                        if(playerList[i].busted()) //checks if they busted 
                        {
                            if(playerList[i].switchValue()) //checks to see if the player has an ace so the ace can be switched from 1 to 11
                            {
                                cout << "Switching Ace from value of 11 to 1..." << endl << "Your Score is: " << playerList[i].totalScore << endl;
                            }else
                            {
                                cout << "You went over 21! Your score went over by " << (playerList[i].totalScore - 21) << endl << endl;
                                playerList[i].isIn = false; //if they are busted then they are no longer in it
                                continue;
                            }
                        }

                        cout << "Player "<< playerList[i].playerNum <<", would you like to hit(h) or stand(s): ";
                        cin >> HoS; //gets input from user about whether or not they want to hit or stand
                        while(!validHoS(HoS)) //check if the user put in a valid input
                        {
                            cout << "***Please enter a valid input***" << endl;
                            cout << "It is Player " << i << "'s turn: " << endl << "Would you like to hit (h) or stand (s)? ";
                            cin >> HoS; 
                        }
                        cout << endl;
                    }
                i++;
            }

            card a; //Puts down the second card of House
            a.cardNum = d.getCardNum(0);
            a.suite = d.getCardSuite(0);
            d.removeCard(0);

            cout << "Second card of House is: " << endl << endl;
            d.printCard(a.getSuite(), a.getNum());

            this_thread::sleep_for(chrono::seconds(1));

            house.totalScore += a.getCardScore();
            cout << endl << endl << "House Score: " << house.totalScore << endl;


            while(house.houseHits()) //continues to give House a card until his total score is > 17
            {
                card c; //Puts down the next card of House
                c.cardNum = d.getCardNum(0);
                c.suite = d.getCardSuite(0);
                d.removeCard(0);

                cout << "Next card of House is: " << endl << endl;
                d.printCard(c.getSuite(), c.getNum());

                this_thread::sleep_for(chrono::seconds(1));

                house.totalScore += c.getCardScore();
                cout << endl << endl << "House Score: " << house.totalScore << endl;

                if(house.totalScore > 21) //checks to see if house is above 21 points, if it is then House Busts
                {
                    cout << "House busts! Players Win!" << endl;
                    house.isIn = false;
                }
            }

            vector<players> winnerList;  //puts all the winners into a list 
            for(int i = 0; i < playerNum; i++)
            {
                if((house.isIn == false || playerList[i].totalScore > house.totalScore) && playerList[i].isIn) 
                {
                    winnerList.push_back(playerList[i]);
                }
            }

            if(winnerList.size() == 0 && house.totalScore < 22) //if the list is empty and the house's score is 21 under then that means the house is the last standing and therefrore add it to the winner list
            {
                winnerList.push_back(house);
            }

            cout << endl << "Winners: " << endl; //prints out the Winners by player number

            this_thread::sleep_for(chrono::seconds(1));

            if(winnerList[0].playerNum == 0) //if the first number is 0 then that means the house won
            {
                cout << "House" << endl << endl;
            }else
            {
                for(int i = 0; i < winnerList.size(); i++) //otherwise the other player won
                {
                    cout << "Player: " << winnerList[i].playerNum << endl; 
                }
            }
            cout << "Would you like to play another round? (Y or N): "; //prompts user if they'd like to play another game
            cin >> roundInput;
            while(!checkInput(userInput)) // If user doesn't select either y or n they are prompted again to select correctly
            {
                cout << "Please Enter A Valid Response." << endl;
                cout << "Welcome to Black Jack! Would you like to play (Y or N): ";
                cin >> userInput;
            }
            round++; 
        }

        cout << "Would you like to play a new game? (Y or N): "; //asks user if they would like to play again and then terminates if not Y
        cin >> roundInput;
        while(!checkInput(roundInput)) // If user doesn't select either y or n they are prompted again to select correctly
        {
            cout << "Please Enter A Valid Response." << endl;
            cout << "Welcome to Black Jack! Would you like to play (Y or N): ";
            cin >> roundInput;
        }
    }

    return 0;
}