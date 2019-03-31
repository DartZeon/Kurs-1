//
//  main.c
//  lab2
//
//  Created by D1 on 3/31/19.
//  Copyright © 2019 D1. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 100

typedef struct Date {
    int year;
    int month;
    int day;
} Date;

typedef struct Student {
   // фамилия, имя, отчество, дата рождения, средняя успеваемость
    char familiya[MAX_NAME];
    char imya[MAX_NAME];
    char otchestvo[MAX_NAME];
    double uspevaemost;
    struct Date birth_date;
    
    struct Student* next;
} Student;

void fill_student(struct Student* student){
    if(student == NULL){
        printf("Error: zero pointer");
        return;
    }
    strcpy(student->familiya, "Ivanov");
    strcpy(student->imya, "Ivan");
    strcpy(student->otchestvo, "Ivanovich");
    student->birth_date.day = 01;
    student->birth_date.month = 01;
    student->birth_date.year = 2001;
    student->uspevaemost = 50.5;
}

void print_student(struct Student* student){
    if(student == NULL){
        printf("Error: zero pointer\n");
        return;
    }
    printf("%s %s %s %02d.%02d.%d. Mark: %2.2f\n", student->familiya, student->imya, student->otchestvo, student->birth_date.day, student->birth_date.month, student->birth_date.year, student->uspevaemost);
}

void print_group(struct Student* list){
    if(list == NULL){
        printf("Empty list\n");
        return;
    }
    struct Student* next = list;
    int number = 1;
    while (next != NULL) {
        printf("%d: ", number++);
        print_student(next);
        next = next->next;
    }
    printf("========================================\n");
}

void add_student(struct Student** list, struct Student* newStudent){
    if(list == NULL){
        printf("Error: zero list");
        return;
    }
    if(newStudent == NULL){
        printf("Error: zero student");
        return;
    }

    struct Student** next = list;
    while (1) {
        if (*next == NULL) {
            *next = newStudent;
            break;
        }
        next = &((*next)->next);
    }
}

void remove_student(struct Student** list, int index){
    if(list == NULL){
        printf("Error: zero list");
        return;
    }

    struct Student** next = list;
    int i = 1;
    while (1) {
        if (*next == NULL) {
            printf("No index %d:%d\n", index, i);
            break;
        }
        if (i == index) {
            struct Student* tmp = *next;
            *next = (*next)->next;
            free(tmp);
            break;
        }
        next = &((*next)->next);
        ++i;
    }
}

void search_name(struct Student* root, char* name){
    if(name == NULL){
        printf("Error: noname");
        return;
    }
    struct Student* next = root;
    int i = 1;
    int count = 0;
    while (next != NULL) {
        if(strcmp(next->familiya, name) == 0){
            printf("%d: ", i);
            print_student(next);
            count++;
        }
        next = next->next;
        i++;
    }
    printf("%d found\n---------------------------------\n", count);
}

void search_marks(struct Student* root, int mark_min, int mark_max){
    if(mark_min > mark_max){
        printf("Error");
        return;
    }
    if(mark_min > 100 || mark_min < 0){
        printf("Error: incorrect mark %d \n", mark_min);
        return;
    }
    if(mark_max > 100 || mark_max < 0){
        printf("Error: incorrect mark %d \n", mark_max);
        return;
    }
    struct Student* next = root;
    int i = 1;
    int count = 0;
    while (next != NULL) {
        if(next->uspevaemost < mark_max && next->uspevaemost > mark_min){
            printf("%d: ", i);
            print_student(next);
            count++;
        }
        next = next->next;
        i++;
    }
    printf("%d found\n---------------------------------\n", count);
}

void search_date(struct Student* root, int day, int month){
    struct Student* next = root;
    int i = 1;
    int count = 0;
    while (next != NULL) {
        if(next->birth_date.day == day && next->birth_date.month == month){
            printf("%d: ", i);
            print_student(next);
            count++;
        }
        next = next->next;
        i++;
    }
    printf("%d found\n---------------------------------\n", count);
}

void search_student(struct Student* root){
    int s = 0;
    do{
        printf("Enter sort type:\n1. Name\n2. Marks\n3. Birth date\n4. Cancel\n");
        char name[MAX_NAME] = {0};
        int mark_max = 0;
        int mark_min = 0;
        int day = 0;
        int month = 0;
        int cc = 0;
        int entered = scanf("%d", &cc);
        if (entered < 1) {
            continue;
        }
        while ((getchar()) != '\n');

        switch (cc) {
            case 1:
                printf("Enter student first name\n");
                scanf("%s", name);
                while ((getchar()) != '\n');
                printf("=========== NAME:%s\n", name);
                search_name(root, name);
                break;
            case 2: {
                int cc2 = EOF;
                while (cc2 == EOF) {
                    printf("Enter student marks\n");
                    cc2 = scanf("%d %d", &mark_min, &mark_max);
                }
                while ((getchar()) != '\n');
//                if (cc2 == 2) {
//                    break;
//                }
                printf("=========== marks [%d:%d]\n", mark_min, mark_max);
                search_marks(root, mark_min, mark_max);
            } break;
            case 3: {
                int cc2 = EOF;
                while (cc2 == EOF) {
                    printf("Enter birth day\n");
                    scanf("%d.%d", &day, &month);
                }
                while ((getchar()) != '\n');
                printf("=========== bday: %d.%d\n", day, month);
                search_date(root, day, month);
            } break;
            case 4:
                s = 1;
                break;
        }
    }while (!s);
}

int main(int argc, const char * argv[]) {
    int stop = 0;
    struct Student* root = NULL;
    do{
        printf("1. Add new student\n2. Print all group\n3. Search\n4. Delete student by number\n5. Exit\n");
        int mode = 0;
        char familiya[MAX_NAME];
        char imya[MAX_NAME];
        char otchestvo[MAX_NAME];
        double uspevaemost;
        int index = 0;
        int permition = 0;
        struct Date date;
        scanf("%d", &mode);
        while ((getchar()) != '\n');
        switch (mode) {
            case 0:
                stop = 1;
                break;
            case 1:
                printf("Enter student data\n");
                struct Student * student;
                student = malloc(sizeof(struct Student));
                scanf("%s %s %s %d.%d.%d %lf", familiya, imya, otchestvo, &date.day, &date.month, &date.year, &uspevaemost);
                while ((getchar()) != '\n');
                strcpy(student->familiya, familiya);
                strcpy(student->imya, imya);
                strcpy(student->otchestvo, otchestvo);
                student->birth_date = date;
                student->uspevaemost = uspevaemost;
                student->next = NULL;
                add_student(&root, student);
                break;
            case 2:
                print_group(root);
                break;
            case 3:
                search_student(root);
                break;
            case 4:
                printf("Enter student number:\n");
                scanf("%d", &index);
                while ((getchar()) != '\n');
                remove_student(&root, index);
                break;
            case 5:
                printf("Are you shure about this? (666 - yes)\n");
                scanf("%d", &permition);
                while ((getchar()) != '\n');
                if(permition == 666){
                    stop = 1;
                }
                break;
        }
    }while(!stop);

    return 0;
}
