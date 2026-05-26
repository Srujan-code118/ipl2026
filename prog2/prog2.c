#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "Record.txt"
#define MAX 100

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

// Function 
void writeRecordsToFile(const char *filename, Student arr[], int n);
void createSeekPositions(const char *filename, long positions[], int n);
void displayRecordAtPosition(const char *filename, long pos);

int main() {
    Student arr[MAX];
    int n,m;
    long positions[MAX];

    printf("Enter number of students: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        printf("\nEnter student ID: ");
        scanf("%d", &arr[i].id);

        printf("Enter name: ");
        scanf("%s", arr[i].name);

        printf("Enter marks: ");
        scanf("%f", &arr[i].marks);  
        
         
    }

 
    writeRecordsToFile(FILENAME, arr, n);

  
    createSeekPositions(FILENAME, positions, n);
    printf("\nDisplaying all record using seek positions:\n");
    for (int i=0;i<n;i++){
    printf("____Record_____\n ");
    displayRecordAtPosition(FILENAME, positions[i]);
    }

    return 0;
    }


void writeRecordsToFile(const char *filename, Student arr[], int n){
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Error opening file for writing!\n");
        return;
    }

    for(int i = 0; i < n; i++){
    
        fprintf(fp, "%d %s %.2f\n", arr[i].id, arr[i].name, arr[i].marks);
    }

    fclose(fp);
}


void createSeekPositions(const char *filename, long positions[], int n) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error opening file for reading!\n");
        return;
    }

    char buffer[256];
    int count = 0;

    while (count < n) {
        long pos = ftell(fp);  

        if (fgets(buffer, sizeof(buffer), fp) == NULL)
            break;

        positions[count] = pos;
        count++;
    }

    fclose(fp);
}


void displayRecordAtPosition(const char *filename, long pos){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }

    // Jump to position
    fseek(fp, pos, SEEK_SET);

    int id;
    char name[50];
    float marks;

    fscanf(fp, "%d %s %f", &id, name, &marks);

    printf("\nRecord at file position %ld:\n", pos);
    printf("ID: %d\n", id);
    printf("Name: %s\n", name);
    printf("Marks: %.2f\n", marks);

    fclose(fp);
}