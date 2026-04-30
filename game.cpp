#include <iostream>
#include <fstream> 
#include <cstdlib> // for calling srand(), rand()
#include <thread> // for calling sleep_for() 
#include <chrono> // for calling seconds()
#include <ctime> // for calling time()
#include <string>
#include <iomanip> // for calling setw()
#include "game.h"

using namespace std;

double main_game(int diff_no){ //function for the main game, take difficulty selection as input
    double wpm; // wpm of player after every round (does not count typo)
    srand(time(NULL));
    string filename;
    if (diff_no==1){  //which text file is read depends on player's decision of difficulty
        filename = "passage/easy.txt";
    }
    else if (diff_no==2){
        filename = "passage/normal.txt";
    }
    else {
        filename = "passage/hard.txt";
    }
    ifstream fin;
    fin.open(filename);
    if (fin.fail()) {     // Check if the file fails to read
        cout << "Could not open the file!" << endl;
        exit(1);
    }
    string passage; // the sentence that player is going to type in every game
    int passage_no = rand()%51+1; // for randomly choose a sentence among 50 of them in each file
    for (int i = 0; i < passage_no; i++) {
        if (!getline(fin, passage)) break;
    }  
    if (getline(fin, passage)) {
        cout << "\n~~~This is the passage you need to type~~~\n" << endl;
        cout << passage << endl;
        cout << "\nAre you ready? (Enter any input to start)" << endl;
        string ready; // let player input something when they are ready
        cin >> ready;
        cin.ignore(1000, '\n'); // this is to avoid the coming timer stop immediately
        cout << "3" << endl;
        this_thread::sleep_for(chrono::seconds(1)); // give players three seconds before they start typing
        cout << "2" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "1" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Start: ";
        auto start = chrono::steady_clock::now(); // start the timer when "Start: " is printed
        string passage_enter;
        getline(cin, passage_enter);
        auto end = chrono::steady_clock::now(); // stop the timer when player press enter
        chrono::duration<double> elapsed = end - start;
        double time_used;
        time_used = elapsed.count() / 60; // change timer unit to minute

        double words = 0; // numbers of words in the player input
        string currentword;
        stringstream word(passage_enter);
        while (word >> currentword){
            words++;
        }

        double raw_wpm; // wpm of player but also count typo
        raw_wpm = (passage_enter.length() / 5) / time_used;

        cout << "===========================================================" << endl;
        cout << setw(16) << "the N-th word" << setw(20) << "correct word" << setw(20) << "entered word" << endl;
        string now, now_player; // used for checking every mistaken word of player one by one
        stringstream ss(passage);
        stringstream ss2(passage_enter);
        double typo_count = 0; // store the number of mistaken word of player for calculating wpm and accuracy
        int totalwords = 0;
        while (ss >> now && ss2 >> now_player){
            totalwords++;
            if (now != now_player){
                cout << setw(9) << totalwords << setw(24) << now << setw(20) << now_player << endl; //display wrong words
                typo_count++;
            }
        }

        if (!ss.fail() && ss2.eof()) {
            totalwords++;
            cout << setw(9) << totalwords << setw(24) << now << setw(20) << "/" << endl; //display missing words
            typo_count++;
        }

        while (ss >> now){
            totalwords++;
            cout << setw(9) << totalwords << setw(24) << now << setw(20) << "/" << endl; //display missing words
            typo_count++;
        }

        int extrawords = 0;
        while (ss2 >> now_player) {
            extrawords++;
            cout << setw(9) << "extra" << setw(24) << "/" << setw(20) << now_player << endl; //display extra words
        }

        if (typo_count==0){ 
            cout << setw(43) << "there are no mistaken words" << endl;
        }

        double accuracy; // the accuracy of player
        accuracy = ((totalwords - typo_count) / totalwords) * 100;
        wpm = raw_wpm - (typo_count / time_used);
        if (wpm < 0) wpm = 0;
        cout << "===========================================================" << endl;
        cout << "Your wpm is: " << fixed << setprecision(2) << wpm << endl;
        cout << "Your raw wpm is: " << fixed << setprecision(2) << raw_wpm << endl;
        cout << "Your accuracy is: " << fixed << setprecision(2) << accuracy << "%" << endl;
        
    }
    if (wpm > 400){ // to detect the abuse of copy and paste
        cout << "This is an invalid number of wpm, thus won't count to statistic.";
        return -1; // return a negative number which is impossible for wpm
    }
    else {
        return wpm; // return the wpm when every game ends to for the statistic of players
    }
}