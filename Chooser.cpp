/*
Created by Jeffrey Oyuela
Email: jeffreyoyuela@gmail.com
LinkedIn: https://linkedin.com/in/jeffreyoyuela/
Date: 9/18/23

Brief: The following is the "Chooser" object. This object will read each line of a given txt file with the titles of different video games, 
store those names in a vector, and choose a video game for the user to play. It chooses the video game by using a random number generator, picking
the title stored in that element of the vector, and adding to the counter stored in a hashmap. The first title to get picked five times is the
game the user should play!
After the game is chosen, the program will ask the user if they'd like to see the results of the program. If they choose yes, it will print out the
results and ask the user if they'd like the results in txt format as well. If they choose yes, then the program does so.
*/

#include "Chooser.hpp"

/**
 * @brief Construct a new Chooser:: Chooser object
 * 
 */
Chooser::Chooser(){
    run_ = true;
    winner_ = "";

    string input = "";
    ifstream file = enterName(input);
    string title;

    //Add each title to the vector of game titles
    while(getline(file, title)){
        games_.push_back(title);
    }

    //Close file
    file.close();
}


/**
 * @brief This parameterized constructor will create a "Chooser" object that will have a vector containing the titles of all the games.
 * 
 * @param a string called "input" which will be the name of the file that contains the titles.
 * @post A Chooser object that has a vector full of video game titles.
 */
Chooser::Chooser(string input){
    run_ = true;
    winner_ = "";

    //Creating ifstream object
    ifstream file(input);

    //If the file failed to open...
    if(!file){

        //Display an error message
        cout << "Error: Invalid File Type or File Does Not Exist" << endl;

        //Prompt the user to input a valid name
        file = enterName(input);
    }

    string title;
    //Read each line of the file and store it in title
    while(getline(file, title)){
        //Add the title to the vector of game titles
        games_.push_back(title);
    }
    
    //Close the file
    file.close();
}


/**
 * @brief Destroy the Chooser:: Chooser object
 * 
 */
Chooser::~Chooser(){

}


/**
 * @brief Prompt the user to input the name of the file to be read. Push 
 *
 * @param A string containing the name of the file we want to work with
 * @return An ifstream object of the file we want to read from
 */
ifstream Chooser::enterName(string &input){
    while(true){
        //Prompt the user for the name of the txt file
        cout << "Enter the name of your file: ";
        cin >> input;

        //Open the file with the given name
        ifstream file(input);

        //If the file was opened, proceed
        if(file){
            return file;
            break;
        }
            
        //Otherwise, display an error message
        else{
            cout << endl << "Error: Invalid File Type or File Does Not Exist" << endl;
        }
    }
    
}


/**
 * @brief This function starts the choosing process!
 * 
 * @post Decides the winner
 */
void Chooser::start(){
    //Create random device
    random_device rd;

    //Create a distribution
    uniform_int_distribution<int> dist(0,games_.size()-1);

    //While the chooser is still running
    while(isRunning()){
        //Grab a random title from games_
        string title = pickGame(dist(rd));

        //Decide if this title has now been picked 5 times
        isWinner(title);
    }

    //Display a message indicating the title of the game the user will play
    cout << endl << "Your next game is: " << winner() << "!" << endl;

    //Ask the user if they'd like to see the results of the algorithm
    results();
}

/**
 * @brief This function asks the user if they'd like to see the results of the algorithm. If they say yes, it prints the results. 
 * It will then ask the user if they'd like their results in a .txt file. If they say yes, it will make the file.
 * 
 * @post Displays the results and creates a txt file with the results
 */
void Chooser::results(){

    //Creating char variable
    char answer;

    //Keep asking the user for a valid answer until they give one
    while(true){
        cout << "Would you like you like the results? Y/N ";
        cin >> answer;

        //If they responded yes...
        if(tolower(answer) == 'y'){

            //Go through each title
            for(string i : games_){
                //If it's been picked at least once...
                if(counter_.find(i) != counter_.end()){
                    
                    //Print the results
                    cout << i << " - " << counter_[i] << endl;
                }
                
                //If it hasn't been picked once...
                else{

                    //Print the results of that title
                    cout << i << " - " << 0 << endl;
                }
            }
            break;
        }

        //If they responded no...
        else if(tolower(answer) == 'n'){
            
            //End the loop
            break;
        }

        //If an invalid response was given, display an error message
        else{
            cout << "Invalid Response" << endl << endl;
        }
    }

    //If they wanted the results
    if(tolower(answer) == 'y'){

        //Keep asking for a valid response
        while(true){

            //Ask for a response
            cout << "Would you like a txt file of your results? Y/N ";
            cin >> answer;

            //If they responded yes...
            if(tolower(answer) == 'y'){

                //Create a txt file
                ofstream file("results.txt");

                //Write the results onto that file
                for(string i : games_){
                    if(counter_.find(i) != counter_.end()){
                        file << i << " - " << counter_[i] << endl;
                    }
                    else{
                        file << i << " - " << 0 << endl;
                    }
                }

                //Close the file
                file.close();
                break;
            }

            //If they responded no...
            else if(tolower(answer) == 'n'){
                //End the loop
                break;
            }

            //If they gave an invalid response, display an error message
            else{
                cout << "Invalid Response" << endl << endl;
            }
        }
    }

}


/**
 * @brief This function will choose a random game from the vector "games_" 
 * 
 * @return A string containing the title of the randomly choosen game
 */
string Chooser::pickGame(int random){
    //Store the title name
    string game = games_[random];

    //If the title has been picked out before...
    if(counter_.find(game) != counter_.end()){
        //Add to its counter
        counter_[game]++;
    }

    //If the titles hasn't been picked out before...
    else{
        //Create a counter for it and start it at 1
        counter_.insert({game, 1});
    }

    //Return the title of the game
    return game; 
}


/**
 * @brief This function will return the title of the winning game
 * 
 * @return A string containing the title of the winning game
 */
string Chooser::winner(){
    return winner_;
}


/**
 * @brief This function will decide whether or not the given game is the game that will be played.
 * 
 * @param A string containing the title of the game, "title".
 * @return A flag indicating whether the game is the winner or not. 
 */
bool Chooser::isWinner(string &title){
    if(counter_[title] == 5){
        winner_ = title;
        run_ = false;
        return true;
    }
    return false;
}


/**
 * @brief This function will indicate whether or not the chooser is still running
 * 
 * @return A boolean indicating whether the chooser is still running
 */
bool Chooser::isRunning(){
    return run_;
}

