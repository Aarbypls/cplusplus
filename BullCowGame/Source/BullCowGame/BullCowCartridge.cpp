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
    else
    {
        ProcessGuess(Input);
    }
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

    if (Lives <= 0)
    {
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s."), *HiddenWord);        
    }
    else
    {
        PrintLine(TEXT("You guessed correctly! You win!"));
    }

    PrintLine(TEXT("\nPress ENTER to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        ClearScreen();
        EndGame();
        return;
    }

    // check if right number of letters
    // Prompt to guess again if wrong # of letters
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The word has %i letters.\nTry guessing again."), HiddenWord.Len());
        return;    
    }

    // check if isogram
    // Prompt to guess again if not isogram   
    // if (!IsIsogram)
    // {
    //     PrintLine(TEXT("The word has no repeating letters.\nTry guessing again."));
    //     return;
    // }

    // remove a life, show lives left
    PrintLine(TEXT("You lost a life!"));
    PrintLine(TEXT("%i lives remaining."), --Lives);

    if (Lives <= 0)
    {
        ClearScreen();
        EndGame();
        return;
        // Play again or quit    
        // Prompt PlayAgain, Press Enter -> PlayAgain?
    }
}