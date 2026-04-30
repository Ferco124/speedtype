#include <iostream>
#include <string>
#include <limits>
#include "profile.h"
#include "game.h"

using namespace std;

int userInput(int lower, int upper){ //this handles user input, it takes a lower and upper bound as input
    while (true){                    //this function ensure the input is an int and is within the inputted range
        int input = 0;
        cout << "#? " ;
        if (cin >> input){
            if (lower <= input && input <= upper){ //compares the input with the range
                return input; //return valid input
            }
        } else cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clears cin error if input is not int
    }
}

int main(){ //main program
    string username;
    cout<< "Welcome to SpeedType!!\nPlease enter username (new user will be created if user does not exist):" << endl;
    cin >> username; //stores username when login
    Profile* user = loadProfile(username); //make Profile object dynamically
    while (true){
        double wpm = 0.0;
        cout << "\n >Main Menu\n[Input] Select an option:" <<endl;  //display main menu
        cout << "1) Play" <<endl;  
        cout << "2) See statistics" <<endl; 
        cout << "3) Change Profile" <<endl; 
        cout << "4) Exit" <<endl; 
        int input = userInput(1,4);  //uses userInput function to ensure valid input
        cout << endl;
        if (input == 1){
            cout << ">Main Menu>Play\n[Input] Select difficulty:" << endl;
            cout << "1) Easy\n2) Normal\n3) Hard\n";
            int diff = userInput(1,3); //uses userInput to ensure valid difficulty selection
            wpm = main_game(diff); //pass difficulty to the main game program, the game will return wpm after game finish

            if (wpm > user->bestWPM){ //new personal best wpm alert
                cout << "\nNew Personal Best WPM!!! Congrats!!!" << endl;
            }

            updateStats(user, wpm); //update player data after each game
        }else if (input == 2){
            viewStats(user); //display user data
        }else if (input == 3){
            changeProfile(user);  //logout current user and ask for new user login
        }else if (input == 4){
            saveProfile(user); //save profile data to txt file
            delete user; //free memory
            cout<< "See you next time!" << endl; 
            exit(0);
        }
    }
}