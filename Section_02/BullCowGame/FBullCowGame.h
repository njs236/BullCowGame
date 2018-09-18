/* the game logic (no view code)
Guess a word like mastermind */

#pragma once
#include <string>
#include <map>
#include <unordered_set>
#include <fstream>

// make syntax Unreal friendly
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

struct FEasyDifficulty
{
	int32 Easyshort = 3;
	int32 Easylong = 5;
	int32 words = 10;

};
struct FMediumDifficulty
{
	int32 Mediumshort = 6;
	int32 Mediumlong = 7;
	int32 words = 10;

};
struct FHardDifficulty
{
	int32 Hardshort = 8;
	int32 Hardlong = 9;
	int32 words = 10;

};
struct FInsaneDifficulty
{
	int32 Insaneshort = 10;
	int32 Insanelong = 16;
	int32 words = 10;

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

enum class EPlayAgainResult
{
	Yes = 1,
	No = 2,
	Same = 3,
	Default = 4,
	Not_Valid_Response = 5
};

enum class EDifficultyLevel
{
	Easy = 5,
	Medium = 7,
	Hard = 10,
	Insane = 11,
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
	EPlayAgainResult DeterminePlayAgain(FString response);
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