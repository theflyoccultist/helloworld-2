#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
        }
    }
}

int main() {
    srand(time(NULL));

    int data[SIZE];

    // Fill the array with random numbers
    for (int i = 0; i < SIZE; i++) {
        data[i] = getRandomNumber(0, 100);
    }

    int n = sizeof(data) / sizeof(data[0]);
    bubbleSort(data, n);

    // Print the numbers in rows of 5
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", data[i]);
        if ((i + 1) % 5 == 0) printf("\n");
    }

    return 0;
}

// typedef struct list { 
//     int data;
//     struct list *next;
// } list;

// int is_empty ( const list *l ) { return ( l == NULL ); }
// list* create_list (int d) 
// {
//     list* head = malloc ( sizeof(list) );
//     head -> data = d;
//     head -> next = NULL;
//     return head;
// }

// list* add_to_front(int d, list* h)
// {
//     list* head = create_list(d);
//     head -> next = h;
//     return head;
// }

// list* array_to_list(int d[], int size)
// {
//     list* head = create_list(d[0]);
//     int i;
//     for (i = 1; i < size; i++)
//     {
//         head = add_to_front(d[i], head);
//     }
//     return head;
// }



// void print_list (list *h, char *title)
// {
//     printf ("%s\n", title);
//     while (h != NULL) {
//         printf ("%d:", h -> data);
//         h = h -> next;
//     }
// }

