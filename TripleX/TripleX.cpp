#include <iostream>
#include <string>
#include <ctime> 

void PrintASCIILogo()
{
    // ASCII art created with https://manytools.org/hacker-tools/ascii-banner/
    std::cout << R"(
  ______    ____     ____    ____     __     ______          _  __
 /_  __/   / __ \   /  _/   / __ \   / /    / ____/         | |/ /
  / /     / /_/ /   / /    / /_/ /  / /    / __/            |   / 
 / /     / _, _/  _/ /    / ____/  / /___ / /___           /   |  
/_/     /_/ |_|  /___/   /_/      /_____//_____/          /_/|_| 
==================================================================                                                                                                                                                                                                                       
    )";
}

void PrintIntroduction(int Difficulty)
{
    std::cout << "\nYou are a secret agent breaking into a Level " << Difficulty;
    std::cout << " secure server room...\nYou need to enter the correct codes in order to continue...\n\n";
}

bool PlayGame(int Difficulty)
{
    PrintIntroduction(Difficulty);

    // Declare 3 number code
    const int CodeA = rand() % Difficulty + Difficulty + 1;
    const int CodeB = rand() % Difficulty + Difficulty + 1;
    const int CodeC = rand() % Difficulty + Difficulty + 1;

    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    // Print hints for user to guess correct numbers
    std::cout << "* There are three numbers in the code.\n";
    std::cout << "* The codes add up to: " << CodeSum << "\n";
    std::cout << "* The codes multiply to give: " << CodeProduct << "\n\n";

    // Store player guess and get input
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;    

    // Check for win/lose case
    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std::cout << "\nYou have successfully broken into the server room!\nYou proceed to the next room.\n";
        return true;
    }
    else
    {
        std::cout << "\nWrong answer! An alarm goes off. Try again!\n";
        return false;
    }
}

int main()
{
    srand(time(NULL));
    PrintASCIILogo();

    int LevelDifficulty = 1;
    const int MaxDifficulty = 5;

    // Loop game until all levels are completed
    while (LevelDifficulty <= MaxDifficulty)
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);

        std::cin.clear(); // clears any errors
        std::cin.ignore(); // discards the buffer

        if (bLevelComplete)
        {
            ++LevelDifficulty;
        }
    }

    std::cout << "\nYou have successfully broken into all of the server rooms! Congratulations!\n";

    return 0;
}