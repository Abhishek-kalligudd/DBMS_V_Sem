#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_RECORDS 100
#define RECORD_FILE "records.dat"
#define INDEX_FILE "index.dat"

// Record structure
typedef struct {
    int id;              // Unique ID for the record
    char name[30];       // Name of the record
} Record;

// Index structure to map ID to file position
typedef struct {
    int id;              // ID of the record
    int position;        // File position of the record (in bytes)
} IndexEntry;

void addRecord();
void createIndex();
void searchRecord();
void displayAllRecords();

int main() {
    int choice;

    while (1) {
        printf("\nFile Indexing System\n");
        printf("1. Add Record\n");
        printf("2. Create Index\n");
        printf("3. Search Record by ID\n");
        printf("4. Display All Records\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                createIndex();
                break;
            case 3:
                searchRecord();
                break;
            case 4:
                displayAllRecords();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void addRecord() {
    int file = open(RECORD_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (file == -1) {
        printf("Error opening file\n");
        return;
    }

    Record record;
    printf("Enter record ID: ");
    scanf("%d", &record.id);
    printf("Enter record name: ");
    scanf("%s", record.name);

    write(file, &record, sizeof(Record));
    close(file);

    printf("Record added successfully.\n");
}

void createIndex() {
    int file = open(RECORD_FILE, O_RDONLY);
    int indexFile = open(INDEX_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1 || indexFile == -1) {
        printf("Error opening file\n");
        return;
    }

    IndexEntry indexEntries[MAX_RECORDS];
    Record record;
    int recordCount = 0;

    while (read(file, &record, sizeof(Record)) == sizeof(Record) && recordCount < MAX_RECORDS) {
        indexEntries[recordCount].id = record.id;
        indexEntries[recordCount].position = recordCount * sizeof(Record);
        recordCount++;
    }

    write(indexFile, indexEntries, sizeof(IndexEntry) * recordCount);

    close(file);
    close(indexFile);
    printf("Index created successfully.\n");
}

void searchRecord() {
    int id;
    printf("Enter the ID of the record to search: ");
    scanf("%d", &id);

    int indexFile = open(INDEX_FILE, O_RDONLY);
    int file = open(RECORD_FILE, O_RDONLY);
    if (indexFile == -1 || file == -1) {
        printf("Error opening file\n");
        return;
    }

    IndexEntry indexEntries[MAX_RECORDS];
    int indexCount = read(indexFile, indexEntries, sizeof(IndexEntry) * MAX_RECORDS) / sizeof(IndexEntry);

    int found = 0;
    for (int i = 0; i < indexCount; i++) {
        if (indexEntries[i].id == id) {
            lseek(file, indexEntries[i].position, SEEK_SET);
            Record record;
            read(file, &record, sizeof(Record));
            printf("Record found:\n");
            printf("ID: %d, Name: %s\n", record.id, record.name);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }

    close(indexFile);
    close(file);
}

void displayAllRecords() {
    int file = open(RECORD_FILE, O_RDONLY);
    if (file == -1) {
        printf("Error opening file\n");
        return;
    }

    Record record;
    printf("\nAll Records:\n");
    printf("ID\tName\n");
    printf("-----------------\n");

    while (read(file, &record, sizeof(Record)) == sizeof(Record)) {
        printf("%d\t%s\n", record.id, record.name);
    }

    close(file);
}
