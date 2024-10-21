//Write a C program to study all the file operations related SYSTEM CALLS supported by UNIX OS and C libraries for file operations
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void writeToFile(int filedesp) {
    char userInput[100];
    printf("Enter text to write to the file: ");
    fgets(userInput, sizeof(userInput), stdin);

    ssize_t bytesWritten = write(filedesp, userInput, strlen(userInput));
    if (bytesWritten == -1) {
        perror("Error writing to file");
    } else {
        printf("Successfully written to the file.\n");
    }
}

void readFromFile(int filedesp) {
    char buffer[100];
    ssize_t bytesRead;

    // Move the file pointer to the beginning
    if (lseek(filedesp, 0, SEEK_SET) == -1) {
        perror("Error seeking in file");
        return;
    }

    // Read from the file
    bytesRead = read(filedesp, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Error reading from file");
        return;
    }

    // Null-terminate the buffer and print the content
    buffer[bytesRead] = '\0';
    printf("Read from file: %s\n", buffer);
}

int main() {
    int filedesp;
    int choice;

    // Opening a file for reading and writing, create if it doesn't exist
    filedesp = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (filedesp == -1) {
        perror("Error opening file");
        return 1;
    }

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Write to file\n");
        printf("2. Read from file\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character left by scanf

        switch (choice) {
            case 1:
                writeToFile(filedesp);
                break;
            case 2:
                readFromFile(filedesp);
                break;
            case 3:
                close(filedesp);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
