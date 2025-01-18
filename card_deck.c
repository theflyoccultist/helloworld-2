#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define suits
enum suit_card { CLUB, DIAMOND, HEART, SPADE };
const char *SUIT[] = { "CLUB", "DIAMOND", "HEART", "SPADE" };

// Define pips
enum pips_card { PIP_A, PIP_2, PIP_3, PIP_4, PIP_5, PIP_6, PIP_7, PIP_8, PIP_9, PIP_J, PIP_Q, PIP_K };
const char *PIPS[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

#define NUM_PIPS (PIP_K + 1) // If i don't do this it skips the King cards

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

int pairs_count = 0;

int has_pair(struct card hand[], int number_draws) {
    int rank_count[NUM_PIPS] = {0}; // Count occurencies of each rank
    for (int i = 0; i < number_draws; i++) {
        rank_count[hand[i].pip]++; // Increment the rank count for each card in hand
    }

    for (int i = 0; i < NUM_PIPS; i++) {
        if (rank_count[i] >=2) {
        pairs_count++;
        return 1; // Pair found
        }
    }

    return 0; // No pairs found
}

int main(void) {
    srand(time(NULL));

    struct card hand[DRAW_SIZE];

    initialize_deck();

    for (int draw = 0; draw < DRAW_COUNT; draw++) {
        shuffle_deck();

        for (int i = 0; i < DRAW_SIZE; i++) {
            hand[i] = deck[i];
        }

        has_pair(hand, DRAW_SIZE);
    }

    float probability = (float)pairs_count / DRAW_COUNT;
    printf("Probability of a pair: %.6f\n", probability);

    return 0;
}