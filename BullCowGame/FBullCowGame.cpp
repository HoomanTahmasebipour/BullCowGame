/*
    FBullCowGame.cpp
    BullCowGame
 
    Created by Hooman Tahmasebipour on 2017-07-25.
 
    This includes all the function declarations in the 
    header file and definies the private and public functions. All libraries
    required for functionality are also included.
 
    Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
*/

#include <iostream>
#include "FBullCowGame.hpp"
#include <map>

// To make syntax unreal friendly
#define TMap std::map

using int32 = int;

// When a game is intantiated, everything is reset
FBullCowGame::FBullCowGame() { Reset();} // default constructor

int32 FBullCowGame::GetCurrentTry() const{ return myCurrentTry; }
long FBullCowGame::GetHiddenWordLength() const { return myHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const{ return bGameWon;}

bool FBullCowGame::IsLowerCase(FString userGuess) const {
    for (auto letter:userGuess) {
        if (!islower(letter)) { // if not a lowercase letter, return false
            return false;
        }
    }
    return true;
}

bool FBullCowGame::IsIsogram(FString word) const{
    
    // let's us treat 0 & 1 letter words as isograms
    if (word.length() <= 1) { return true; }
    
    TMap<char, bool> letterSeen;
    for (auto Letter:word) { // loop through word as many times as the # of letters in it
        Letter = tolower(Letter); // handle uppercase as well
        if (letterSeen[Letter]) { // if this is a repeating letter, not isogram (false)
            return false;
        }
        else { // if new letter, continue going through the word
            letterSeen[Letter] = true;
        }
    }
    return true; // executes only when all the letters were new
}

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries {
        {3,6}, {4,6}, {5,8}, {6,8}, {7,10}, {8,10}, {9,12}
    };
    return WordLengthToMaxTries[static_cast<int32>(myHiddenWord.length())];
}

void FBullCowGame::Reset() {
    myCurrentTry = 1;
    bGameWon = false;
    guessIsAllLowerCase = true;
    return;
}

// based on the user's selection, the game difficulty is set.
// ie the length of the word
void FBullCowGame::setDifficulty() {
    FString difficultyLevel = "";
    bool validResponse = true;
    std::cout << "Levels: G -- PG -- PG-13 -- 14A -- R -- Unrated -- I Dare You!!\n";
    std::cout << "Tell me, how badly you want to lose?\nI'll try my hardest to oblige: ";
    std::getline(std::cin, difficultyLevel);
    do {
        validResponse = true;
        if ("G" == difficultyLevel) {
            myHiddenWord = "you";
        }
        else if("PG" == difficultyLevel) {
            myHiddenWord = "lose";
        }
        else if("PG-13" == difficultyLevel) {
            myHiddenWord = "badly";
        }
        else if("14A" == difficultyLevel) {
            myHiddenWord = "oblige";
        }
        else if("R" == difficultyLevel) {
            myHiddenWord = "hardest";
        }
        else if("Unrated" == difficultyLevel) {
            myHiddenWord = "organism";
        }
        else if("I Dare You!!" == difficultyLevel) {
            myHiddenWord = "carbonize";
        }
        else {
            std::cout << "\nPlease enter the level exactly as seen above\n";
            std::cout << "Let's try that again: ";
            std::getline(std::cin, difficultyLevel);
            std::cout << std::endl;
            validResponse = false;
        }
    } while (!validResponse);
}

EGuessStatus FBullCowGame::CheckGuessVAlidity(FString userGuess) const {
    
    if (userGuess.length() != GetHiddenWordLength()) { // if guess length is wrong
        return EGuessStatus::Wrong_Length;
    }
    else if (!IsIsogram(userGuess)) { // if the guess isnt isogram
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowerCase(userGuess)) { // if guess isnt all lowercase
        return EGuessStatus::Not_Lowercase; // TODO make function
    }
    else {
        return EGuessStatus::OK;
    }
    
}

// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString userGuess) {
    long hiddenWordLength = GetHiddenWordLength();
    long userGuessLength = userGuess.length();
    
    FBullCowCount BCCount;
    
    myCurrentTry++;

    for (int32 mHWChar = 0; mHWChar < hiddenWordLength; mHWChar++) {
        // compare letters against hidden word
        for (int32 GChar = 0; GChar <userGuessLength; GChar++) {
            if (myHiddenWord[mHWChar] == userGuess[GChar]) {
                if (mHWChar == GChar) { // letters match and in same place
                    BCCount.Bulls++; // increment bulls
                }
                else { // letters match but in different places
                    BCCount.Cows++; // increment
                }
            }    
        }
    }
    if (BCCount.Bulls == GetHiddenWordLength()) bGameWon = true;
    return BCCount;
}












