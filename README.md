# SpeedType

SpeedType is a typing trainer game project for COMP2113.  
It features a user profile system and multiple difficulty levels.

## Group Members & Work Distribution

**Cheung Tsun Ho (3036587365)**:  
Main Program (main.cpp), Profile System (profile.cpp), Statistics Calculation (game.cpp), README.md  

**Tang Chun Lok (3036590506)**:  
Typing Game Logic & Statistics Calculation (game.cpp), Sentences Library


## Gameplay

When you run the game, the game will ask for a username. If you have played before, typing your username will load your previous data, just like logging back into your account. If you are a new user, the game will create a new user profile for that username. 

The main menu has 4 options. Play, See Statistics, Change Profile and Exit

### Play  
The game has 3 difficulty level, easy normal and hard. They varies in the length and complexity of words. You can choose the difficulty you want to play.

Once you choose a difficulty, you will see the passage you need to type to get ready. To start the game, enter anything into the terminal and the game will start a 3 second countdown. Once the countdown is finished you can start typing.

After a game is over, you will see some statistics. First is a list of mistakes you made. Second is your WPM, only correct words will be considered when calculating the WPM. Third is Raw WPM, this consider all words, including those with mistakes, when calculating. So if you make no mistake, the two WPM should be the same. Finally is the accuracy, which is the percentage of correct words you typed.

If you scored a new personal best record, the game will alert you.

#### WPM and Accuracy Calculation
Our game utilizes the Standardized Net WPM metric, which is used in professional typing competitions and other web typing game.

**The 5 Character Rule**: To ensure fairness across different sentence complexities, 1 "Word" is defined as 5 characters (including spaces). This prevents a user's WPM from fluctuating simply because one sentence has longer words than another.

**Raw WPM**: This is the raw typing speed, calculated as:

$$Raw WPM = \frac{(\text{Total Characters} / 5)}{\text{Time}}$$

**Accuracy**: Calculated as the percentage of the target passage correctly typed. We use floating-point division to ensure precision in the final percentage.

**WPM**: This is the final score saved to your profile. It is calculated by taking your raw speed and applying a penalty for every mistake:

$$WPM = \text{Raw WPM} - \left( \frac{\text{Typo Count}}{\text{Time}} \right)$$

This ensures that a player who types very fast but makes many mistakes (or fails to finish the passage) will receive a score that reflects their true typing level.

WPM over 400 will be considered invalid, and that game will not be counted towards player statistics. This act as an anti-cheat measure, to prevent user from copy and pasting the passage directly in the terminal.

### See Statistics
This option will display the lifetime statistics of that user, that includes play count, average WPM and best WPM.

### Change Profile
This option logout the user and let them login as another user profile.


## Coding Requirements

### Generation of random events
The game will randomly pick a sentence from a set library of sentences for the player to type.

### Data structures for storing data
Player data is stored using a struct 

```C++
struct Profile {
    string name;
    int playCount;
    double avgWPM;
    double bestWPM;
};
```

Player data is loaded onto memory dynamically upon login. After each game the data is updated automatically and saved to a text file.   
The details are explained in more detail below.

### Dynamic memory management
The Profile struct is the player data structure that is handled dynamically. When a player logs in or creates a new account, a new Profile object is dynamically allocated on the memory with the loadProfile function. After each game, the player data on memory gets updated. When player logout or exit, the memory of the current player data is deallocated before loading new user data onto the memory.

### File input/output
Player data is stored in a text file in the format of [username].txt. When launching the game player will login by typing the username. The game will try to find the save file for that username and read the save file. The save file contains 1 integer `playCount` and 2 floating point numbers `avgWPM` and `bestWPM`, the game will read the file and load the data onto memory. A new save will be created if an existing save is not found. 

When the player finishes a game, the new updated player data will be saved to the text file, ensuring no play data lost even if the game is not exited properly.

### Program codes in multiple files
The game is coded in separate files, the main program (main.cpp), the profile management (profile.cpp/h), and the actual game itself (game.cpp/h).

### Multiple Difficulty Levels
The game offer 3 difficulty level, easy normal and hard. Harder difficulty will have longer sentences and more complex words.

## Compiling
1. Download the entire repository and set working directory to speedtype
2. In the terminal type ```make speedtype```
3. Launch the game by typing ```./speedtype```
4. ```make clean``` will remove compilied files