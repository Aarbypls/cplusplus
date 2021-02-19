// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // debug line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You have won!"));
            EndGame();
        }
        else 
        {
            PrintLine(TEXT("You lost a life!"));
            PrintLine(TEXT("%i lives remaining."), --Lives);
            if (Lives > 0)
            {
                if (Input.Len() != HiddenWord.Len())
                {
                    PrintLine(TEXT("The word has %i letters.\nTry guessing again."), HiddenWord.Len());
                }
            }
            else
            {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            }
        }
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
    // welcome the player
    PrintLine(TEXT("Welcome to the Bull Cows game!"));

    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and\npress ENTER to continue."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("Press ENTER to play again."));
}