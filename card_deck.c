// This project shuffles a deck of cards and draws 7 cards 1 million times.
// It then calculates the probability of getting a pair, two pairs, three of a kind, full house, and four of a kind.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define suits
enum suit_card { CLUB, DIAMOND, HEART, SPADE };
const char *SUIT[] = { "CLUB", "DIAMOND", "HEART", "SPADE" };

// Define pips
enum pips_card { PIP_A, PIP_2, PIP_3, PIP_4, PIP_5, PIP_6, PIP_7, PIP_8, PIP_9, PIP_10, PIP_J, PIP_Q, PIP_K };
const char *PIPS[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

#define NUM_PIPS PIP_K

#define DECK_SIZE 52
#define DRAW_SIZE 7
#define DRAW_COUNT 1000000

// Card structure with pip and suit
struct card {
    enum suit_card suit;
    enum pips_card pip;
} deck [52];

// Initialize the deck of cards
void initialize_deck() {
    int index = 0;

    // This loop outputs the entire card deck in order
    for (int suit = CLUB; suit <= SPADE; suit++) {
        for (int pip = PIP_A; pip <= NUM_PIPS; pip++) {
            deck[index].suit = suit;
            deck[index].pip = pip;
            index++;
        }
    }
}

// Shuffle the deck of cards
void shuffle_deck() {
    int i;
    for (i = DECK_SIZE - 1; i > 1; i--) {
        int j = rand() % DECK_SIZE; // Pick a random index

        // Swap deck[i] and deck[j]
        struct card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// I gotta access those at the main() function too, that's why I put them here
int four, full_house, three, two_pairs, two, no_pair;

// This function checks if the hands contains a pair, a three or four and adds it to the counter.
void analyze_hand(struct card hand[], int number_draws) {
    
    int pairs = 0, three_of_a_kind = 0, four_of_a_kind = 0;
    int rank_count[NUM_PIPS] = {0}; // Count occurencies of each rank

    // Increment the rank count for each card in hand
    for (int i = 0; i < number_draws; i++) {
        rank_count[hand[i].pip]++;
    }

    for (int i = 0; i < NUM_PIPS; i++) {
        if (rank_count[i] == 2) {
            pairs++;
        } else if (rank_count[i] == 3) {
            three_of_a_kind++;
        } else if (rank_count[i] == 4) {
            four_of_a_kind++;
        }
    }

    // This logic groups each draw, from the luckiest to the unluckiest
    if (four_of_a_kind > 0) {
        four++;
    } else if (three_of_a_kind && pairs > 0) {
        full_house++;
    } else if (three_of_a_kind) {
        three++;
    } else if (pairs > 1) {
        two_pairs++;
    } else if (pairs == 1) {
        two++;
    } else {
        no_pair++;
    }
}

int main(void) {
    srand(time(NULL));

    struct card hand[DRAW_SIZE];

    initialize_deck();

    // Draw cards one million times
    for (int draw = 0; draw < DRAW_COUNT; draw++) {
        shuffle_deck();

        for (int i = 0; i < DRAW_SIZE; i++) {
            hand[i] = deck[i];
        }

        analyze_hand(hand, DRAW_SIZE);
    }

    // Printing all the probabilities here
    float four_probability = (float)four / DRAW_COUNT;
    printf("Probability of four of a kind : %.6f\n", four_probability);

    float full_house_probability = (float)full_house / DRAW_COUNT;
    printf("Probability of full house : %.6f\n", full_house_probability);

    float three_probability = (float)three / DRAW_COUNT;
    printf("Probability of three of a kind : %.6f\n", three_probability);

    float two_pair_probability = (float)two_pairs / DRAW_COUNT;
    printf("Probability of two pairs : %.6f\n", two_pair_probability);

    float pair_probability = (float)two / DRAW_COUNT;
    printf("Probability of a pair : %.6f\n", pair_probability);

    float no_pair_probability = (float)no_pair / DRAW_COUNT;
    printf("No pair : %.6f\n", no_pair_probability);

    // Added this just to check that it's equal to 1
    float total = four_probability + full_house_probability + three_probability + two_pair_probability + pair_probability + no_pair_probability;
    printf("Total : %.6f\n", total);

    return 0;
}