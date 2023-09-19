#ifndef CHOOSER_
#define CHOOSER_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <random>

using namespace std;

class Chooser{
    public:
        //Default Constructor
        Chooser();

        //Parameterized Constructor
        Chooser(string input);

        //Destructor
        ~Chooser();

        //Prompts user for name of file
        ifstream enterName(string &input);

        //Starts the Chooser
        void start();

        //Prints and creates a txt file with the ending stats
        void results();

        //Picks a random game
        string pickGame(int random); 

        //Says the winner
        string winner();

        //Determines if the given game is the winner
        bool isWinner(string &title);

        //Checks if the game is still running
        bool isRunning();

    
    private:
        //A flag indicating whether the chooser is still running
        bool run_;

        //A string containing the title of the winner!
        string winner_;

        //A vector containing the titles of all the games we are choosing from
        vector<string> games_;

        //A hashmap containing the titles of all the games as a key and an integer indicating how many times that game has been choosen
        unordered_map<string, int> counter_; // title -> count

};


#endif