typedef struct Student {
    char name[50];
    int id;
    float gpa;
} Student;

int addStudent(char *name, float gpa);
int displayStudent();
int searchRecord(int id, Student *info);
int deleteRecord(int id);
int initData();
