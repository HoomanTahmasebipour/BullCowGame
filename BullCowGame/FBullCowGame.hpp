/*
    FBullCowGame.hpp
    BullCowGame

    Created by Hooman Tahmasebipour on 2017-07-25.

    This header file includes all the function declarations, 
    which are defined in the cpp file, as well as all necesarry
    private variable declarations. All libraries necessary 
    for functionality are also included.
 
    Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
*/

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>
#pragma once

// To make syntax user friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); //constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    long GetHiddenWordLength() const;
    
    bool IsGameWon() const;
    EGuessStatus CheckGuessVAlidity(FString) const;
    
    void Reset(); 
    void setDifficulty();
    
    // counts bulls and cows and increases turn #, asssuming valid guess
    FBullCowCount SubmitValidGuess(FString);
    
private:
    int32 myCurrentTry;
    FString myHiddenWord;
    bool bGameWon = false;
    bool guessIsAllLowerCase = true;
    
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
};

#endif /* FBullCowGame_hpp */
