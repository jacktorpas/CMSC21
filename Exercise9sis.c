#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define M "Male"
#define F "Female"

struct Student{
    char studentNo[15]; //since it's hyphenated
    char lastName[15], firstName[15];
    char course[15], sex[10];
    int yrLevel, age;
    int finalGrade; //passing is 60, from 0-100
    struct Student *next;
}; typedef struct Student Student;

struct StudentRecord{
    Student *head;
    Student *tail;
    int size;
}; typedef struct StudentRecord StudentRecord;

void menu();
void recordInit(StudentRecord*);

Student* studentInit();
int enrolStudent(StudentRecord*, Student*);
void insertStudent(StudentRecord*, Student*, int);
void dropStudent(StudentRecord*, int);
void editStudent(StudentRecord*, int, int);
void displayAllStudents(StudentRecord);
void filterStudents(StudentRecord*, int, char*);
void sortRecord(StudentRecord*, int);

int getStudeIndex(StudentRecord, char*);
Student* getStudent(StudentRecord*, int);

int studNoIsValid(char*);
int stringsAreSimilar(char*, char*);
int strCmpLower(char*, char*);
void printStudent(Student*, int);


void menu(){
    printf("--Student Information System--\n");
    printf("1. Enrol a student\n");
    printf("2. Drop a student\n");
    printf("3. Edit a student\n");
    printf("4. Display all students\n");
    printf("5. Filter students by last name\n");
    printf("6. Filter students by student number\n");
    printf("7. Filter students by year level\n");
    printf("8. Filter students by course\n");
    printf("9. Filter students by sex\n");
    printf("10. Filter students by passing\n");
    printf("11. Filter students by failing\n");
    printf("12. Sort students by last name\n");
    printf("13. Sort students by student number\n");
    printf("14. Exit\n\n");
}

//initializing the record
void recordInit(StudentRecord *record){
    record->head = 0;
    record->tail = 0;
    record->size = 0;
}

Student* studentInit(){
    Student *s = (Student*) malloc(sizeof(Student));
    char input[15];
    printf("Enrol\n");

    do{
        printf("Student number: ");
        scanf("%s", input);
    }while(!studNoIsValid(input));
    strcpy(s->studentNo, input);

    do{
        printf("Last name: ");
        scanf("%s", input);
    }while(strlen(input) > 15);
    strcpy(s->lastName, input);

    do{
        printf("First name: ");
        scanf("%s", input);
    }while(strlen(input) > 15);
    strcpy(s->firstName, input);

    do{
        printf("Course: ");
        scanf("%s", input);
    }while(strlen(input) > 15);
    strcpy(s->course, input);

    do{
        printf("Year level: ");
        scanf("%i", &s->yrLevel);
    }while(s->yrLevel < 1 || s->yrLevel > 5);

    do{
        printf("Age: ");
        scanf("%i", &s->age);
    }while(s->age < 0);

    do{
        printf("Sex: ");
        scanf("%s", input);
    }while(strCmpLower(M, input) != 0 && strCmpLower(F, input) != 0);
    strcpy(s->sex, input);

    do{
        printf("Final grade: ");
        scanf("%i", &s->finalGrade);
    }while(s->finalGrade < 0 || s->finalGrade > 100);

    s->next = 0;
    return s;
}

int enrolStudent(StudentRecord *record, Student *s){
    insertStudent(record, s, record->size);
    record->size++;
    return record->size;
}

void insertStudent(StudentRecord *record, Student *s, int index){
    if(index >= 0 && index <= record->size){
        if(index == 0){
            s->next = record->head;
            record->head = s;
        }

        if(index == record->size){
            if(record->tail != 0){
                record->tail->next = s;
            }
            record->tail = s;
        }

        if(index > 0 && index < record->size){
            Student *prev = getStudent(record, index - 1);
            s->next = prev->next;
            prev->next = s;
        }
    }
}

void dropStudent(StudentRecord *record, int index){
    Student *toDrop = record->head;
    if(index >= 0 && index < record->size){
        if(index == 0){
            toDrop = record->head;
            record->head = toDrop->next;
        }else{
            Student *prev = getStudent(record, index - 1);
            toDrop = prev->next;
            prev->next = toDrop->next;
            if(index == record->size - 1){
                record->tail = prev;
            }
        }

        free(toDrop);
        record->size--;
    }
}

void editStudent(StudentRecord *record, int index, int editField){
    Student *s = getStudent(record, index);
    char input[15];
    int tempInt;

    switch(editField){
        case 1:
            printf("Edit student number (%s): ", s->studentNo);
            scanf("%s", input);
            if(studNoIsValid(input)){
                strcpy(s->studentNo, input);
            }else{
                printf("Invalid student number!\n");
            }
            break;
        case 2:
            printf("Edit last name (%s): ", s->lastName);
            scanf("%s", input);
            if(strlen(input) <= 15){
                strcpy(s->lastName, input);
            }else{
                printf("Invalid last name!\n");
            }
            break;
        case 3:
            printf("Edit first name (%s): ", s->firstName);
            scanf("%s", input);
            if(strlen(input) <= 15){
                strcpy(s->firstName, input);
            }else{
                printf("Invalid first name!\n");
            }
            break;
        case 4:
            printf("Edit course (%s): ", s->course);
            scanf("%s", input);
            if(strlen(input) <= 15){
                strcpy(s->course, input);
            }else{
                printf("Invalid course!\n");
            }
            break;
        case 5:
            printf("Edit year level (%i): ", s->yrLevel);
            scanf("%i", &tempInt);
            if(tempInt >= 1 && tempInt <= 5){
                s->yrLevel = tempInt;
            }else{
                printf("Invalid year level!\n");
            }
            break;
        case 6:
            printf("Edit age (%i): ", s->age);
            scanf("%i", &tempInt);
            if(tempInt > 0){
                s->yrLevel = tempInt;
            }else{
                printf("Invalid age!\n");
            }
            break;
        case 7:
            printf("Edit sex (%s): ", s->sex);
            scanf("%s", input);     
            if(strCmpLower(M, input) == 0 || strCmpLower(F, input) == 0){
                strcpy(s->sex, input);
            }else{
                printf("Invalid sex!\n");
            }
            break;
        case 8:
            printf("Edit final grade (%i): ", s->finalGrade);
            scanf("%i", &tempInt);
            if(tempInt >= 0 && tempInt <= 100){
                s->finalGrade = tempInt;
            }else{
                printf("Invalid final grade!\n");
            }
            break;
    }
}

void displayAllStudents(StudentRecord record){
    Student *current = record.head;

    for(int i = 0; i < record.size; i++){
        printf("\n\n");
        printStudent(current, 0);
        current = current->next;
    }
    printf("\n\n");
    printf("%i student(s) displayed\n\n", record.size);
}

void filterStudents(StudentRecord *record, int mode, char *detailToMatch){
    int flag, flag2 = 0;
    Student *current = record->head;

    for(int i = 0; i < record->size; i++){
        flag = 0;
        switch(mode){
            case 0:
                if(strCmpLower(current->lastName, detailToMatch) == 0){
                    flag = 1;
                }
                break;
            case 1:
                if(stringsAreSimilar(current->studentNo, detailToMatch) == 1){
                    flag = 1;
                }
                break;
            case 2:
                if(atoi(detailToMatch) == current->yrLevel){ //string to int
                    flag = 1;
                }
                break;
            case 3:
                if(strCmpLower(current->course, detailToMatch) == 0){
                    flag = 1;
                }
                break;
            case 4:
                if(strCmpLower(current->sex, detailToMatch) == 0){
                    flag = 1;
                }
                break;
            case 5:
                if(current->finalGrade >= 60){
                    flag = 1;
                }
                break;
            case 6:
                if(current->finalGrade < 60){
                    flag = 1;
                }
                break;
        }
        if(flag == 1){
            printf("\n\n");
            printStudent(current, 0);
            flag2 = 1;
        }
        current = current->next;
    }
    if(flag2 == 1){
        printf("\n\n");
    }else{
        printf("\nNo student found.\n");
    }
}

void sortRecord(StudentRecord *record, int mode){
    Student *prev, *current, *toChange;
    int i, j, flag;

    for(i = 1; i < record->size; i++){
        prev = getStudent(record, i - 1);
        current = prev->next;
        flag = -1;

        switch(mode){
            case 0:
                if(strCmpLower(prev->lastName, current->lastName) == 1){
                    toChange = record->head;
                    for(j = 0; j <= i; j++){
                        if(strCmpLower(toChange->lastName, current->lastName) == 1){
                            flag = 0;
                            break;
                        }else if(strCmpLower(toChange->next->lastName, current->lastName) == 1){
                            flag = 1;
                            break;
                        }

                        toChange = toChange->next;
                    }
                }
                break;
            case 1:
                if(strcmp(prev->studentNo, current->studentNo) == 1){
                    toChange = record->head;
                    for(j = 0; j <= i; j++){
                        if(strcmp(toChange->studentNo, current->studentNo) == 1){
                            flag = 0;
                            break;
                        }else if(strcmp(toChange->next->studentNo, current->studentNo) == 1){
                            flag = 1;
                            break;
                        }

                        toChange = toChange->next;
                    }
                }
                break;
            case 2:
                if(strCmpLower(prev->lastName, current->lastName) == 0){
                    toChange = record->head;
                    for(j = 0; j < i; j++){
                        if(strCmpLower(toChange->lastName, current->lastName) == 0 &&
                            strCmpLower(toChange->firstName, current->firstName) == 1)
                        {
                            flag = 0;
                            break;
                        }else if(strCmpLower(toChange->next->lastName, current->lastName) == 0 &&
                            strCmpLower(toChange->next->firstName, current->firstName) == 1)
                        {
                            flag = 1;
                            break;
                        }
                        if(toChange->next != 0){
                            toChange = toChange->next;
                        }                    
                    }
                }
                break;
        }

        if(flag == 1 || flag == 0){
            if(current == record->tail){
                record->tail = prev;
                prev->next = 0;
            }else{
                prev->next = current->next;
            }

            if(flag == 0){
                current->next = toChange;
                record->head = current;
            }else if(flag == 1){
                current->next = toChange->next;
                toChange->next = current;
            }
        }
        prev = current;
        current = current->next;
    }
}

int getStudeIndex(StudentRecord record, char *studentNo){
    Student *current = record.head;
    if(studNoIsValid(studentNo) == 1){
        int i;
        for(i = 0; i < record.size; i++){
            if(stringsAreSimilar(studentNo, current->studentNo)){
                return i;
            }
            current = current->next;
        }
        return -1;
    }
}

Student* getStudent(StudentRecord *record, int index){
    Student *current = record->head;
    if(index >= 0 && index < record->size){
        for(int i = 0; i < index; i++){
            current = current->next;
        }
        return current;
    }
}

int studNoIsValid(char *st){
    int flag = 0;
    for(int i = 0; st[i] != '\0'; i++){
        if(st[i] == 45){ //ascii code for hyphen '-'
            flag = 1;
        }
        if((st[i] < 48 || st[i] > 57) && st[i] != 45){ //48-57 is ascii code for 0-9
            return 0;
        }
    }
    return 1 * flag;
}

int stringsAreSimilar(char *st1, char *st2){
    if(strlen(st1) == strlen(st2)){
        int len = strlen(st1);
        for(int i = 0; i < len; i++){
            if(st1[i] != st2[i]){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

//same as strcmp (compare) but with lowercase versions
int strCmpLower(char *st1, char *st2){
    for(int i = 0; st1[i] != '\0' || st2[i] != '\0'; i++){
        if(tolower(st1[i]) > tolower(st2[i])){
            return 1;
        }else if(tolower(st1[i]) < tolower(st2[i])){
            return -1;
        }
    }
    return 0;
}

void printStudent(Student *s, int mode){
    switch(mode){
        case 0:
            printf("Student number: %s\n", s->studentNo);
            printf("Last name: %s\n", s->lastName);
            printf("First name: %s\n", s->firstName);
            printf("Course: %s\n", s->course);
            printf("Year level: %i\n", s->yrLevel);
            printf("Age: %i\n", s->age);
            printf("Sex: %s\n", s->sex);
            printf("Final grade: %i\n", s->finalGrade);
            break;
        case 1:
            printf("\nEdit student: %s\n", s->studentNo);
            printf("1. Student number\n");
            printf("2. Last name\n");
            printf("3. First name\n");
            printf("4. Course \n");
            printf("5. Year level\n");
            printf("6. Age\n");
            printf("7. Sex\n");
            printf("8. Final grade\n");
            printf("9. Back\n");
            break;
    }
}

int main(){
    StudentRecord record;
    Student *s;
    int index;
    char input[15];
    int choice1, choice2;
    recordInit(&record);

    while(true){
        system("cls");
        menu();
        printf("? ");
        scanf("%i", &choice1);

        switch(choice1){
            case 1: //enrol
                printf("\n");
                s = studentInit();

                if(getStudeIndex(record, s->studentNo) == -1){                    
                    enrolStudent(&record, s);
                    printf("\nStudent has been enrolled.\n");
                }else{
                    printf("\nStudent with that student number already exists. Student not enrolled.\n");
                }
                break;
            case 2: //drop
                printf("\nEnter the student number of that you wish to drop: ");
                scanf("%s", input);

                printf("Dropping the student...\n");
                if(studNoIsValid(input)){
                    index = getStudeIndex(record, input);
                    if(index != -1){
                        dropStudent(&record, index);
                        printf("Student has been dropped.\n\n");
                    }else{
                        printf("No student found.\n\n");
                    }
                }else{
                    printf("Invalid student number.\n\n");
                }
                break;
            case 3: //edit
                printf("Student number: ");
                scanf("%s", input);
                if(studNoIsValid(input)){
                    index = getStudeIndex(record, input);
                    if(index != -1){
                        s = getStudent(&record, index);
                        do{
                            printStudent(s, 1);
                            printf("\n? ");
                            scanf("%i", &choice2);
                            printf("\n");
                            editStudent(&record, index, choice2);
                        }while(choice2 != 9);
                        printf("Student successfully edited.\n\n");
                    }else{
                        printf("No student found.\n\n");
                    }
                }else{
                    printf("Invalid student number.\n\n");
                }
                break;
            case 4: //display all
                if(record.size != 0){
                    displayAllStudents(record);
                }else{
                    printf("No students yet. You may try adding one now.\n\n");
                }
                break;
            case 5: //filter by last name
                printf("Enter last name: ");
                scanf("%s", input);
                filterStudents(&record, 0, input);
                break;
            case 6: //filter by student no.
                printf("Enter student number: ");
                scanf("%s", input);

                if(studNoIsValid(input)){
                    filterStudents(&record, 1, input);                    
                }else{
                    printf("Invalid student number.\n\n");
                }
                break;
            case 7: //filter by year lvl
                printf("Enter year level: ");
                scanf("%i", &index);

                if(index >= 1 && index <= 5){
                    itoa(index, input, 10); //int to string
                    filterStudents(&record, 2, input);
                }else{
                    printf("Invalid year level.\n\n");            
                }
                break;
            case 8: //filter by course
                printf("Enter course: ");
                scanf("%s", input);
                filterStudents(&record, 3, input);
                break;
            case 9: //filter by sex
                printf("Enter sex: ");
                scanf("%s", input);
                filterStudents(&record, 4, input);
                break;
            case 10: //filter by passing
                filterStudents(&record, 5, "");
                break;
            case 11: //filter by failing
                filterStudents(&record, 6, "");
                break;
            case 12: //sort by last name
                if(record.size != 0){
                    sortRecord(&record, 0);
                    sortRecord(&record, 2);
                    displayAllStudents(record);
                }else{
                    printf("No students yet. You may try adding one now.\n");
                }
                break;
            case 13: //sort by student number
                if(record.size != 0){
                    sortRecord(&record, 1);
                    displayAllStudents(record);
                }else{
                    printf("No students yet. You may try adding one now.\n");
                }
                break;
            case 14: //exit
                exit(0);
                break;
        }
        system("pause");
    }
    return 0;
}



