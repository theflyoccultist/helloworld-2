#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// Define the list node structure
typedef struct list { 
    int data;           // Data field to store the value of the node
    struct list *next;  // Pointer to the next node in the list
} list;

// Function to create a new list node with the given data value
list* create_list (int d) 
{
    // Allocate memory for a new node
    list* head = (list*)malloc ( sizeof(list) );

    // Initialize the data field, set the next pointer to NULL (end of the list)
    head -> data = d;
    head -> next = NULL;
    
    // Return the newly created node (head of the list)
    return head;
}

// Function to add a new node with data 'd' to the front of the list 'h'
list* add_to_front(int d, list* h)
{
    // Create a new node with the provided data
    list* head = create_list(d);

    // Set the next pointer of the new node to point to the current head
    head -> next = h;

    // Return the new head (the new node is now at the front of the list)
    return head;
}

// Function to convert an array of integers into a linked list
list* array_to_list(int d[], int size)
{
    // Create the head of the list using the first element of the array
    list* head = create_list(d[0]);
    
    // Loop through the remaining elements of the array
    for (int i = 1; i < size; i++)
    {
        // Add each element to the front of the list
        head = add_to_front(d[i], head);
    }
    // Return the head of the linked list
    return head;
}

void free_list(list *head) {
    list* current = head;
    list* next;

    // Traverse the list and free each node
    while (current != NULL) {
        next = current -> next; // Save the pointer to the next node
        free(current);          // Free the current node
        current = next;         // Move to the next node
    }
}

// Function to generate random numbers between 0 and 100
int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// The swap function also works for elements in a list
void swap(list*a, list*b) {
    int temp = a -> data;
    a -> data = b -> data;
    b -> data = temp;
}

void bubbleSort(list* h) {
    // Skips sorting if the list is empty (or only one element left)
    if (h == NULL || h -> next == NULL) return;

    // Pointers to nodes in the linked list
    list *i, *j; 

    // The largest unsorted element bubbles up to its correct place
    for (i = h; i != NULL; i = i -> next) {

        // Compare each adjacent pair of nodes and swaps them if necessary
        for (j = i -> next; j != NULL; j = j -> next) {
            if (i -> data > j -> data) {
                swap(i, j);
            }
        }
    }
}

// Print the numbers in rows of 5
void print_list (list *h) {
    int count = 0;
    while (h != NULL) {
        printf("%d\t", h -> data);
        count ++;
        if (count % 5 == 0) printf("\n");
        h = h -> next;
    }
}

int main() {
    srand(time(NULL));
    list* head = NULL;

    int data[SIZE];

    // Fill the array with random numbers
    for (int i = 0; i < SIZE; i++) {
        data[i] = getRandomNumber(0, 100);
    }

    head = array_to_list(data, SIZE);

    printf("\nBefore sorting\n");
    print_list(head);
    printf("\n");

    bubbleSort(head);

    printf("After Sorting\n");
    print_list(head);

    free_list(head);

    return 0;
}