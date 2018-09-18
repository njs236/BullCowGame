/* This is the console executable, that makes use of the FBullCowGame class
this acts as a view in a MVC pattern, and is responsible for all user
interaction. For game logic, see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#include <vector>
#include <stdlib.h>


FBullCowGame game;

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void DisplayIntroduction();
void StartGame();
bool AskDifficulty();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
std::vector<char> extract_keys(std::map<char, int> const& input_map);

std::vector<char> extract_keys(std::map<char, int> const& input_map)
{
	std::vector<char> retval;
	for (auto const& element : input_map) {
		retval.push_back(element.first);
	}
	return retval;
};



int main()
{
	
	game = FBullCowGame();
	/*
	std::map<char, int> map = game.NORDER("blah");

	std::vector<char> keys = extract_keys(map);

	for (int32 i = 0; i < keys.size(); i++) {
		std::cout << "key: " << keys[i];
	}
	*/
	bool bPlayAgain = false;
	
	do {
		DisplayIntroduction();
		AskDifficulty();
		StartGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	
	return 0;

}


void DisplayIntroduction() {

	std::cout << "\n\n" << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << std::endl;
	std::cout << " }____{                  ___" << std::endl;
	std::cout << " /    \\                 /   \\" << std::endl;
	std::cout << "(O  O )                (O  O)        " << std::endl;
	std::cout << " \\   /____(\\     /)____\\   /     " << std::endl;
	std::cout << "  \\ / BULL| \\   / | COW \\ /          " << std::endl;
	std::cout << "   O-,----/  *  * \\------O             " << std::endl;
	std::cout << "    \\^    \\^       \\^    \\^            " << std::endl;
	std::cout << "If you get a letter correct in the right place, you will get a bull. \n";
	std::cout << "If you get a letter correct but in the wrong place, you'll get a cow. \n";
	
	

	
}

FText GetValidGuess() {
	
	bool bGuessIsValid = false;
	FText Guess = "";
	
	do {
		// Display Try Number.
		std::cout << "Try " << game.GetCurrentTry() << " of " << game.GetMaxTry() << ". ";
		// Enter your guess
		std::cout << "Enter your guess: ";
		
		getline(std::cin, Guess);
		//Check guess validity
		EValidityResult ValidityResult = game.CheckGuessValidity(Guess);
		switch (ValidityResult) {
		case EValidityResult::OK:
			bGuessIsValid = true;
			break;
		case EValidityResult::Not_LowerCase:
			std::cout << "Guess needs to be a lower case word with a " << game.GetWordLength() << " letter Isogram. Please type again.\n\n";
			break;
		default:
			std::cout << game.GetWordLength() << " letter isogram required. Please type again.\n\n";
		}
	} while (!bGuessIsValid); //only when guess is not valid. 
	return Guess;
}



// Plays game until completion
void StartGame() {

	// Reset Game.
	
	game.Reset();
	
	// Loop while game is playing.
	while (game.IsPlaying()) {

		
		FText Guess = GetValidGuess(); 
		// ValidGuesses:
		// only responds if it is valid input
		
		//submit valid guess
		FBullCowCount BullCowCount = game.SubmitValidGuess(Guess);
			
		// condition of win or other guess (see documentation for use case)
		// I liked the result being given as a simple boolean rather than interfering with game logic in console. 
		if (game.IsGameWon()) {
			
		}
		else {
			std::cout << BullCowCount.Bulls << " Bulls " << BullCowCount.Cows << " Cows. What will you guess now?" << "\n\n";
		}
	}

	PrintGameSummary();
		


}

void PrintGameSummary()
{
	if (game.IsGameWon()) {
		std::cout << "Yes you guessed the word! " << "\n\n";
	} else {
		std::cout << "BETTER LUCK NEXT TIME! " << "\n\n";
	}


}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? ";
	bool bPlayAgainValid = false;
	do {
		// prompt to enter to play again. 
		FText Response = "";
		getline(std::cin, Response);
		EPlayAgainResult response = game.DeterminePlayAgain(Response);
		if (response == EPlayAgainResult::Yes) {
			system("CLS");
			return true;
		}
		else if (response == EPlayAgainResult::No) {

			return false;
		}
		else {
			std::cout << "Invalid Response!" << std::endl;
		}
	} while (!bPlayAgainValid);
	return false;
}

bool AskDifficulty()
{
	std::cout << "Choose Difficulty Level: (1 - 3)\n ";
	bool bDifficultValid = false;
	do {
		// prompt to enter difficulty level
		char Response[256];
		fgets(Response, 256, stdin);
		int32 i = atoi(Response);
		//Check to see if prompt is valid input. 
		EDifficultyResult response = game.CheckDifficultyValidity(Response);
		// Prompt is Valid then
		if (response == EDifficultyResult::OK) {
			bDifficultValid = true;
			// Set difficulty level. 
			game.SetDifficultyLevel(i);
			// Respond with what difficulty level they have chosen. 
			switch (game.GetDifficultyLevel()) {
			case EDifficultyLevel::Easy:
				std::cout << "You've chosen difficulty Level Easy. \n\n";
				break;
			case EDifficultyLevel::Medium:
				std::cout << "You've chosen difficulty Level Medium.\n\n";
				break;
			case EDifficultyLevel::Hard:
				std::cout << "You've chosen difficulty Level Hard.\n\n";
				break;
			default:
				break;

			}
		}
		else {
			std::cout << "Invalid Response!" << std::endl;

		}
	} while (!bDifficultValid);
	std::cout << "You have " << game.GetMaxTry() << " tries to guess the word. ";
	std::cout << "Can you guess the " << game.GetWordLength() << " letter isogram I'm thinking of?" << std::endl << "\n";
	return false;
}
