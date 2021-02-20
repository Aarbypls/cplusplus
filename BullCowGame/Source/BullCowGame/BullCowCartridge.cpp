// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

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
    // TO DO: validate hidden word IF they don't add it in

    if (Guess == HiddenWord)
    {
        ClearScreen();
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The word has %i letters.\nTry guessing again."), HiddenWord.Len());
        return;    
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Your guess was not an isogram.\nThe word has no repeating letters.\nTry guessing again."));
        return;
    }

    // Incorrect guess; remove a life
    PrintLine(TEXT("That guess was incorrect. You lost a life!"));
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

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    // One letter words are by definition isograms   
    if (Word.Len() == 1)
    {
        return true;
    }

    // Iterate through, checking each letter against the others for duplicates
    for (int32 Index = 0; Index < Word.Len() - 1; Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}