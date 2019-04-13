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

typedef struct _Date_ {
    int year;
    int month;
    int day;
} Date;

typedef struct _Student_ {
   // фамилия, имя, отчество, дата рождения, средняя успеваемость
    char familiya[MAX_NAME];
    char imya[MAX_NAME];
    char otchestvo[MAX_NAME];
    double uspevaemost;
    Date birth_date;
    
    struct _Student_* next;
} Student;

char in_buffer[256];

size_t write_student(FILE* file, Student* student){
    
    size_t byteSize = 0;
    size_t size = fwrite(student->familiya, MAX_NAME, 1, file);
    byteSize = size;
    if(size == 0){
        printf("Error: cant write file\n");
        return -1;
    }
    size = fwrite(student->imya, MAX_NAME, 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant write file\n");
        return -1;
    }
    size = fwrite(student->otchestvo, MAX_NAME, 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant write file\n");
        return -1;
    }
    size = fwrite(&(student->birth_date.day), sizeof(int), 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant write file\n");
        return -1;
    }
    size = fwrite(&(student->birth_date.month), sizeof(int), 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant write file\n");
        return -1;
    }
    size = fwrite(&(student->birth_date.year), sizeof(int), 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant write file\n");
        return -1;
    }
    size = fwrite(&(student->uspevaemost), sizeof(double), 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant write file\n");
        return -1;
    }
    
    return byteSize;
}

Student* read_student(FILE* file){
    Student* student = malloc(sizeof(Student));
    memset(student, 0, sizeof(Student));

    size_t byteSize = 0;
    size_t size = fread(student->familiya, MAX_NAME, 1, file);
    byteSize = size;
    if(size == 0){
        printf("Error: cant read file\n");
        free(student);
        return NULL;
    }
    size = fread(student->imya, MAX_NAME, 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant read file\n");
        free(student);
        return NULL;
    }
    size = fread(student->otchestvo, MAX_NAME, 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant read file\n");
        free(student);
        return NULL;
    }
    size = fread(&(student->birth_date.day), sizeof(int), 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant read file\n");
        free(student);
        return NULL;
    }
    size = fread(&(student->birth_date.month), sizeof(int), 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant read file\n");
        free(student);
        return NULL;
    }
    size = fread(&(student->birth_date.year), sizeof(int), 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant read file\n");
        free(student);
        return NULL;
    }
    size = fread(&(student->uspevaemost), sizeof(double), 1, file);
    byteSize += size;
    if(size == 0){
        printf("Error: cant read file\n");
        free(student);
        return NULL;
    }
    
    return student;
}



void fill_student(Student* student){
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

void print_student(Student* student){
    if(student == NULL){
        printf("Error: zero pointer\n");
        return;
    }
    printf("%s %s %s %02d.%02d.%d. Mark: %2.2f\n", student->familiya, student->imya, student->otchestvo, student->birth_date.day, student->birth_date.month, student->birth_date.year, student->uspevaemost);
}

void print_group(Student* list){
    if(list == NULL){
        printf("Empty list\n");
        return;
    }
    Student* next = list;
    int number = 1;
    while (next != NULL) {
        printf("%d: ", number++);
        print_student(next);
        next = next->next;
    }
    printf("========================================\n");
}

void add_student(Student** list, Student* newStudent){
    if(list == NULL){
        printf("Error: zero list");
        return;
    }
    if(newStudent == NULL){
        printf("Error: zero student");
        return;
    }

    Student** next = list;
    while (1) {
        if (*next == NULL) {
            *next = newStudent;
            break;
        }
        next = &((*next)->next);
    }
}

void remove_student(Student** list, int index){
    if(list == NULL){
        printf("Error: zero list");
        return;
    }

    Student** next = list;
    int i = 1;
    while (1) {
        if (*next == NULL) {
            printf("No index %d:%d\n", index, i);
            break;
        }
        if (i == index) {
            Student* tmp = *next;
            *next = (*next)->next;
            free(tmp);
            break;
        }
        next = &((*next)->next);
        ++i;
    }
}

void search_name(Student* root, char* name){
    if(name == NULL){
        printf("Error: noname");
        return;
    }
    Student* next = root;
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

void search_marks(Student* root, int mark_min, int mark_max){
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
    Student* next = root;
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

void search_date(Student* root, int day, int month){
    Student* next = root;
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

void search_student(Student* root){
    int finish = 0;
    do {
        char name[MAX_NAME] = {0};
        int mark_max = 0;
        int mark_min = 0;
        int day = 0;
        int month = 0;
        int cc = 0;
        
        int in_success = 0;
        while (!in_success) {
            printf("\nEnter sort type:\n1. Name\n2. Marks\n3. Birth date\n4. Cancel\n");
            char * rr = fgets(in_buffer, sizeof(in_buffer), stdin);
            if (rr != NULL) {
                int scanned = sscanf(in_buffer, "%d", &cc);
                if (scanned == 1) {
                    in_success = 1;
                    break;
                } else {
                    printf("Expected 1 argument, got %d\n", scanned);
                }
            }
        }

        switch (cc) {
            case 1:
                in_success = 0;
                while (!in_success) {
                    printf("Enter student first name\n");
                    char * rr = fgets(in_buffer, sizeof(in_buffer), stdin);
                    if (rr != NULL) {
                        int scanned = sscanf(in_buffer, "%s", name);
                        if (scanned != 1) {
                            printf("Error: 1 argument expected, got %d\n", scanned);
                        } else {
                            in_success = 1;
                            break;
                        }
                    }
                }
                printf("=========== search name: %s\n", name);
                search_name(root, name);
                break;
                
            case 2: {
                in_success = 0;
                while (!in_success) {
                    printf("Enter student marks 'min max':\n");
                    char * rr = fgets(in_buffer, sizeof(in_buffer), stdin);
                    if (rr != NULL) {
                        int scanned = sscanf(in_buffer, "%d %d", &mark_min, &mark_max);
                        if (scanned != 2) {
                            printf("Error: 2 arguments expected, got %d\n", scanned);
                        } else {
                            in_success = 1;
                            break;
                        }
                    }
                }
                printf("=========== search marks [%d:%d]\n", mark_min, mark_max);
                search_marks(root, mark_min, mark_max);
            } break;
                
            case 3: {
                in_success = 0;
                while (!in_success) {
                    printf("Enter birth day 'DD.MM'\n");
                    char * rr = fgets(in_buffer, sizeof(in_buffer), stdin);
                    if (rr != NULL) {
                        int scanned = sscanf(in_buffer, "%d.%d", &day, &month);
                        if (scanned != 2) {
                            printf("Error: 2 arguments expected, got %d\n", scanned);
                        } else {
                            in_success = 1;
                            break;
                        }
                    }
                }
                printf("=========== search bday: %d.%d\n", day, month);
                search_date(root, day, month);
            } break;
                
            case 4:
                finish = 1;
                break;
        }
    } while (!finish);
}

void save_category(Student* root, const char* filename){
    int mark1 = 0;
    int mark2 = 50;
    int mark3 = 70;
    int mark4 = 100;
    size_t lenght = strlen(filename);
    char* name2 = malloc(lenght + 10);
    memcpy(name2, filename, lenght);
    name2[lenght] = '1';
    name2[lenght + 1] = '\0';
    FILE *file1 = fopen(name2, "w+");
    name2[lenght] = '2';
    FILE *file2 = fopen(name2, "w+");
    name2[lenght] = '3';
    FILE *file3 = fopen(name2, "w+");
    free(name2);
    name2 = NULL;
    Student* next = root;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    while (next != NULL) {
        if(next->uspevaemost >= mark1 && next->uspevaemost < mark2){
            write_student(file1, next);
            count1++;
        }
        
        else if(next->uspevaemost >= mark2 && next->uspevaemost < mark3){
            write_student(file2, next);
            count2++;
        }
        else if(next->uspevaemost >= mark3 && next->uspevaemost <= mark4){
            write_student(file3, next);
            count3++;
        }
        next = next->next;
    }
    fclose(file1);
    fclose(file2);
    fclose(file3);

    printf("%d low mark, %d medium mark, %d high mark\n---------------------------------\n", count1, count2, count3);
    
}

void search_category(Student* root){
    int finish = 0;
    do {
        int cc = 0;
        int mark1 = 0;
        int mark2 = 50;
        int mark3 = 70;
        int mark4 = 100;
        
        int in_success = 0;
        while (!in_success) {
            printf("\nEnter category type:\n1. Low marks\n2. Medium marks\n3. High marks\n4. Cancel\n");
            char * rr = fgets(in_buffer, sizeof(in_buffer), stdin);
            if (rr != NULL) {
                int scanned = sscanf(in_buffer, "%d", &cc);
                if (scanned == 1) {
                    in_success = 1;
                    break;
                } else {
                    printf("Expected 1 argument, got %d\n", scanned);
                }
            }
        }
        
        switch (cc) {
            case 1:
                in_success = 0;
                while (!in_success) {
                    search_marks(root, mark1, mark2);
                    in_success = 1;
                    break;
                }
    
            case 2: {
                in_success = 0;
                search_marks(root, mark2, mark3);
            } break;
                
            case 3: {
                in_success = 0;
                search_marks(root, mark3, mark4);
            } break;
                
            case 4:
                finish = 1;
                break;
        }
    } while (!finish);
}

int main(int argc, const char * argv[]) {
    Student* root = NULL;
    if(argc != 2){
        printf("Error: no file name\n");
        exit(-1);
    }
    const char* filename = argv[1];
//    FILE *file = fopen(filename, "w");
//    if(file == NULL){
//        printf("Error: cant open file %s\n", filename);
//        exit(-1);
//    }
//    Student* testStudent = malloc(sizeof(Student));
//    fill_student(testStudent);
//    print_student(testStudent);
//    size_t byte = write_student(file, testStudent);
//    printf("Written %d byte\n",(int)byte);
//    int x = fclose(file);
//    if(x != 0){
//        printf("Error: cant close file");
//    }
//
//    file = fopen(filename, "r");
//    if(file == NULL){
//        printf("Error: cant open file %s\n", filename);
//        exit(-1);
//    }
//    Student* student = read_student(file);
//    if(student == NULL){
//        printf("Error: no students\n");
//    }
//    else{
//        print_student(student);
//        free(student);
//    }
//    x = fclose(file);
//    if(x != 0){
//        printf("Error: cant close file");
//    }
    
    
    
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Error: cant open file %s\n", filename);
        exit(-1);
    }
    
    Student** lastStudent = &root;
    do{
        Student* student = read_student(file);
        if(student == NULL){
            break;
        }
        *lastStudent = student;
        lastStudent = &student->next;
    }while(1);
    
    fclose(file);
    file = fopen(filename, "a+");
    if(file == NULL){
        printf("Error: cant open file %s\n", filename);
        exit(-1);
    }
    
    
    int stop = 0;
    do{
        int mode = 0;
        char familiya[MAX_NAME];
        char imya[MAX_NAME];
        char otchestvo[MAX_NAME];
        double uspevaemost = 0.0;
        int index = 0;
        int permition = 0;
        int in_success = 0;
        Date date = {0};
        
        while (!in_success) {
            printf("0. Save group on disk\n1. Add new student\n2. Print all group\n3. Search\n4. Delete student by number\n5. Classify by categories\n6. Exit\n");
            char * rr = fgets(in_buffer, sizeof(in_buffer), stdin);
            if (rr != NULL) {
                int scanned = sscanf(in_buffer, "%d", &mode);
                if (scanned == 1) {
                    in_success = 1;
                    break;
                } else {
                    printf("Error: 1 int argument expected, got %d\n", scanned);
                }
            }
        }
        
        switch (mode) {
            case 1:
                in_success = 0;
                while (!in_success) {
                    printf("Enter student data: 'f.name l.name s.name DD.MM.YYYY mark':\n");
                    char *rr = fgets(in_buffer, sizeof(in_buffer), stdin);
                    if (rr != NULL) {
                        int in_count = sscanf(in_buffer, "%s %s %s %d.%d.%d %lf", familiya, imya, otchestvo, &date.day, &date.month, &date.year, &uspevaemost);
                        if (in_count == 7) {
                            in_success = 1;
                            break;
                        } else {
                            printf("Error: 7 arguments expected (got %d)\n", in_count);
                        }
                    }
                }
                Student * student = malloc(sizeof(Student));
                strcpy(student->familiya, familiya);
                strcpy(student->imya, imya);
                strcpy(student->otchestvo, otchestvo);
                student->birth_date = date;
                student->uspevaemost = uspevaemost;
                student->next = NULL;
                add_student(&root, student);
                write_student(file, student);
                break;
                
            case 2:
                print_group(root);
                break;
                
            case 3:
                search_student(root);
                break;
                
            case 4:
                in_success = 0;
                while (!in_success) {
                    printf("Enter student number:\n");
                    char *rr = fgets(in_buffer, sizeof(in_buffer), stdin);
                    if (rr != NULL) {
                        int in_count = sscanf(in_buffer, "%d", &index);
                        if (in_count == 1) {
                            in_success = 1;
                            break;
                        } else {
                            printf("Error: 1 arguments expected (got %d)\n", in_count);
                        }
                    }
                }
                remove_student(&root, index);
                break;
                
            case 0: {
                Student* lastStudent = root;
                fclose(file);
                file = fopen(filename, "a+");
                if(file == NULL){
                    printf("Error: cant open file %s\n", filename);
                    exit(-1);
                }
                
                while(lastStudent != NULL){
                    write_student(file, lastStudent);
                    lastStudent = lastStudent->next;
                }
            } break;
                
            case 6:
                printf("Are you shure about this? (666 - yes)\n");
                scanf("%d", &permition);
                while ((getchar()) != '\n');
                if(permition == 666){
                    stop = 1;
                }
                break;
                
            case 5:
                save_category(root, filename);
                search_category(root);
                break;
        }
    } while(!stop);
    
    fclose(file);

    return 0;
}
