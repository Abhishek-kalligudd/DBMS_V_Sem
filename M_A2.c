//Write a C program to demonstrate indexing and associated operations.
#include <stdio.h>

#define MAX_SIZE 10

// Function to display the array elements
void displayArray(int arr[], int size) {
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to insert an element into the array
int insertElement(int arr[], int size, int element, int index) {
    if (size >= MAX_SIZE) {
        printf("Array is full. Cannot insert element.\n");
        return size;
    }
    if (index < 0 || index > size) {
        printf("Invalid index. Please enter an index between 0 and %d.\n", size);
        return size;
    }
    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = element;
    return size + 1;
}

// Function to delete an element from the array
int deleteElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        printf("Invalid index. Please enter an index between 0 and %d.\n", size - 1);
        return size;
    }
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    return size - 1;
}

// Function to find the index of a given element
void findElementIndex(int arr[], int size, int element) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            printf("Element %d found at index %d.\n", element, i);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Element %d not found in the array.\n", element);
    }
}

int main() {
    int arr[MAX_SIZE];
    int size = 0;
    int choice, element, index;

    do {
        printf("\nMenu:\n");
        printf("1. Insert Element\n");
        printf("2. Delete Element\n");
        printf("3. Display Array\n");
        printf("4. Find Element Index\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                printf("Enter index (0 to %d): ", size);
                scanf("%d", &index);
                size = insertElement(arr, size, element, index);
                break;
            case 2:
                printf("Enter index of element to delete (0 to %d): ", size - 1);
                scanf("%d", &index);
                size = deleteElement(arr, size, index);
                break;
            case 3:
                displayArray(arr, size);
                break;
            case 4:
                printf("Enter element to find: ");
                scanf("%d", &element);
                findElementIndex(arr, size, element);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
