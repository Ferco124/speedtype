#include <iostream>
#include "main.h"
#include "profile.h"
#include "game.h"

using namespace std;

int userInput(int lower, int upper){
    while (true){
        int input = 0;
        cout << "#? " ;
        if (cin >> input){
            if (lower <= input && input <= upper){
                return input;
            }
        } else cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main(){
    string username;
    cout<< "Welcome to SpeedType!!\nPlease enter username (new user will be created if user does not exist):" << endl;
    cin >> username;
    Profile* user = loadProfile(username);
    double wpm;
    int input = 0;
    while (true){
        wpm = 0.0;
        cout << "\n >Main Menu\n[Input] Select an option:" <<endl; 
        cout << "1) Play" <<endl; 
        cout << "2) See statistics" <<endl; 
        cout << "3) Change Profile" <<endl; 
        cout << "4) Exit" <<endl; 
        input = userInput(1,4);
        cout << endl;
        if (input == 1){
            cout << ">Main Menu>Play\nWhich difficulties you want?" << endl;
            cout << "1) Easy\n2) Normal\n3) Hard\n";
            int diff = userInput(1,3);
            wpm = main_game(diff);

            if (wpm > user->bestWPM){
                cout << "\nNew Personal Best WPM!!! Congrats!!!" << endl;
            }

            updateStats(user, wpm);
        }else if (input == 2){
            viewStats(user);
        }else if (input == 3){
            changeProfile(user);
        }else if (input == 4){
            saveProfile(user);
            delete user;
            cout<< "See you next time!" << endl;
            exit(0);
        }
    }
}