#include <iostream>
#include <random> // for std::mt19937
#include <ctime> // for std::time

int getAnswer()
{
    // Initialize our mersenne twister with a random seed based on the clock
	std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    // Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution<> hiLoAnswer(1, 100);
    int answer = hiLoAnswer(mersenne);

    return answer;
}

int getGuess(int guessCount)
{
    while (true)
    {
        std::cout << "Guess #" << guessCount << ":";
        int guess { 0 };
        std::cin >> guess;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767,'\n');
            std::cout << "Oops, that input is invalid. Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767,'\n');

            return guess;
        }
    }
}

int playGame()
{
    std::cout << "Let's play a game. I'm thinking of a number between 1-100. You have 7 tries to guess what it is.\n";

    int answer = getAnswer(); // Generate random answer for game
    for (int guessCount = 1; guessCount <= 7; ++guessCount)
    {
        int guess { getGuess(guessCount) };
        if (answer != guess)
        {
            if (guess > answer)
                std::cout << "Your guess is too high.\n";
            else
                std::cout << "Your guess is too low.\n";
        }
        else
        {
            std::cout << "Correct! You win!\n";
            return 1;
        }
    }

    std::cout << "Sorry, you lose. The correct number was " << answer << ".\n";
    return 0;    
}

int playAgain()
{
    while (true) // Loop until user gets a valid answer
    {
        std::cout << "Would you like to play again (y/n)? ";
        char c { 'n' };
        std::cin >> c;

        if (c == 'y')
            return true;
        else if (c == 'n')
            return false;
        else
            continue;
    }
}

int main()
{
    do
    {
        playGame();
    } 
    while (playAgain());

    std::cout << "Thank you for playing.\n";
    return 0;
}