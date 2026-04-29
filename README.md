# SpeedType

SpeedType is a typing trainer game project for COMP2113.  
It features a user profile system and multiple difficulty levels.

## Group members

Cheung Tsun Ho (3036587365)  
Tang Chun Lok (3036590506)

## Coding Requirements

**Generation of random events**:  
The game will randomly pick a sentence from a set library of sentences for the player to type.

**Data structures for storing data**:  
Player data is stored using a struct 

```C++
struct Profile {
    string name;
    int playCount;
    double avgWPM;
    double bestWPM;
};
```

**Dynamic memory management**:  
Player data is loaded into memory when logging in. After each game data in the memory gets updates, and the data will be saved once the player logout or exit.

**File input/output**:  
Player data is stored in a .txt file. When launching the game player will login by typing the username. The game will try to find the save file for that username, a new save will be created if not found.

**Program codes in multiple files**:  
The game is coded in 3 separate files, the main program, the profile management, and the actual game itself.

**Multiple Difficulty Levels**:  
The game offer 3 difficulty level, easy normal and hard. Harder difficulty will have longer sentences and more complex words.

## Compiling
1. Download the entire repository and set working directory to speedtype
2. In the terminal type ```make speedtype```
3. Launch the game by typing ```./speedtype```
4. ```make clean``` will remove compilied files