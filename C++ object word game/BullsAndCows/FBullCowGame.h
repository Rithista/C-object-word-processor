#pragma once
#include <string>
#include <tuple>
#include <list>
#include <map>
#include <vector>
#define TMap std::map

//heyy
using FString = std::string;
using int32 = int;


struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};


enum class EGuessStatus {
	Invalid,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Not_RightLength
	
};

enum class EDifficultStatus {
	Invalid,
	OK,
	Not_Number
};

class FBullCowGame {
public:
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	std::vector<std::pair<FString, std::pair<int32, int32>>>GetUserHistory();

	FString GetHiddenWord() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	EDifficultStatus CheckDifficultValidity(FString) const;


	void Reset(); //TODO make richer return
	void SetDifficulty(FString);
	FBullCowCount SubmitValidGuess(FString);




private:
	//init on constructor
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyDifficulty;
	FString MyHiddenWord;
	bool bIsGameWon;
	std::vector<std::pair<FString, std::pair<int32, int32>>>GuessMap;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	FString SetIsogram();
};