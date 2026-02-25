#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "debug.h"
#include <stdbool.h>

#define SCANF(fmt, ...)        \
    do {                       \
        scanf(fmt, __VA_ARGS__); \
        clearInputBuffer();    \
    } while (0)

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char feature[] = "\n===== STUDENT MANAGEMENT =====\
    \n1. Add student\
    \n2. Display students\
    \n3. Search student by ID\
    \n4. Delete student by ID\
    \n5. Exit\
    \n6. Help";

    initData();
    printf(feature);
    bool exitProgram = false;
    while (!exitProgram)
    {
        printf("\nChoose: ");
        int option;
        SCANF("%d", &option);
        switch (option)
        {
            case 1: {
                char name[50];
                float gpa;
                printf("\nEnter name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("\nEnter GPA: ");
                SCANF("%f", &gpa);
                int id = addStudent(name, gpa);
                printf("\nAdd record ID: %d Name: %s GPA: %.2f done!", id, name, gpa);
                break;
            }
            case 2: {
                displayStudent();
                break;
            }
            case 3: {
                printf("\nEnter ID: ");
                int id;
                SCANF("%d", &id);
                Student info;
                if (searchRecord(id, &info) == 0) {
                    printf("\nID: %d Name: %s GPA: %.02f", info.id, info.name, info.gpa);
                } else {
                    printf("\nNo record found!");
                }
                break;
            }
            case 4: {
                printf("\nEnter ID to delete: ");
                int id;
                SCANF("%d", &id);
                if (deleteRecord(id) == 0) {
                    printf("\nDelete record ID = %d done!", id);
                } else {
                    printf("\nNo record found!");
                }
                break;
            }
            case 5: {
                exitProgram = true;
                break;
            }
            case 6: {
                printf(feature);
                break;
            }
            default: {
                printf(feature);
                break;
            }
        }
    }


    return 0;
}