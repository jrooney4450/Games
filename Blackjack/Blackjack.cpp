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
        case RANK_2:     std::cout << '2'; break;
        case RANK_3:     std::cout << '3'; break;
        case RANK_4:     std::cout << '4'; break;
        case RANK_5:     std::cout << '5'; break;
        case RANK_6:     std::cout << '6'; break;
        case RANK_7:     std::cout << '7'; break;
        case RANK_8:     std::cout << '8'; break;
        case RANK_9:     std::cout << '9'; break;
        case RANK_10:    std::cout << 'T'; break;
        case RANK_JACK:  std::cout << 'J'; break;
        case RANK_QUEEN: std::cout << 'Q'; break;
        case RANK_KING:  std::cout << 'K'; break;
        case RANK_ACE:   std::cout << 'A'; break;
    }
    
    switch(card.suit)
    {
        case SUIT_CLUB:    std::cout << 'C'; break;
        case SUIT_DIAMOND: std::cout << 'D'; break;
        case SUIT_HEART:   std::cout << 'H'; break;
        case SUIT_SPADE:   std::cout << 'S'; break;
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

    using index_t = std::array<Card, 52>::size_type;
    for (index_t index = 0; index < 52; ++index)
    {
        index_t swapIndex = randomCard(mersenne);
        swapCard(deck[index], deck[swapIndex]);
    }
}

int getCardValue(Card &card)
{
    switch(card.rank)
    {
        case RANK_2:     return 2;
        case RANK_3:     return 3;
        case RANK_4:     return 4;
        case RANK_5:     return 5;
        case RANK_6:     return 6;
        case RANK_7:     return 7;
        case RANK_8:     return 8;
        case RANK_9:     return 9;
        case RANK_10:    return 10;
        case RANK_JACK:  return 10;
        case RANK_QUEEN: return 10;
        case RANK_KING:  return 10;
        case RANK_ACE:   return 11;
    }

    return 0;
}

int getHandValue(std::vector<Card> &handOut)
{
    int count { 0 };
    for (std::size_t i=0; i < handOut.size(); ++i)
    {
        count += getCardValue(handOut[i]);
    }
    return count;
}

void printHand(std::vector<Card> &handOut)
{
    for (std::size_t i=0; i < handOut.size(); ++i)
    {
        printCard(handOut[i]);
        std::cout << ' ';
    }
}

bool hitMe()
{
    while (true) // Loop until user gets a valid answer
    {
        std::cout << "Would you like to hit or stand (h/s)? ";
        char c { 's' };
        std::cin >> c;

        if (c == 'h')
            return true;
        else if (c == 's')
            return false;
        else
            continue;
    }
}

void playBlackjack(std::array<Card, 52> &deck)
{
    shuffleDeck(deck);

    // Initialize player and dealer hand's as vectors
    std::vector<Card> dealerHand;
    std::vector<Card> playerHand;
    int deckIndex { 0 };

    // dealer draws one card up and one card down, print to console and store to dealer's hand
    std::cout << "The dealer's first card is: ";
    printCard(deck[deckIndex]);
    std::cout << '\n';
    dealerHand.push_back(deck[deckIndex]);

    // Store dealer's second card to hand but dont print to console
    ++deckIndex;
    dealerHand.push_back(deck[deckIndex]);


    // player is dealt two cards, print to console and store to player's hand
    ++deckIndex;
    std::cout << "Your hand is: ";
    printCard(deck[deckIndex]);
    playerHand.push_back(deck[deckIndex]);
    std::cout << ' ';

    // Player second card
    ++deckIndex; 
    printCard(deck[deckIndex]);
    playerHand.push_back(deck[deckIndex]);
    std::cout << '\n';

    int playerVal {0};
    int dealerVal {0};

    // Player draw phase
    bool isHitMe {true};
    bool isPlayerBust {false};
    isHitMe = hitMe();

    while (isHitMe)
    {
        ++deckIndex;
        playerHand.push_back(deck[deckIndex]);
        std::cout << "Your hand is: ";
        printHand(playerHand);
        std::cout << '\n';

        playerVal = getHandValue(playerHand);

        if (playerVal > 21) // player loses
        {
            isPlayerBust = true;
            std::cout << "Player Bust... Dealer wins... D:\n";
            break;
        }
        else if (playerVal == 21)
        {
            std::cout << "Blackjack! Let's hope the dealer doesn't also have blackjack.\n";
            break;
        }
        isHitMe = hitMe();
    }

    // Dealer draw phase
    bool isDealerBust {false};

    playerVal = getHandValue(playerHand);
    dealerVal = getHandValue(dealerHand);
    
    if (isPlayerBust == false)
    {
        std::cout << "The dealer flips the hidden card. Dealer's hand is: ";
        printHand(dealerHand);
        std::cout << '\n';
    }

    while (isPlayerBust == false)
    {
        if (dealerVal < 17)
        {
            std::cout << "Dealer draws again\n";
            ++deckIndex;
            dealerHand.push_back(deck[deckIndex]);
            dealerVal += getCardValue(deck[deckIndex]);
            printHand(dealerHand);
            std::cout << '\n';
        }
        else if (dealerVal > 21)
        {
            isDealerBust = true;
            std::cout << "Dealer Bust!! You Win!!\n";
            break;
        }
        else
            break;
    }

    if (isPlayerBust == false && isDealerBust == false)
    {
        std::cout << "dealer's score is " << dealerVal << " player's score is " << playerVal << '\n';

        if (dealerVal > playerVal)
        {
            std::cout << "dealer wins... D:\n";
        }
        else if (dealerVal < playerVal)
        {
            std::cout << "You win!!\n";
        }
        else
        {
            std::cout << "it's a tie, the dealer wins... D:\n";
        }
    }
}

int main()
{
    // // Initialize deck personal solution
    // // for (std::array<int, 4>::size_type i { 0 }; i < MAX_SUITS; ++i) // everything in one for loop
    // // using index_t = std::array<Card, 52>::size_type; // TODO make index correct DType
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

    // Initialize deck tutorial solution
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

    playBlackjack(deck);

    return 0;
}