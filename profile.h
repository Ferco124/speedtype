#ifndef PROFILE_H
#define PROFILE_H

#include <string>
using namespace std;

struct Profile { //structure for storing user data
    string name;
    int playCount;
    double avgWPM;
    double bestWPM;
};

Profile* loadProfile(string name); 
void saveProfile(Profile* p);
void updateStats(Profile* p, double WPM);
void viewStats(Profile* p);
void changeProfile(Profile* &p);

#endif