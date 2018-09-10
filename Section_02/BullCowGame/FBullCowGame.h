#pragma once
#include <string>
#include <map>

using int32 = int;
using FString = std::string;

//all values initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//another way to do Validity would be to use enum

enum class EValidityResult
{
	OK = 1,
	Not_Isogram = 2,
	Wrong_Length = 3,
	Not_LowerCase = 4
};



//Sent to console. IsWord = correct word. IsIsogram = Word is an Isogram. Word = Hidden Word. 
struct ValidityResult
{
	bool IsWord = false;
	bool OKAY = false;
	bool IsWrongLength = false;
	bool IsLowerCase = false;
	FString Word = "";
};

class FBullCowGame
{
public:
	FBullCowGame();
	int32 Reset(); // TODO make a return type for more descriptive function
	int32 DeterminePlayAgain(FString response);
	int32 GetMaxTry() const;
	int32 GetCurrentTry() const;
	int32 GetWordLength() const;
	bool IsPlaying();
	bool IsGameWon();
	EValidityResult CheckGuessValidity(FString);
	//provide a method for counting bulls and cows and increasing turn #
	FBullCowCount SubmitValidGuess(FString);
	std::map<char,int> NORDER(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTry;
	FString MyWord;
	bool bGameIsWon = false;
	FString RandomlySelectWordForGame();
	bool IsLowercase(FString) const;
	bool IsIsogram(FString word) const;
	
	
	

};