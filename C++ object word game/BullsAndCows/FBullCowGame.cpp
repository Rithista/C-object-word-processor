#include "FBullCowGame.h"
#include <map>
#include <time.h> 
#include <stdlib.h>
#include <tuple>
#include <list>
#include <vector>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}



int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

std::vector<std::pair<FString, std::pair<int32, int32>>> FBullCowGame::GetUserHistory(){ return GuessMap; }

int32 FBullCowGame::GetMaxTries() const {
	
	TMap<int32, int32> WordLengthToTries{ {2,3}, {3,6}, {4,9}, {5,12}, {6,15}, {7, 20}, {8, 24} };
	
	
	return WordLengthToTries[GetHiddenWordLength()]; 


}



FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }

bool FBullCowGame::IsGameWon() const { return bIsGameWon; }




void FBullCowGame::Reset()
{

	FString HIDDEN_WORD = SetIsogram();
	MyHiddenWord = HIDDEN_WORD;

	GuessMap.clear();

	MyCurrentTry = 1;
	bIsGameWon = false;
	

	return;
}

void FBullCowGame::SetDifficulty(FString difficulty)
{
	MyDifficulty = difficulty;
}

//valid guess comes in
//increment try number because it was an actual user guess
//returns how many bulls and cows they have
FBullCowCount FBullCowGame::SubmitValidGuess(FString MyGuess)
{
	//increment turn number
	MyCurrentTry++;
	FString Guess = MyGuess;

	//return structure variable
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();
	//loop through all guess letter
	for(int32 i = 0; i < WordLength; i++){
		for (int32 j = 0; j < WordLength; j++) {
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	//Add the guess and turn to the tuple history
	GuessMap.push_back(std::make_pair(Guess, std::make_pair(BullCowCount.Bulls, BullCowCount.Cows)));

	return BullCowCount;
}





EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Not_RightLength;
	}
	return EGuessStatus::OK;
}

EDifficultStatus FBullCowGame::CheckDifficultValidity(FString input) const
{
	if (input == "1" || input == "2" || input == "3") {
		return EDifficultStatus::OK;
		MyDifficulty == input;
	}
	return EDifficultStatus::Not_Number;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> isoMap;
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (isoMap[Letter]) {
			return false;
		}
		else {
			isoMap[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

FString FBullCowGame::SetIsogram()
{
	if (MyDifficulty == "1") {
		FString easyIsograms[10] = {
		"bat", "hot", "sky", "run", "mug", "bath", "cow", "bike", "cat", "lamp"
		};
		srand(time(NULL));
		return easyIsograms[rand() % 10];
	}
	else if (MyDifficulty == "2") {
		FString normalIsograms[10] = {
		"adult", "horse", "light", "plant", "mouse", "board", "count", "stand", "speak", "reign"
		};
		srand(time(NULL));
		return normalIsograms[rand() % 10];
	}
	else {
		FString hardIsograms[10] = {
		"kitchen", "rocket", "country", "planet", "minature", "slanted", "washing", "project", "display", "sandwich"
		};
		srand(time(NULL));
		return hardIsograms[rand() % 10];
	}

	
}


