#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 200

// Define the list node structure
typedef struct list { 
    int data;           // Data stored in the node
    struct list *next;  // Pointer to the next node
    struct list *prev;  // Pointer to the previous node
} list;

// Function to create a new doubly linked list
list* create_list (int d) 
{
    struct list* newList = (struct list*)malloc( sizeof(struct list) );
        if (newList == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
        }

    newList -> data = d;
    newList -> next = NULL;
    newList -> prev = NULL;
    
    return newList;
}

// Function to add a new node with data 'd' to the front of the list 'h'
list* add_to_front(int d, list* h)
{
    list* head = create_list(d);

    head -> next = h;
    if (h != NULL) {
        h -> prev = head;
    }

    return head;
}

// Function to convert an array of integers into a linked list
list* array_to_list(int d[], int size)
{
    if (d == NULL || size <= 0) {
    fprintf(stderr, "Invalid array or size\n");
    return NULL;
    }
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

// Function to generate random numbers between 0 and 100
int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

struct list* split_list(struct list* head) {
    struct list* slow = head;
    struct list* fast = head;

    while (fast != NULL && fast -> next != NULL) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }

    if (slow != NULL && slow -> prev != NULL) {
        slow -> prev -> next = NULL;    // Break forward link
        slow -> prev = NULL;            // Break backward link
    }

    return slow; // Return the head of the second half
}

struct list* merge(struct list* head_a, struct list* head_b) {
    if (head_a == NULL) return head_b;
    if (head_b == NULL) return head_a;
    
    struct list* result = NULL;

    // Compare data and recursively merge
    if (head_a -> data < head_b -> data) {
        result = head_a;
        result -> next = merge(head_a -> next, head_b);
        if (result -> next != NULL) {
            result -> next -> prev = result; // Update backward link            
        }
    } else {
        result = head_b;
        result -> next = merge(head_a, head_b -> next);
        if (result -> next != NULL) {
            result -> next -> prev = result;
        }    
    }
    
    return result;
}

struct list* merge_sort(struct list* head) {
    if (head == NULL || head -> next == NULL) {
        return head; // if list wih 0 or 1 element is already sorted
    }

    struct list* second_half = split_list(head); // Split the list into two halves

    // Recursively sort half
    struct list* left_sorted = merge_sort(head);
    struct list* right_sorted = merge_sort(second_half);

    return merge(left_sorted, right_sorted);
}

// Print the numbers in rows of 5
void print_list (struct list *head) {
    if (head == NULL || head -> next == NULL) return;

    int count = 0;
    while (head != NULL) {
        printf("%d\t", head -> data);
        count ++;
        if (count % 5 == 0) printf("\n");
        head = head -> next;
    }
}

void free_list(struct list *head) {
    list* current = head;
    list* next;

    // Traverse the list and free each node
    while (current != NULL) {
        next = current -> next; // Save the pointer to the next node
        free(current);          // Free the current node
        current = next;         // Move to the next node
    }
}

int main() {
    srand(time(NULL));

    int data[SIZE];
    for (int i = 0; i < SIZE; i++) {
        data[i] = getRandomNumber(0, 49);
    }

    // Convert the array to a doubly linked list
    struct list* head = array_to_list(data, SIZE);

    printf("Before Sorting:\n");
    print_list(head);
    printf("\n");

    // Perform merge sort on the list
    head = merge_sort(head);

    printf("After Sorting:\n");
    print_list(head);

    free_list(head); // Free allocated memory

    return 0;
}
