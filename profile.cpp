#include <iostream>
#include <fstream>
#include "profile.h"

Profile* loadProfile(string name){ //function for loading user data, take username as input
    Profile* p = new Profile; //make new Profile object
    p->name = name; //set name to the username

    ifstream file(name + ".txt"); //check if file with inputted username exists
    if (file.is_open()) {
        file >> p->playCount >> p->avgWPM >> p->bestWPM; //load save file data to Profile object
        file.close(); //close file
        cout << "Welcome back, " << name << "!" << endl;
    } else {
        p->playCount = 0; //make new profile with no data
        p->avgWPM = 0.0;
        p->bestWPM = 0.0;
        cout << "Created new profile for " << name << "." << endl;
    }
    return p; //return memory address of Profile
}

void saveProfile(Profile* p){ //function for saving user data, take pointer to loaded Profile as input
    ofstream file(p->name + ".txt"); //save data to txt file
    file << p->playCount << " " << p->avgWPM << " " << p->bestWPM; //read data from Profile and output to txt file
    file.close();
}

void updateStats(Profile* p, double WPM){ //function for updating user data in memory, take pointer to loaded Profile and new WPM as input
    if (WPM >= 0){ //check if last game is valid, invalid game will return new WPM of -1 
        if (WPM > p->bestWPM){ //check if new WPM is higher then the current bestWPM saved in profile
            p->bestWPM = WPM; //update bestWPM if new WPM is higher
        } 
        
        double totalWPM = (p->avgWPM * p->playCount) + WPM; //calculate current total WPM for calculation below
        p->playCount++; //increate playCount by 1
        p->avgWPM = totalWPM / p->playCount; //calculate new average WPM
        
        saveProfile(p);
    }
}

void viewStats(Profile* p){ //function for viewing user data, take pointer to loaded Profile as input
    cout<< "Username: " << p->name<<endl; //print user stats one by one from the loaded Profile
    cout<< "Play Count: " << p->playCount<<endl;
    cout<< "Average WPM: " << p->avgWPM<<endl;
    cout<< "Best WPM: " << p->bestWPM<<endl;
}

void changeProfile(Profile* &p){ //function for changing user, take pointer to loaded Profile as input
    string newUser;
    cout<< "Please enter username (new user will be created if user does not exist): ";
    cin >> newUser;  //take new username as input
    saveProfile(p); //save current loaded profile data to txt file
    delete p;  //free memory
    p = loadProfile(newUser); //load new user data, the inputted pointer is updated directly 
}                             //as the input is passed by reference