#include "FBullCowGame.h"
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <unordered_set>
#include <fstream>
#include <time.h>
#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame()
{
	//LoadEasyDictionary;
	//LoadDictionary();
	//Reset();
}

int32 FBullCowGame::Reset()
{
	//const FString HIDDEN_WORD = "planet";
	//DifficultyLevel = EDifficultyLevel::Invalid;

	MyCurrentTry = 1;
	//MyWord = HIDDEN_WORD;
	
	bGameIsWon = false;
	return 0;
}



int32 FBullCowGame::DeterminePlayAgain(FString response)
{
	if (response[0] == 'Y' || response[0] == 'y') {
		return 2;
	}
	else if (response[0] == 'N' || response[0] == 'n') {
		return 1;
	}
	else {
		return 0;
	}
}


int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
int32 FBullCowGame::GetWordLength() const{return MyWord.length();}

EDifficultyResult FBullCowGame::CheckDifficultyValidity(FString response)
{
	if (response == "1\n" || response == "2\n" || response == "3\n") {
		return EDifficultyResult::OK;
	}
	return EDifficultyResult::Not_Valid_Response;
}
EDifficultyLevel FBullCowGame::GetDifficultyLevel() const
{
	return DifficultyLevel;
}
void FBullCowGame::SetDifficultyLevel(int32 level)
{

	switch (level) {
		case 1: //easy
			DifficultyLevel = EDifficultyLevel::Easy;
			break;
		case 2: //medium
			DifficultyLevel = EDifficultyLevel::Medium;
			break;
		case 3: //hard
			DifficultyLevel = EDifficultyLevel::Hard;
			break;
		default:
			break;
	}

	LoadEasyDictionary();
	LoadWord();
	
}
bool FBullCowGame::IsGameWon() { return bGameIsWon; };

int32 FBullCowGame::GetMaxTry() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,5}, {6,5} ,{7,5}, {8,6}, {9,6}, {10,7}, {11,8}, {12,9}, {13,10}, {14,12}, {15, 15}, {16,20} };


	return WordLengthToMaxTries[MyWord.length()]; 
}

bool FBullCowGame::IsPlaying()
{
	if (!IsGameWon() && MyCurrentTry <= GetMaxTry()) {
		return true;
	}
	return false;
}

//Checks the Guess Validity for correct word, and whether it is an isogram.
EValidityResult FBullCowGame::CheckGuessValidity(FString Guess)
{

	// check to see if the result is wrong word length.
	if (Guess.length() != GetWordLength()) {
		return EValidityResult::Wrong_Length;
	}
	else if (!IsLowercase(Guess)) {
		return EValidityResult::Not_LowerCase;
	}
	// check to see if the result is Isogram.
	else if (!IsIsogram(Guess)) {
		return EValidityResult::Not_Isogram;
	}
	else {
		return EValidityResult::OK;
	};
}

//Receives a valid guess, increments turn and checks word. 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment turn number
	MyCurrentTry++;
	//set up a return variable
	//loop through all letters in guess
	int32 bulls = 0;
	int32 cows = 0;
	int32 HiddenWordLength = MyWord.length();  //assuming same length as guess. 
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {


		// compare letters against guess
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {


			//if they match then
			if (tolower(Guess[GChar]) == tolower(MyWord[MHWChar])) {
				// if they're  in the same place
				if (MHWChar == GChar) {
					// increment bulls 
					bulls++;
				// else
				} else {
					// increment cows.
					cows++;
				}
			}
		}
	}
	FBullCowCount BullCowCount;
	BullCowCount.Bulls = bulls;
	BullCowCount.Cows = cows;
	if (bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

void FBullCowGame::LoadDictionary()
{
	if (DifficultyLevel == EDifficultyLevel::Invalid) {
		return;
	}
		std::ifstream ifs;
		FString word = "";

		ifs.open("words.txt", std::ifstream::in);

		char c = ifs.get();
		// randomly select a word from total word list.

		while (ifs.good()) {
			word += c;
			if (c == '\n') {
				if (word.length() <= WordLength) { // check to see word is within difficulty word length.
					if (IsIsogram(word)) { // check to see if word is an isogram.

						words.insert(word);

					}
				}
				word = "";
			}
			c = ifs.get();
		}
		ifs.close();

		return;

}



void FBullCowGame::LoadEasyDictionary()
{
	if (DifficultyLevel == EDifficultyLevel::Invalid) {
		return;
	}
	std::ifstream ifs;
	FString word = "";

	ifs.open("shortwords.txt", std::ifstream::in);

	char c = ifs.get();
	// randomly select a word from total word list.
	FWordLength length = DetermineWordLength();
	while (ifs.good()) {
		word += c;
		if (c == '\n') {
			//std::cout << length.beginning;
			//std::cout << length.end;
			//std::cout << word.length();
			if (length.beginning <= word.length() - 1) {
				if (word.length() - 1 <= length.end) {// check to see word is within difficulty word length.
					if (IsIsogram(word)) { // check to see if word is an isogram.
						word.pop_back();
					words.insert(word);

					}
				}
			}
			word = "";
		}
		c = ifs.get();
	}
	ifs.close();

	return;
}

void FBullCowGame::LoadWord()
{
	int iSecret;
	int count = 0;
	srand(time(NULL));
	iSecret = rand() % words.size();
	for (auto word : words) {
		count++;
		if (count == iSecret) {
			MyWord = word;
		}
	}

}

FWordLength FBullCowGame::DetermineWordLength()
{
	FWordLength length;
	switch (GetDifficultyLevel()) {
	case EDifficultyLevel::Easy:
		length.beginning = 3;
		length.end = 5;
		break;
	case EDifficultyLevel::Medium:
		length.beginning = 5;
		length.end = 7;
		break;
	case EDifficultyLevel::Hard:
		length.beginning = 5;
		length.end = 7;
		break;
	default:
		break;

	}
	return length;
}

FString FBullCowGame::RandomlySelectWordForGame()
{
	return FString();
}

bool FBullCowGame::IsLowercase(FString guess) const
{
	if (guess.length() < 1) { return true; }
	for (auto letter : guess) {
		if (!islower(letter)) {
			return false;
		}
	}
	return true;
}

/*
bool FBullCowGame::IsIsogram(FString Guess)
{
	// get length of Guess.

	int32 len = Guess.length();
	// if guess is same length as hidden word
	if (Guess.length() == MyWord.length()) {
		// use a sorting algorithm. 
		std::sort(Guess.begin(), Guess.end());
		
		bool isIsogram = true;
		// 
		//int32 count = (int32)(len * log(len));

		// check the contents after sorting. 
		for (int32 i = 0; i < (int32)Guess.length(); i++)
		{
			// make sure the loop doesn't exceed its limit. 
			if (i >= (int32)Guess.length() - 1)
			{
				break;
			}
			else
			{
				//count++;
				// if the loop is broken by same letters then break.
				if (Guess[i] == Guess[i + 1])
				{
					isIsogram = false;
					break;
				}
			}
		}

		if (isIsogram) {
			return isIsogram;
		}
	}
	else {
		return false;
	}
	return false;
}
*/

bool FBullCowGame::IsIsogram(FString guess) const
{
	//treat 0 and 1 letter words as isograms
	if (guess.length() <= 1) {return true;}

	//set up our map
	TMap<char, bool> LetterSeen;
	// search the guess word for double characters
	for (auto letter : guess) {
		letter = tolower(letter); //handle mixed case
		if (LetterSeen[letter]) {// If letter is in map,
			return false;//break and Is Not Isogram
		} else {// otherwise
			LetterSeen[letter] = true;//add character to map
		
		}
	}
	// default is it is Isogram.
	return true;
}


std::map<char,int> FBullCowGame::NORDER(FString)
{
	// this loop is using a map. however.. in the look up in map you will be searching each item in map for the letter.
	// let's say we have the word challenge, which we know has double ups.
	// putting in map.... chal and then fail.
	// first loop will run 0 since the map is empty, add c
	// second loop will run 1 since the map has c, and add h
	// third loop will run twice since the map has c and h, and adds a
	// fourth loop will run three times since the map has c and h and a, and adds l
	// fifth loop will run 4 times since the map has c,h,a and l and fails because it finds another l
	// this means the loop is run... 15 times before failing on this word (since 
	// if you go for a nlogn sort... meaning.... for this.... 30 possible runs... clearly the number is higher.... 
	// however 30 sorting opportunities means (plus the 10 for checking) that it may pick up quicker.
	// ie.... c does not find itself again... after 10 tries.
	// h does not find itself again... after 10 tires
	// a does not fin itself again... after 10 tries. and it's over.
	// if you be doing something in the comparisons there... ie.... doing something with the letters c compares to... (ie storing them in map)
	std::map<char, int> map;
	FString word = "challenge";
	for (int32 i = 0; i < word.length(); i++) {
		// search map
		map[word[i]] = i;






	}
	return map;
}




