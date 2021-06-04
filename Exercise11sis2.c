#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct Student{
    int studentNo;
    int age, finalGrade, yrLevel;
    char lastName[15], firstName[15], course[15], sex[10];
} Student;

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

int enrolStudent(){
    Student *s = malloc(sizeof(Student));
    FILE *fp = fopen("student.bin", "ab+");
    if(fp == NULL){
        printf("Could not open student.bin\n");
        exit(-1);
    }
    do{
        printf("Enter student number (must be 1-300): ");
        scanf("%i", &s->studentNo);        
    }while(s->studentNo < 1 || s->studentNo > 300);
    fflush(stdin);
    do{
        printf("Enter last name: ");
        scanf("%s", s->lastName);        
    }while(strlen(s->lastName) > 15);
    fflush(stdin);
    do{
        printf("Enter first name: ");
        scanf("%s", s->firstName);        
    }while(strlen(s->firstName) > 15);
    fflush(stdin);
    do{
        printf("Enter course: ");
        scanf("%s", s->course);
    }while(strlen(s->course) > 15);
    fflush(stdin);
    do{
        printf("Enter the year level: ");
        scanf("%i", &s->yrLevel);
    }while(s->yrLevel < 1 || s->yrLevel > 5);
    fflush(stdin);
    do{
        printf("Enter age: ");
        scanf("%i", &s->age);
    }while(s->age < 0);
    fflush(stdin);
    do{
        printf("Sex: ");
        scanf("%s", s->sex);
    }while(strCmpLower("Male", s->sex) != 0 && strCmpLower("Female", s->sex) != 0);
    fflush(stdin);
    do{
        printf("Enter final grade: ");
        scanf("%i", &s->finalGrade);
    }while(s->finalGrade < 0 || s->finalGrade > 100);
    fflush(stdin);

    fwrite(s, sizeof(Student), 1, fp);
    printf("\nStudent %i enrolled.\n", s->studentNo);
    fclose(fp);
}

void editStudent(){
    Student *s = malloc(sizeof(Student));
    FILE *fp = fopen("student.bin", "rb");
    FILE *fp2 = fopen("temp.bin", "wb");
    if(fp == NULL){
        printf("Could not open student.bin\n");
        exit(-1);
    }
    int choice, s_num;
    
    printf("Student number: ");
    scanf("%i", &s_num);

    while(true){
        bool found = false;
        printStudent(s, 1);
        printf("\n? ");
        scanf("%i", &choice);
        while(fread(s, sizeof(Student), 1, fp)){
            if(s_num == s->studentNo){
                if(choice == 1){
                    found = true;
                    do{
                        printf("Edit student number (%i): ", s->studentNo);
                        scanf("%i", &s->studentNo);
                    }while(s->studentNo < 1 || s->studentNo > 300);                    
                }else if(choice ==2){
                    found = true;
                    do{
                        printf("Edit last name (%s): ", s->lastName);
                        scanf("%s", s->lastName);                
                    }while(strlen(s->lastName) > 15);
                }else if(choice == 3){
                    found = true;
                    do{
                        printf("Edit first name (%s): ", s->firstName);
                        scanf("%s", s->firstName);                
                    }while(strlen(s->firstName) > 15);
                }else if(choice == 4){
                    found = true;
                    do{
                        printf("Edit course (%s): ", s->course);
                        scanf("%s", s->course);
                    }while(strlen(s->course) > 15);
                }else if(choice == 5){
                    found = true;
                    do{
                        printf("Edit year level (%i): ", s->yrLevel);
                        scanf("%i", &s->yrLevel);
                    }while(s->yrLevel < 1 || s->yrLevel > 5);
                }else if(choice == 6){
                    found = true;
                    do{
                        printf("Edit age (%i): ", s->age);
                        scanf("%i", &s->age);
                    }while(s->age < 0);
                }else if(choice == 7){
                    found = true;
                    do{
                        printf("Edit sex (%s): ", s->sex);
                        scanf("%s", s->sex);                        
                    }while(strCmpLower("Male", s->sex) != 0 && strCmpLower("Female", s->sex) != 0);
                }else if(choice == 8){
                    found = true;
                    do{
                        printf("Edit final grade (%i): ", s->finalGrade);
                        scanf("%i", &s->finalGrade);
                    }while(s->finalGrade < 0 || s->finalGrade > 100);
                }else if(choice == 9){
                    break;
                }
            }
            fwrite(s, sizeof(Student), 1, fp2);
        }
        if(found == false && choice != 9){
            printf("No student found.\n");
        }else if(choice == 9){
            break;
        }else{
            fclose(fp);
            fclose(fp2);
            remove("student.bin");
            rename("temp.bin", "student.bin");
            printf("Student has been successfully edited.\n");
        }
    }    
}

void dropStudent(){
    Student *s = malloc(sizeof(Student));
    FILE *fp = fopen("student.bin", "rb+");
    FILE *fp2 = fopen("temp.bin", "ab+");
    if(fp == NULL){
        printf("Could not open student.bin\n");
        exit(-1);
    }
    int s_num;
    printf("Enter the student number of that you wish to drop: ");
    scanf("%i", &s_num);

    while(fread(s, sizeof(Student), 1, fp)){
        if(s_num != s->studentNo){
            fwrite(s, sizeof(Student), 1, fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    remove("student.bin");
    rename("temp.bin", "student.bin");
    printf("Student has been dropped.\n");
}

void displayAllStudents(){
    Student *s = malloc(sizeof(Student));
    FILE *fp = fopen("student.bin", "rb+");
    if(fp == NULL){
        printf("Could not open student.bin\n");
        exit(-1);
    }
    while(fread(s, sizeof(Student), 1, fp)){
        printStudent(s, 0);
    }
    fclose(fp);
}

void filterStudents(int choice){
    Student *s = malloc(sizeof(Student));
    FILE *fp = fopen("student.bin", "rb");
    if(fp == NULL){
        printf("Could not open student.bin\n");
        exit(-1);
    }
    char tempStr[15];
    int temp;
    
    if(choice == 5){
        printf("Enter last name: ");
        scanf("%s", tempStr);
        while(fread(s, sizeof(Student), 1, fp)){
            if(strcmp(tempStr, s->lastName) == 0) printStudent(s, 0);
        }
    }else if(choice == 6){
        printf("Enter student number: ");
        scanf("%i", &temp);
        while(fread(s, sizeof(Student), 1, fp)){
            if(temp == s->studentNo) printStudent(s, 0);
        }
    }else if(choice == 7){
        printf("Enter year level: ");
        scanf("%i", &temp);
        while(fread(s, sizeof(Student), 1, fp)){
            if(temp == s->yrLevel) printStudent(s, 0);
        }
    }else if(choice == 8){
        printf("Enter the course: ");
        scanf("%s", tempStr);
        while(fread(s, sizeof(Student), 1, fp)){
            if(strcmp(tempStr, s->course) == 0) printStudent(s, 0);
        }
    }else if(choice == 9){
        printf("Enter sex: ");
        scanf("%s", tempStr);
        while(fread(s, sizeof(Student), 1, fp)){
            if(strcmp(tempStr, s->sex) == 0) printStudent(s, 0);
        }
    }else if(choice == 10){
        bool passed = false;
        while(fread(s, sizeof(Student), 1, fp)){
            if(s->finalGrade >= 60){
                printStudent(s, 0);
                passed = true;
            }
        }
        if(passed == false){
            printf("No students have a passing grade.\n");
        }
    }else if(choice == 11){
        bool failed = false;
        while(fread(s, sizeof(Student), 1, fp)){
            if(s->finalGrade < 60){
                printStudent(s, 0);
                failed = true;
            }
        }
        if(failed == false){
            printf("No students have a failing grade.\n");
        }
    }

    fclose(fp);
}

void sortStudents(int choice){
    Student s;
    Student *t;
    FILE *fp = fopen("student.bin", "rb");
    if(fp == NULL){
        printf("Could not open student.bin\n");
        exit(-1);
    }
    fseek(fp, 0, SEEK_END);
    int count = ftell(fp) / sizeof(Student); //tells how many students so far

    t = calloc(count, sizeof(Student));
    rewind(fp);
    for(int i = 0; i < count; i++){
        fread(&t[i], sizeof(Student), 1, fp);
    }
    
    if(choice == 12){
        for(int i = 0; i < count; i++){
            for(int j = i + 1; j < count; j++){
                if(strcmp(t[i].lastName, t[j].lastName) == 0){
                    if(strcmp(t[i].firstName, t[i].firstName) > 0){
                        s = t[i];
                        t[i] = t[j];
                        t[j] = s;
                    }
                }else if(strcmp(t[i].lastName, t[j].lastName) > 0){
                    s = t[i];
                    t[i] = t[j];
                    t[j] = s;
                }
            }
        }
    }else if(choice == 13){
        for(int i = 0; i < count; i++){
            for(int j = i + 1; j < count; j++){
                if(t[i].studentNo > t[j].studentNo){
                    s = t[i];
                    t[i] = t[j];
                    t[j] = s;
                }
            }
        }
    }
    //displaying the newly sorted records
    for(int i = 0; i < count; i++){
        printStudent(&t[i], 0);
    }
    fclose(fp);
}

void printStudent(Student *s, int mode){
    switch(mode){
        case 0:
            printf("\nStudent number: %i\n", s->studentNo);
            printf("Last name: %s\n", s->lastName);
            printf("First name: %s\n", s->firstName);
            printf("Course: %s\n", s->course);
            printf("Year level: %i\n", s->yrLevel);
            printf("Age: %i\n", s->age);
            printf("Sex: %s\n", s->sex);
            printf("Final grade: %i\n\n", s->finalGrade);
            break;
        case 1:
            printf("\nEdit:\n");
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

int main(){
    int choice;
    while(true){
        system("cls");
        menu();
        printf("\n? ");
        scanf("%i", &choice);

        switch(choice){
            case 1: enrolStudent(); break;
            case 2: dropStudent(); break;
            case 3: editStudent(); break;
            case 4: displayAllStudents(); break;
            case 5: filterStudents(5); break;
            case 6: filterStudents(6); break;
            case 7: filterStudents(7); break;
            case 8: filterStudents(8); break;
            case 9: filterStudents(9); break;
            case 10: filterStudents(10); break;
            case 11: filterStudents(11); break;
            case 12: sortStudents(12); break;
            case 13: sortStudents(13); break;
            case 14: exit(0); break;
        }
        system("pause");
    }

    return 0;
}





