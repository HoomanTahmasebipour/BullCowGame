/*  main.cpp
    BullCowGame

    Created by Hooman Tahmasebipour on 2017-07-21.
    This is the main file for the game, includes
    the FBullCowGame header file as well as all
    necessary libraries to make the code work.

  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

//  To make syntax unureal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; //create instant of new game

int main(int32 argc, const char * argv[]) {
    
    do {
        PrintIntro();
        PlayGame();
    }while (AskToPlayAgain());
    
    return 0;
}

void PrintIntro() {
    std::cout << "\n\nWelcome to Bulls and Cows!\n";
    
    std::cout << std::endl;
    std::cout << "           }   {    ___ " << std::endl;
    std::cout << "           (o o)   (o o) " << std::endl;
    std::cout << "   /--------\\ /     \\ /-------\\ " << std::endl;
    std::cout << "  / | BULLS |0   &   0| COWS | \\  " << std::endl;
    std::cout << " *  |-------|         |------|  *  " << std::endl;
    std::cout << "    ^      ^          ^      ^ " << std::endl;
    BCGame.setDifficulty();
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinging of?\n";
    std::cout << "You have " << BCGame.GetMaxTries() <<" attempts, good luck!\n\n";
    
    return;
}

void PlayGame() {
    
    BCGame.Reset();
    int32 maxTries = BCGame.GetMaxTries();
    
    // loop asking for guess until game is NOT won
    do {
        FText userGuess = GetValidGuess(); //TODO check for valid guess
        
        // submit valid guess to game, and recieve counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(userGuess);
        
        // print # of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    } while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries);
    
    PrintGameSummary();
    
    return;
}


// loop continually until user gives valid guess
FText GetValidGuess () {
    EGuessStatus status = EGuessStatus::Invalid_Status;
    FText userGuess = " ";
    do {
        int32 currentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << currentTry <<" of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, userGuess);
    
        status = BCGame.CheckGuessVAlidity(userGuess);
        switch(status) {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter guess in all lowercase letters with no spaces\n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word wihout repeating letters\n\n";
            break;
        default:
            break; // assume userGuess is valid
        }
    } while (status != EGuessStatus::OK);
    return userGuess;
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "WELL DONE! You're a Genius!\n";
    }
    else {
        std::cout << "Better luck next time, loser.\n";
    }
    
    return;
}

bool AskToPlayAgain() {
    FText response = " ";
    bool validResponse = true;
    std::cout << "Do you want to play again? (yes/no) ";
    std::getline(std::cin, response);
    
    do {
        if (response == "yes") {
            std::cout << std::endl;
            return true;
        }
        else if (response == "no") {
            std::cout << std::endl << "Thanks for playing!\n";
            std::cout << std::endl;
            std::cout << "          }   {  ___ " << std::endl;
            std::cout << "          (x x) (x x) " << std::endl;
            std::cout << "   /-------\\ /   \\ /-------\\ " << std::endl;
            std::cout << "  / | GOOD |x     x| BYE  | \\  " << std::endl;
            std::cout << " *  |------|       |------|  *  " << std::endl;
            std::cout << "    ^      ^       ^      ^ " << std::endl;
            return false;
        }
        else {
            std::cout << "Please enter either \"yes\" or \"no\"";
            validResponse = false;
        }
    }while (!validResponse);
    return false;
}






