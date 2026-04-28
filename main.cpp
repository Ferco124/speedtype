#include <iostream>
#include "main.h"
#include "profile.h"

using namespace std;

int userInput(int lower, int upper, string error){
    while (true){
        int input = 0;
        cout << "#? " ;
        cin >> input;
        if (lower <= input && input <= upper){
            return input;
        }
        if(error != ""){
            cout << error << endl;
        }
    }
}

int main(){
    string username;
    cout<< "Welcome to SpeedType!!\nPlease enter username (new user will be created if user does not exist):" << endl;
    cin >> username;
    Profile* user = loadProfile(username);

    int input = 0;
    while (true){
        cout << "\n >Main Menu\n[Input] Select an option:" <<endl; 
        cout << "1) Play" <<endl; 
        cout << "2) See statistics" <<endl; 
        cout << "3) Change Profile" <<endl; 
        cout << "4) Exit" <<endl; 
        input = userInput(1,4);
        cout << endl;
        if (input == 1){
            cout<< "insane gameplay goes here"<<endl;
            user->playCount +=1;
        }else if (input == 2){
            viewStats(user);
        }else if (input == 3){
            changeProfile(user);
        }else if (input == 4){
            saveProfile(user);
            cout<< "See you next time!" << endl;
            exit(0);
        }
    }
}