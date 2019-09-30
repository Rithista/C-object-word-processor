/* Console executable using BullCow class 


*/
#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <list>
#include <vector>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//instantiate functions, prototypes
void StartText();
void PlayGame();
void PrintGuessHistory();
void PrintGameSummary();
void PrintHiddenWordLength();
void SetDifficulty();
bool AskToPlayAgain();
FText GetValidGuess();

FBullCowGame BCGame; // Game Instance

//program entry
int main() 
{
	do {
		BCGame.Reset();
		StartText();
		PlayGame();
	}
	while (AskToPlayAgain() == true);
	return 0; //exit program
}

void StartText() 
{
	//intro the game
	int32 WORD_LENGTH = 
	system("CLS");
	std::cout << "\n<==Yo Man welcome to Bulls n Cows word game, can you guess the ISOGRAM?==>" << std::endl;
	std::cout << "   An ISOGRAM is a word with no Repeating letters!" << std::endl;
	std::cout << "   Bull = Right Letter Right Place, Cow = Right Letter Wrong Place" << std::endl << std::endl;

}

void SetDifficulty() {
	FText difficultyInput = "";
	EDifficultStatus Status = EDifficultStatus::Invalid;
	bool IsNumDifficult = false;
	do {
		std::cout << "Please type 1 for EASY, 2 for NORMAL or 3 for HARD: ";
		std::getline(std::cin, difficultyInput);
		Status = BCGame.CheckDifficultValidity(difficultyInput);

		switch (Status) {
		case EDifficultStatus::Not_Number:
				std::cout << "Enter 1, 2 or 3 instead of that crap.";

		default:
			BCGame.Reset();
		}
	} while (Status != EDifficultStatus::OK);
	system("CLS");
	StartText();
	BCGame.SetDifficulty(difficultyInput);


}

void PlayGame() 
{
	//User sets difficulty so that the Isogram is set
	SetDifficulty();


	//game loop
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//while the game is not won
	//and there are tries remaining

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { 	//TODO for to while once we are validating tries

		PrintHiddenWordLength();
		FText Guess = GetValidGuess(); //TODO check for a valid guess and ask again if not valid

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//Submit valid guess to the game
		if (BCGame.IsGameWon()) {
			break;
		}


		PrintGuessHistory();

		std::cout << "Your guess was [" << Guess << "]" << std::endl;
		std::cout << "This has Bulls: " << BullCowCount.Bulls << " Cows: " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;

		//TODO make method thats prints all values in tuple history

	}
	//TODO Game summary
	PrintGameSummary();
}

void PrintHiddenWordLength() {
	std::cout << "===It is a " << BCGame.GetHiddenWordLength() << " letter word===" << std::endl << std::endl;
}


void PrintGuessHistory() {
	std::cout << "vv Previous Guesses vv" << std::endl;
	std::vector<std::pair<FString, std::pair<int32, int32>>>Guesses = BCGame.GetUserHistory();
	for (auto elem : Guesses) {
		std::cout << "[" << elem.first << "] B = " << elem.second.first << " , C = " << elem.second.second << std::endl;
	}
	std::cout << std::endl;
}


void PrintGameSummary() {

	bool winCondition = BCGame.IsGameWon();
	if (winCondition) {
		if (BCGame.GetCurrentTry() <= 2) {
			std::cout << "YOU MAD MAN, You got [" << BCGame.GetHiddenWord() << "] in One Guess WTF?!?!\n";
		}
		else {
			std::cout << "Well done you Guessed the word [" << BCGame.GetHiddenWord() << "]\n";
		}
	}
	else {
		std::cout << "Better luck next time, the word was [" << BCGame.GetHiddenWord() << "]!\n";
	}
	std::cout << std::endl;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'Y') || (Response[0] == 'y');
}

FText GetValidGuess() //TODO change to get valid guess
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTry = BCGame.GetMaxTries();

		std::cout << "Try (" << CurrentTry << "/" << MaxTry <<  ") Please enter your Guess: ";
		std::getline(std::cin, Guess);
		system("CLS");
		StartText();

		Status = BCGame.CheckGuessValidity(Guess);
		//TODO make a map method that prints back all the previous valid entries and their Bs and Cs
		switch (Status)
		{
		case EGuessStatus::Not_RightLength:
			PrintHiddenWordLength();
			PrintGuessHistory();
			std::cout << "Your guess was [" << Guess << "]" << std::endl;
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " Length word." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			PrintHiddenWordLength();
			PrintGuessHistory();
			std::cout << "Your guess was [" << Guess << "]" << std::endl;
			std::cout << "Please enter a Guess with no Repeating Letters." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			PrintHiddenWordLength();
			PrintGuessHistory();
			std::cout << "Your guess was [" << Guess << "]" << std::endl;
			std::cout << "Please enter a Guess that is Lower Case." << std::endl;
			break;
		default:
			return Guess;
		}

		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}
