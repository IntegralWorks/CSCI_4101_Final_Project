#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

#include "blank_card_bodies.h"
#include "rng.h"

enum ranks
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
};

enum suits
{
    SPADE = 0,
    HEART,
    DIAMOND,
    CLUB
};


enum royals
{
    NOT_ROYAL = 0,
    A = 1,
    J = 11,
    Q = 12,
    K = 13
    
};

struct card_data
{
    suits suit;
    ranks rank;
};

std::string select_suit(suits suit)
{
    switch (suit)
    {
        case SPADE:
            return "\u2660";
        case HEART:
            return "\u2665";
        case DIAMOND:
            return "\u2666";
        case CLUB:
            return "\u2663";
        
        default:
            return "INVALID";
    }
}

std::string select_royal(ranks rank)
{
    royals royal_status = (royals)rank;
    switch (royal_status)
    {
        case J:
            return "\u2658";
        case Q:
            return "\u2655";
        case K:
            return "\u2654";
        case A:
            return "\U0001D538";
        
        default:
            return "NOT ROYAL";
    }
}

std::string *select_card_body(ranks rank)
{
    switch (rank)
    {
    case ACE:
        return &blank_card_body_1;
    case TWO:
        return &blank_card_body_2;
    case THREE:
        return &blank_card_body_3;
    case FOUR:
        return &blank_card_body_4;
    case FIVE:
        return &blank_card_body_5;
    case SIX:
        return &blank_card_body_6;
    case SEVEN:
        return &blank_card_body_7;
    case EIGHT:
        return &blank_card_body_8;
    case NINE:
        return &blank_card_body_9;
    case TEN:
        return &blank_card_body_10;
    case JACK:
    case QUEEN:
    case KING:
        return &blank_card_body_royal;
    
    default:
        return &blank_card_body_1;
    }
}

std::string render(suits suit, ranks rank)
{
    
    std::string new_card     = blank_card;
    std::string suit_symbol  = select_suit(suit);
    std::string royal_symbol = select_royal(rank);
    size_t body_pos, rank_pos;
    
    body_pos = new_card.find("body");
    new_card.replace(body_pos, 4, *select_card_body(rank));

    while ((rank_pos = new_card.find("r")) != std::string::npos)
    {
        if (royal_symbol == "NOT ROYAL")
        {
            if (rank == TEN)
            {
                new_card.replace(rank_pos, 2, std::to_string(rank));
            }

            else
            {
                new_card.replace(rank_pos, 1, std::to_string(rank));
            }
        }

        else
        {
            new_card.replace(rank_pos, 1, royal_symbol);
        }
    }

    while ((rank_pos = new_card.find("s")) != std::string::npos)
    {
        new_card.replace(rank_pos, 1, select_suit(suit));
    }

    return new_card;
}

//emulates python's str.replace(<substr1>, <substr2>)
std::vector<std::string> convert_card_to_lines(std::string card, int lead_card)
{
    std::vector<std::string> lines;

    // Split card by newline
    std::stringstream ss(card);
    std::string line;
    while (std::getline(ss, line)) 
    {
        lines.push_back(line);
    }

    if (lead_card != 1)
    {
        lines[1]  = "  ---------";
        lines[12] = "  ---------";
    }
    return lines;
}

void print_hand(std::vector<std::string> card_lines1, 
    std::vector<std::string> card_lines2,
    std::vector<std::string> card_lines3,
    std::vector<std::string> card_lines4,
    std::vector<std::string> card_lines5)
{
    std::string result = "";
    for (size_t i = 0; i < card_lines1.size(); ++i) {
        result += card_lines1[i] + "  " + card_lines2[i] + "  " + card_lines3[i] + "  " + card_lines4[i] + "  " + card_lines5[i] + "\n";
    }

    std::cout << result;
}


// https://en.cppreference.com/w/cpp/chrono/system_clock
// https://en.cppreference.com/w/cpp/chrono/c/tm
// https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
// https://cplusplus.com/reference/chrono/milliseconds/
int generate_seed() 
{
    auto now            = std::chrono::system_clock::now();
    std::time_t t       = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&t);

    auto sinceEpoch   = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(sinceEpoch) % 1000;

    return milliseconds.count();
}

void draw_cards(int *hand)
{
    int previous_draws[5]    = {-1, -1, -1, -1, -1};
    int successful_draws = 0;
    int draw_attempt;
    bool valid_draw = true;
    while (successful_draws != 5)
    {
        valid_draw = true;
        draw_attempt = rng() % 52;
        for (int i = 0; i < 5; i++)
        {

            if (draw_attempt == previous_draws[i])
            {
                valid_draw = false;
            }
        }

        if (valid_draw == true)
        {
            hand          [successful_draws] = draw_attempt;
            previous_draws[successful_draws] = draw_attempt;
            successful_draws      += 1;

        }
    }
}

int main()
{
    int initial_seed = generate_seed();
    int seed_record[4] = {initial_seed, initial_seed+1, initial_seed+2, initial_seed+3};
    set_seeds(seed_record[0], seed_record[1], seed_record[2], seed_record[3]);

    std::cout << "Seeds: "<< seed_record[0] <<" "<< seed_record[1] <<" "<< seed_record[2] <<" "<< seed_record[3] << "\n";
    int hand[5] = {0,0,0,0,0};
    draw_cards(hand);
    std::cout << "Card Indices: "<< hand[0] <<" "<< hand[1] <<" "<< hand[2] <<" "<< hand[3] << " " << hand[4] <<" " <<"\n";

    std::string deck[52];
    card_data   deck_data[52];
    
    int card_count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 14; j++)
        {
            deck     [card_count] = render((suits)i  , (ranks)j);
            deck_data[card_count] = {.suit = (suits)i, .rank = (ranks)j};
            card_count += 1;
        }
    }

    for (int i = 0; i < 52; i++)
    {
        if (deck[i]=="")
        {
            std::cout<<"WARNING: EMPTY STRING FOUND AT {" << i << "}"<<" ";
        }
    }
    

    std::vector<std::string> card_lines1 = convert_card_to_lines(deck[hand[0]],1);
    std::vector<std::string> card_lines2 = convert_card_to_lines(deck[hand[1]],0);
    std::vector<std::string> card_lines3 = convert_card_to_lines(deck[hand[2]],0);
    std::vector<std::string> card_lines4 = convert_card_to_lines(deck[hand[3]],0);
    std::vector<std::string> card_lines5 = convert_card_to_lines(deck[hand[4]],0);


    std::cout<<"\n";
    print_hand(card_lines1, card_lines2, card_lines3, card_lines4, card_lines5);
    std::cout<<"\n";

    return 0;
}