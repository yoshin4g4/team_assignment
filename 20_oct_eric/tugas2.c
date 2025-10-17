#include <stdio.h>
#include <stdlib.h>

int main() {
    int *grades;
    int numStudents, i;

    printf("Enter number of students: ");
    scanf("%d", &numStudents);

    grades = malloc(numStudents * sizeof(int));  // Memory allocation
    for(i = 0; i < numStudents; i++) {
        printf("Enter grade for student %d: ", i + 1);
        scanf("%d", &grades[i]);
    }

    // Bebaskan memori
    free(grades);

    // Memory leak, no free call
    return 0;
}

