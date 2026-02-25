#include "student.h"
#include "debug.h"
#include "stdio.h"
#include "string.h"

#define DATA_PATH "data/data"
#define DATA_PATH_TEMP "data/data_temp"

int initData() {
    FILE *fptr;
    fptr = fopen(DATA_PATH, "r");
    if (fptr) {
        fclose(fptr);
        return 0;
    }
    int idPool = 0;
    fptr = fopen(DATA_PATH, "wb+");
    CHECK(fptr != NULL);
    fwrite(&idPool, sizeof(idPool), 1, fptr);
    fclose(fptr);
    return 0;
}

int getID(int *id) {
    FILE *fptr;
    fptr = fopen(DATA_PATH, "rb+");
    CHECK(fptr != NULL);

    fread(id, sizeof(*id), 1, fptr);
    fseek(fptr, 0, SEEK_SET);
    *id = *id + 1;
    fwrite(id, sizeof(*id), 1, fptr);

    fclose(fptr);
    return 0;
}

int addStudent(char *name, float gpa) {
    FILE *fptr;
    Student newStudent = {0};
    strcpy(newStudent.name, name);
    newStudent.gpa = gpa;
    getID(&(newStudent.id));

    fptr = fopen(DATA_PATH, "ab+");
    CHECK(fptr);
    fwrite(&newStudent, sizeof(newStudent), 1, fptr);
    fclose(fptr);
    return newStudent.id;
}

int displayStudent() {
    FILE *fptr;
    Student student = {0};
    fptr = fopen(DATA_PATH, "rb");
    CHECK(fptr);
    fseek(fptr, sizeof(int), SEEK_SET);
    printf("\nStudent list:");
    printf("\n||%-10s||%-30s||%-10s||", "ID", "Name", "GPA");
    while (fread(&student, sizeof(student), 1, fptr) != 0)
    {
        printf("\n||%-10d||%-30s||%-10.02f||", student.id, student.name, student.gpa);
    }
    fclose(fptr);
    return 0;
}

int searchRecord(int id, Student *info) {
    FILE *fptr;
    Student student = {0};
    fptr = fopen(DATA_PATH, "rb");
    CHECK(fptr);
    fseek(fptr, sizeof(int), SEEK_SET);
    while (fread(&student, sizeof(student), 1, fptr) != 0)
    {
        if (student.id == id) {
            memcpy(info, &student, sizeof(student));
            fclose(fptr);
            return 0;
        }
    }
    fclose(fptr);
    return 1;
}

int deleteRecord(int id) {
    FILE *fOriginPtr, *fTempPtr;
    Student student = {0};
    fOriginPtr = fopen(DATA_PATH, "rb");
    CHECK(fOriginPtr);
    fTempPtr = fopen(DATA_PATH_TEMP, "wb+");
    CHECK(fTempPtr);
    int idPool;
    fread(&idPool, sizeof(int), 1, fOriginPtr);
    fwrite(&idPool, sizeof(int), 1, fTempPtr);
    
    int found = 0;
    while (fread(&student, sizeof(student), 1, fOriginPtr) != 0)
    {
        if (student.id != id) {
            fwrite(&student, sizeof(student), 1, fTempPtr);
        } else {
            found = 1;
        }
    }
    fclose(fOriginPtr);
    fclose(fTempPtr);
    remove(DATA_PATH);
    rename(DATA_PATH_TEMP, DATA_PATH);

    return (found != 1);
}
