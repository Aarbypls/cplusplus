// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // welcome the player
    PrintLine(TEXT("Welcome to the Bull Cows game!"));
    PrintLine(TEXT("Guess the 4 letter word.")); // magic number - remove
    PrintLine(TEXT("Press the ENTER key to continue."));

    SetupGame();

    // Prompt Player For Guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // Checking PlayerGuess
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
    }
    else
    {
        PrintLine(TEXT("You have lost!"));
    }

    // check if isogram
    // Prompt to guess again if not isogram
    // check if right number of letters
    // Prompt to guess again if wrong # of letters

    // remove a life

    // check if lives > 0
    // if yes GuessAgain
    // Show Lives Left
    // if no show GameOver and HiddenWord
    // Prompt PlayAgain, Press Enter -> PlayAgain?
    // Check user input
    // Play again or quit
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    Lives = 4;
}