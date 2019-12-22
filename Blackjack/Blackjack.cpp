#include <iostream>
#include <array>
#include <random> // for std::mt19937
#include <ctime> // for std::time
#include <cstdlib> // for rand() and srand()

enum CardRank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    MAX_RANKS
};

enum CardSuit
{
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    SUIT_SPADE,
    MAX_SUITS
};

struct Card
{
    CardRank rank;
    CardSuit suit;
};

void printCard(const Card &card)
{
    switch(card.rank)
    {
        case RANK_2: std::cout << '2'; break;
        case RANK_3: std::cout << '3'; break;
        case RANK_4: std::cout << '4'; break;
        case RANK_5: std::cout << '5'; break;
        case RANK_6: std::cout << '6'; break;
        case RANK_7: std::cout << '7'; break;
        case RANK_8: std::cout << '8'; break;
        case RANK_9: std::cout << '9'; break;
        case RANK_10: std::cout << 'T'; break;
        case RANK_JACK: std::cout << 'J'; break;
        case RANK_QUEEN: std::cout << 'Q'; break;
        case RANK_KING: std::cout << 'K'; break;
        case RANK_ACE: std::cout << 'A'; break;
    }
    
    switch(card.suit)
    {
        case SUIT_CLUB: std::cout << 'C'; break;
        case SUIT_DIAMOND: std::cout << 'D'; break;
        case SUIT_HEART: std::cout << 'H'; break;
        case SUIT_SPADE: std::cout << 'S'; break;
    }
}

void printDeck(const std::array<Card, 52> &deck)
{
    for (const auto &card : deck)
    {
        printCard(card);
        std::cout << " ";
    }

    std::cout << "\n";
}

void swapCard(Card &card1, Card &card2)
{
    Card temp = card1;
    card1 = card2;
    card2 = temp;
}

void shuffleDeck(std::array<Card, 52> &deck)
{
    // Initialize our mersenne twister with a random seed based on the clock
	std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    // Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution<> randomCard(0, 51);

    // for (int i = 0; i < 6; ++i)
    // {
    //     printCard(deck[randomCard(mersenne)]);
    //     std::cout << ' ';
    // }

    using index_t = std::array<Card, 52>::size_type;
    for (index_t index = 0; index < 52; ++index)
    {
        index_t swapIndex = randomCard(mersenne);
        swapCard(deck[index], deck[swapIndex]);
    }
}

// void getValue(Card &card)
// {
    
// }

int main()
{
    // // Personal solution for deck printing
    // // for (std::array<int, 4>::size_type i { 0 }; i < MAX_SUITS; ++i) // everything in one for loop
    // Card cardTemp = {};
    // int counter { 0 };
    // std::array<Card, 52> deck {};
    // for (int suitIdx { 0 }; suitIdx < MAX_SUITS; ++suitIdx) // iterate through suits
    // {
    //     for (int rankIdx = 0; rankIdx < MAX_RANKS; ++rankIdx) // iterate through ranks
    //     {
    //         cardTemp = { static_cast<CardRank>(rankIdx), static_cast<CardSuit>(suitIdx) }; 
    //         deck[counter] = cardTemp;
    //         ++counter;
    //     }
    // }

    // We could initialize each card individually, but that would be a pain.  Let's use a loop.
    std::array<Card, 52> deck;
	using index_t = std::array<Card, 52>::size_type;
	index_t card = 0;
	for (int suit = 0; suit < MAX_SUITS; ++suit)
	for (int rank = 0; rank < MAX_RANKS; ++rank)
	{
		deck[card].suit = static_cast<CardSuit>(suit);
		deck[card].rank = static_cast<CardRank>(rank);
		++card;
	}
    
    printDeck(deck);

    // swapCard(deck[0], deck[1]);
    shuffleDeck(deck);

    printDeck(deck);

    // getValue();

    return 0;
}