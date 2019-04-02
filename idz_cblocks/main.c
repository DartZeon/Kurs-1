#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 10
#define MAX_STRING 100
#define SWAP(x,y) {typeof(x) tmp = x; x=y; y=tmp;}

enum Type {
    Gold=0,
    Silver,
    Bronze,
    Type_COUNT
};

struct Medals {
    char *country_name[COUNT];
    int *table[COUNT];
} Medals;



struct Medals* create_medals(){
    struct Medals* medals = malloc(sizeof(Medals));
    for(int i = 0; i < COUNT; i++){
        medals->country_name[i] = malloc(MAX_STRING);
        medals->table[i] = malloc(sizeof(int)*Type_COUNT);
    }
    return medals;
}

void del_medals(struct Medals* medals){
    if(medals == NULL){
        printf("Error: zero medals");
        return;
    }
    for(int i = 0; i < COUNT; i++){
        free(medals->country_name[i]);
        free(medals->table[i]);
    }
    free (medals);
}


void print_country(struct Medals* medals, char *name){
    if(medals == NULL){
        printf("Error: zero medals");
        return;
    }
    if(name == NULL){
        printf("Error: zero names");
        return;
    }
    for(int i = 0; i < COUNT; i++){
        char* country = medals->country_name[i];
        if(country == NULL){
            return;
        }
        if(strlen(country) == 0){
            return;
        }
        if(0 == strcmp(country, name)){
            printf("%d: %s \t", i, country);
            for(int j = 0; j < Type_COUNT; j++){
                printf("%d ", medals->table[i][j]);
            }
            printf("\n");
        }
    }
}

void print_medals(struct Medals* medals){
    if(medals == NULL){
        printf("Error: zero medals");
        return;
    }
    for(int i = 0; i < COUNT; i++){
        char* country = medals->country_name[i];
        if(country == NULL){
            return;
        }
        if(strlen(country) == 0){
            return;
        }
        printf("%d: %s \t", i, country);
        for(int j = 0; j < Type_COUNT; j++){
            printf("%d ", medals->table[i][j]);
        }
        printf("\n");
    }
}

void fill_struct(struct Medals* medals){
    char *name = "Germany";
    strcpy(medals->country_name[2], name);
    medals->table[0][Gold] = 5;
    medals->table[0][Silver] = 6;
    medals->table[0][Bronze] = 2;
    
    name = "Canada";
    strcpy(medals->country_name[0], name);
    medals->table[1][Gold] = 5;
    medals->table[1][Silver] = 8;
    medals->table[1][Bronze] = 10;
    
    name = "France";
    strcpy(medals->country_name[1], name);
    medals->table[2][Gold] = 5;
    medals->table[2][Silver] = 8;
    medals->table[2][Bronze] = 4;
    
    name = "Australia";
    strcpy(medals->country_name[3], name);
    medals->table[3][Gold] = 8;
    medals->table[3][Silver] = 2;
    medals->table[3][Bronze] = 6;
}

void insert_data(struct Medals* medals, char *country, int *number){
    if(medals == NULL){
        printf("Zero medals\n");
        return;
    }
    if(number == NULL){
        printf("Zero numbers\n");
        return;
    }
    if(country == NULL){
        printf("Zero countries\n");
        return;
    }
    for(int i = 0; i < COUNT; i++){
        char* country2 = medals->country_name[i];
        if(strcmp(country, country2) == 0){
            for(int j = 0; j < Type_COUNT; j++){
                medals->table[i][j] += number[j];
            }
            return;
        }
        if(strlen(country2) == 0){
            strcpy(medals->country_name[i], country);
            for(int j = 0; j < Type_COUNT; j++){
                medals->table[i][j] = number[j];
            }
            return;
        }
    }
    printf("No more place\n");
}

void sort_medals_byname(struct Medals* medals){
    if(medals == NULL){
        printf("Zero medals\n");
        return;
    }
    int didSwap = 0;
    do{
        didSwap = 0;
        for(int i = 1; i < COUNT; i++){
            if(strlen(medals->country_name[i]) == 0){
                break;
            }
            if(strcmp(medals->country_name[i - 1], medals->country_name[i]) > 0) {
                SWAP(medals->country_name[i - 1], medals->country_name[i]);
                for(int j = 0; j < Type_COUNT; j++){
                    SWAP(medals->table[i - 1], medals->table[i]);
                }
                didSwap = 1;
            }
        }
    }while(didSwap);
}

void sort_medals_bytype(struct Medals* medals){
    if(medals == NULL){
        printf("Zero medals\n");
        return;
    }
    int didSwap = 0;
    do{
        didSwap = 0;
        for(int i = 1; i < COUNT; i++){
            if(strlen(medals->country_name[i]) == 0){
                break;
            }
            int * table0 = medals->table[i - 1];
            int * table1 = medals->table[i];
            double sum0 = 10000.0*(double)table0[Gold] + 1000.0*(double)table0[Silver] + (double)table0[Bronze];
            double sum1 = 10000.0*(double)table1[Gold] + 1000.0*(double)table1[Silver] + (double)table1[Bronze];
            if(sum1 > sum0) {
                SWAP(medals->country_name[i - 1], medals->country_name[i]);
                for(int j = 0; j < Type_COUNT; j++){
                    SWAP(medals->table[i - 1], medals->table[i]);
                }
                didSwap = 1;
            }
        }
    }while(didSwap);
}

int main(int argc, const char * argv[]) {
    struct Medals*data = create_medals();
    fill_struct(data);
    print_medals(data);
    
    int stop = 0;
    do{
        printf("\n1 - change data\n2 - print country\n3 - print table\n4 - exit\n");
        int mode = 0;
        int number[Type_COUNT] = {0};
        char name[MAX_STRING] = {0};
        scanf("%d", &mode);
        switch (mode) {
            case 0:
                stop = 1;
                break;
            case 1:
                printf("Country, gold, silver, bronze\n");
                scanf("%s %d %d %d", name, &number[Gold], &number[Silver], &number[Bronze]);
                insert_data(data, name, number);
                sort_medals_byname(data);
                break;
            case 2:
                printf("Country\n");
                scanf("%s", name);
                print_country(data, name);
                break;
            case 3:
                printf("Country table\n");
                sort_medals_bytype(data);
                print_medals(data);
                break;
            case 4:
                stop = 1;
                break;
                
            default:
                break;
        }
    }while(!stop);
    return 0;
}
