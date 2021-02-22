// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    // Load all words from the HiddenWordList txt file and set them to an array
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    // Check that words are 1) isograms, 2) between 4 and 8 letters long, inclusive
    Isograms = GetValidWords(Words);    

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ClearScreen();        
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcome the player
    PrintLine(TEXT("Welcome to the Bull Cows game!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type your guess, then ENTER to continue."));
    PrintLine(TEXT("Bulls = right letter in right spot\nCows = right letter in wrong spot"));

    // DEBUG LINE - COMMENT OUT
    // PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); 
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

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
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
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        EndGame();
        return;
    }

    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows."), Score.Bulls, Score.Cows);

    PrintLine(TEXT("%i lives remaining."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 &&
            Word.Len() <= 8 &&
            IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    // Bulls = correct letter in correct spot
    // Cows = correct letter in wrong spot
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 ComparisonIndex = 0; ComparisonIndex < HiddenWord.Len(); ComparisonIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[ComparisonIndex])
            {
                Count.Cows++;
                break;
            }
        }       
    }
    
    return Count;
}