// Given a file with integer numbers, this program will use the first number to determine the array length.
// Then, it will regroup every couple next numbers as a rational number and perform operations on them.

#include <stdio.h>
#include <stdlib.h>

// Define the rational number structure
typedef struct rational {
    double num;     // Numerator
    double den;     // Denominator
    struct rational *next;
} rational;

// Function to create a new rational number
rational* create_rational (int num, int den) {
    if (den == 0) {
        fprintf(stderr, "0 is not an anthorized Denominator\n");
        exit(1);
    }

    rational* new_rational = (struct rational*)malloc ( sizeof(rational) );
    if (new_rational == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    new_rational -> num = num;
    new_rational -> den = den;
    new_rational -> next = NULL;
    return new_rational;
}

// Function to loop through the rest of the numbers and pair them as rational numbers
rational* pair_rational_numbers(FILE* file) {
    int num, den;
    rational* head = NULL;
    rational* tail = NULL;

    // Assuming the first number is already handled
    while (fscanf(file, "%d %d", &num, &den) == 2) {
        rational* new_rational = create_rational(num, den);
        if (head == NULL) {
            head = new_rational;
            tail = new_rational;
        } else {
            tail -> next = new_rational;    // Link the new node to the end
            tail = new_rational;            // Move the tail pointer to the new node            
        }
    }
    return head;
}

// Print the list of rational numbers to the console
void print_rational_list(rational* head) {
    rational* current = head;
    while (current != NULL) {
        printf("%f/%f\n", current -> num, current -> den);
        current = current -> next;
    }
}

// Good to free the memory
void free_list(rational* head) {
    rational* current = head;
    while (current != NULL) {
        rational* next = current -> next;
        free(current);
        current = next;
    }
}

int main (int argc, char* argv[]) {
    FILE *ifp, *ofp;

    if (argc != 3) {
        fprintf(stderr, "Usage: <filename> <filename>\n");
        exit(1);
    }

    ifp = fopen(argv[1], "r");
    if (ifp == NULL) {
        fprintf(stderr, "Can't open input file %s\n", argv[1]);
        exit(1);
    }

    ofp = fopen(argv[2], "w");
    if (ofp == NULL) {
        fprintf(stderr, "Can't open output file %s\n", argv[2]);
        exit(1);
    }

    printf("Reading from %s and writing to %s\n", argv[1], argv[2]);

    // Skip the first number
    int first_num;
    fscanf(ifp, "%d", &first_num);
    printf("First number (array size): %d\n", first_num);

    rational* head = NULL;
    head = pair_rational_numbers(ifp);

    printf("Printing the list of rational numbers\n");
    print_rational_list(head);

    free_list(head);
    fclose(ifp);
    fclose(ofp);

    return 0;
}
