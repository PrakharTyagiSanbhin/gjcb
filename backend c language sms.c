#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int rollNo;
    char name[100];
    char phone[20];
    char course[50];
    char department[50];
    int semester;
    float marks;
    char grade;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
char calculateGrade(float marks);

int main()
{
    int choice;

    while (1)
    {
        printf("\n=====================================\n");
        printf("     STUDENT MANAGEMENT SYSTEM\n");
        printf("=====================================\n");

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            printf("\nThank You!\n");
            exit(0);

        default:
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

char calculateGrade(float marks)
{
    if (marks >= 90)
        return 'A';
    else if (marks >= 75)
        return 'B';
    else if (marks >= 60)
        return 'C';
    else
        return 'D';
}

void addStudent()
{
    FILE *fp;
    struct Student s;
    struct Student temp;
    int found = 0;

    fp = fopen("students.dat", "ab+");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Roll No: ");
    scanf("%d", &s.rollNo);

    rewind(fp);

    while (fread(&temp, sizeof(temp), 1, fp))
    {
        if (temp.rollNo == s.rollNo)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\nRoll Number Already Exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Phone No: ");
    scanf("%s", s.phone);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Department / Branch: ");
    scanf(" %[^\n]", s.department);

    printf("Enter Semester: ");
    scanf("%d", &s.semester);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    s.grade = calculateGrade(s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents()
{
    FILE *fp;
    struct Student s;
    int count = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n===============================================================================================================\n");
    printf("%-8s %-20s %-15s %-15s %-20s %-10s %-10s %-10s\n",
           "RollNo",
           "Name",
           "Phone",
           "Course",
           "Department",
           "Semester",
           "Marks",
           "Grade");
    printf("===============================================================================================================\n");

    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("%-8d %-20s %-15s %-15s %-20s %-10d %-10.2f %-10c\n",
               s.rollNo,
               s.name,
               s.phone,
               s.course,
               s.department,
               s.semester,
               s.marks,
               s.grade);

        count++;
    }

    printf("\nTotal Students: %d\n", count);

    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;

    int roll;
    int found = 0;

    printf("\nEnter Roll No to Search: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;

            printf("\nStudent Found\n");
            printf("-------------------------\n");

            printf("Roll No              : %d\n", s.rollNo);
            printf("Student Name         : %s\n", s.name);
            printf("Phone No             : %s\n", s.phone);
            printf("Course               : %s\n", s.course);
            printf("Department / Branch  : %s\n", s.department);
            printf("Semester             : %d\n", s.semester);
            printf("Marks                : %.2f\n", s.marks);
            printf("Grade                : %c\n", s.grade);

            break;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("\nStudent Not Found!\n");
    }
}

void updateStudent()
{
    FILE *fp;
    struct Student s;

    int roll;
    int found = 0;

    printf("\nEnter Roll No to Update: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;

            printf("\nEnter New Student Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Phone No: ");
            scanf("%s", s.phone);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Department / Branch: ");
            scanf(" %[^\n]", s.department);

            printf("Enter New Semester: ");
            scanf("%d", &s.semester);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            s.grade = calculateGrade(s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);

            fwrite(&s, sizeof(s), 1, fp);

            printf("\nStudent Updated Successfully!\n");

            break;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("\nStudent Not Found!\n");
    }
}

void deleteStudent()
{
    FILE *fp;
    FILE *temp;

    struct Student s;

    int roll;
    int found = 0;

    printf("\nEnter Roll No to Delete: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
    {
        printf("\nStudent Deleted Successfully!\n");
    }
    else
    {
        printf("\nStudent Not Found!\n");
    }
}
