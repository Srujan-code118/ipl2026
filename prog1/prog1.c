#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int roll;
    char name[30];
    float marks;
};

/* Function to display a record */
void display(struct Student s)
{
    printf("\nRoll  : %d", s.roll);
    printf("\nName  : %s", s.name);
    printf("\nMarks : %.2f\n", s.marks);
}

/* Function to get mth record using fseek */
void getRecord(char filename[], int m)
{
    FILE *fp;
    struct Student s;

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }

    /* Move file pointer to mth record */
    fseek(fp, (m - 1) * sizeof(struct Student), SEEK_SET);

    if (fread(&s, sizeof(struct Student), 1, fp) == 1)
    {
        printf("\n%dth Record:\n", m);
        display(s);
    }
    else
    {
        printf("Record not found\n");
    }

    fclose(fp);
}

/* Function to delete a record */
void deleteRecord(char filename[], int rollNo)
{
    FILE *fp, *temp;
    struct Student s;
    int found = 0;

    fp = fopen(filename, "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        /* Copy all records except matching roll number */
        if (s.roll != rollNo)
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove(filename);           // delete old file
        rename("temp.dat", filename); // rename temp file
        printf("\nRecord deleted successfully\n");
    }
    else
    {
        remove("temp.dat");
        printf("\nRecord not found\n");
    }
}

int main()
{
    FILE *fp;
    struct Student s;
    int n, i, m, rollDelete;

    fp = fopen("student.dat", "wb");

    if (fp == NULL)
    {
        printf("Cannot create file\n");
        return 1;
    }

    printf("Enter number of records: ");
    scanf("%d", &n);

    /* Store records */
    for (i = 0; i < n; i++)
    {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Roll: ");
        scanf("%d", &s.roll);

        printf("Name: ");
        scanf("%s", s.name);

        printf("Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(struct Student), 1, fp);
    }

    fclose(fp);

    /* Access mth record */
    printf("\nEnter record number to fetch: ");
    scanf("%d", &m);

    getRecord("student.dat", m);

    /* Delete record */
    printf("\nEnter roll number to delete: ");
    scanf("%d", &rollDelete);

    deleteRecord("student.dat", rollDelete);

    return 0;
}