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

// Function to get the first number of the file
rational* get_first_number(FILE* file) {
    int num;
    fscanf(file, "%d", &num);
    return create_rational(num, 1);
}

// Function to loop through the rest of the numbers and pair them as rational numbers
rational* pair_rational_numbers(FILE* file, rational* head) {
    int num, den;
    rational* tail = head;

    // Assuming the first number is already handled
    while (fscanf(file, "%d %d", &num, &den) == 2) {
        rational* new_rational = create_rational(num, den);
        tail -> next = new_rational;    // Link the new node to the end
        tail = new_rational;            // Move the tail pointer to the new node
    }
    return head;
}

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

    rational* size = get_first_number(ifp);
    printf("First number (array size): %f\n", size -> num);

    rational* head = pair_rational_numbers(ifp, size);

    printf("Printing the list of rational numbers\n");
    print_rational_list(head);

    free_list(head);
    fclose(ifp);
    fclose(ofp);

    return 0;
}
