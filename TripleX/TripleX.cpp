#include <iostream>

int main()
{
    // Print starting messages to the terminal
    std::cout << std::endl;
    std::cout << "You are a secret agent breaking into a secure server room...";
    std::cout << std::endl;
    std::cout << "You need to enter the correct codes in order to continue..." << std::endl;

    // Declare 3 number code
    const int CodeA = 4;
    const int CodeB = 3;
    const int CodeC = 2;

    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    // Print hints for user to guess correct numbers
    std::cout << std::endl;
    std::cout << "* There are three numbers in the code." << std::endl;
    std::cout << "* The codes add up to: " << CodeSum << std::endl;
    std::cout << "* The codes multiply to give: " << CodeProduct << std::endl;

    int GuessA, GuessB, GuessC;

    std::cin >> GuessA;
    std::cin >> GuessB;
    std::cin >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;    

    std::cout << "You entered: " << GuessA << GuessB << GuessC;

    return 0;
}