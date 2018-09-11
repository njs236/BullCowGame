#pragma once
#include <string>
#include <map>
#include <unordered_set>
#include <fstream>

using int32 = int;
using FString = std::string;

//all values initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

struct FWordLength
{
	int32 beginning = 0;
	int32 end = 0;
};

//another way to do Validity would be to use enum

enum class EDifficultyResult
{
	OK = 1,
	Not_Valid_Response = 2
};
enum class EValidityResult
{
	OK = 1,
	Not_Isogram = 2,
	Wrong_Length = 3,
	Not_LowerCase = 4
};

enum class EDifficultyLevel
{
	Easy = 5,
	Medium = 7,
	Hard = 10,
	Invalid = 12
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
	EDifficultyResult CheckDifficultyValidity(FString);
	EDifficultyLevel GetDifficultyLevel() const;
	void SetDifficultyLevel(int32);
	bool IsPlaying();
	bool IsGameWon();
	EValidityResult CheckGuessValidity(FString);
	//provide a method for counting bulls and cows and increasing turn #
	FBullCowCount SubmitValidGuess(FString);
	std::map<char,int> NORDER(FString);

private:
	int32 MyCurrentTry;
	EDifficultyLevel DifficultyLevel ;
	int32 WordLength;
	FString MyWord;
	void LoadDictionary();
	void LoadEasyDictionary();
	void LoadWord();
	FWordLength DetermineWordLength();
	std::unordered_set<FString> words;
	bool bGameIsWon = false;
	FString RandomlySelectWordForGame();
	bool IsLowercase(FString) const;
	bool IsIsogram(FString word) const;
	

};