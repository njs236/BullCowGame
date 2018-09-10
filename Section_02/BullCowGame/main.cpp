/* This is the console executable, that makes use of the FBullCowGame class
this acts as a view in a MVC pattern, and is responsible for all user
interaction. For game logic, see the FBullCowGame class.
*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#include <vector>

FBullCowGame game;

using FText = std::string;
using int32 = int;

void DisplayIntroduction();
void StartGame();
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
	//while (true) {
	bool bPlayAgain = false;
	
	do {
		DisplayIntroduction();
		StartGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	
	
	//}
	
	return 0;

}


void DisplayIntroduction() {
	// This code is not going to change, so I have put it in its own function.
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
	std::cout << "You have " << game.GetMaxTry() << " tries to guess the word. ";
	std::cout << "Can you guess the " << game.GetWordLength() << " letter isogram I'm thinking of?" << std::endl << "\n";

	
}

FText GetValidGuess() {
	
	bool bGuessIsValid = false;
	FText Guess = "";
	
	do {
		std::cout << "Try " << game.GetCurrentTry() << " of " << game.GetMaxTry() << ". ";
		std::cout << "Enter your guess: ";
		
		getline(std::cin, Guess);
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
	} while (!bGuessIsValid);
	return Guess;
}



// Handling of the game on screen. 
void StartGame() {

	// Reset Game.
	game.Reset();
	// Loop while game is playing.
	while (game.IsPlaying()) {
		// Display Try Number.
		
		FText Guess = GetValidGuess(); 
		// ValidGuesses:
		// only responds if it is valid input
		
		//submit valid guess
		FBullCowCount BullCowCount = game.SubmitValidGuess(Guess);
			
		// condition of win or other guess (see documentation for use case)
		// TODO: keep the logic of the game being won discrete from the view.
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
	std::cout << "Do you want to play again with the same word? ";

	// these are the valid responses given.
	FText Response = "";
	getline(std::cin, Response);
	int32 response = game.DeterminePlayAgain(Response);
	if (response == 2) {
		return true;
	}
	else if (response == 1) {

		return false;
	}
	else {
		std::cout << "Invalid Response!" << std::endl;
		AskToPlayAgain();
	}
	return false;
}
