#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

// Structure to store student details
typedef struct {
    char name[MAX_NAME_LENGTH];
    float grade;
} Student;

// Function to compare students based on their grades
int compareStudents(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    if (studentA->grade > studentB->grade)
        return -1;
    else if (studentA->grade < studentB->grade)
        return 1;
    else
        return 0;
}

// Function to print student details
void printStudentDetails(Student* students, int numStudents) {
    printf("Sorted student details:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Name: %s, Grade: %.1f\n", students[i].name, students[i].grade);
    }
}

int main() {
    int numStudents;
    printf("Enter the number of students: ");
    scanf("%d", &numStudents);

    Student* students = (Student*)malloc(numStudents * sizeof(Student));

    // Get student details from the user
    for (int i = 0; i < numStudents; i++) {
        printf("Enter the name of student %d: ", i + 1);
        scanf("%s", students[i].name);
        printf("Enter the grade of student %d: ", i + 1);
        scanf("%f", &students[i].grade);
    }

    // Sort the students based on their grades
    qsort(students, numStudents, sizeof(Student), compareStudents);

    // Print the sorted student details
    printStudentDetails(students, numStudents);

    free(students);
    return 0;
}