#include <iostream>
#include <fstream>
#include "profile.h"

Profile* loadProfile(string name){
    Profile* p = new Profile;
    p->name = name;

    ifstream file(name + ".txt");
    if (file.is_open()) {
        file >> p->playCount >> p->avgWPM >> p->bestWPM;
        file.close();
        cout << "Welcome back, " << name << "!" << endl;
    } else {
        p->playCount = 0;
        p->avgWPM = 0.0;
        p->bestWPM = 0.0;
        cout << "Created new profile for " << name << "." << endl;
    }
    return p;
}

void saveProfile(Profile* p){
    ofstream file(p->name + ".txt");
    file << p->playCount << " " << p->avgWPM << " " << p->bestWPM;
    file.close();
}

void updateStats(Profile* p, double WPM){
    if (WPM > p->bestWPM){
        p->bestWPM = WPM;
    } 
    
    double totalWPM = (p->avgWPM * p->playCount) + WPM;
    p->playCount++;
    p->avgWPM = totalWPM / p->playCount;
    
    saveProfile(p);
}

void viewStats(Profile* p){
    cout<< "Username: " << p->name<<endl;
    cout<< "Play Count: " << p->playCount<<endl;
    cout<< "Average WPM: " << p->avgWPM<<endl;
    cout<< "Best WPM: " << p->bestWPM<<endl;
}

void changeProfile(Profile* &p){
    string newUser;
    cout<< "Please enter username (new user will be created if user does not exist): ";
    cin >> newUser;
    saveProfile(p);
    delete p;
    p = loadProfile(newUser);
}