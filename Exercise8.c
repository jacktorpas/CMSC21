#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector{
    int size;
    int cap;
    char *st;
} vector;

void initString(vector *vString, char* st){
    vectorInit(vString);
    int len = strlen(st);

    if(vString->cap < len){
        resize(vString, len);
    }

    for(int i = 0; i < len; i++){
        vString->st[i] = st[i];
        vString->size++;
    }

    return;
}

void concatenate(vector *combined, vector *a, vector *b){
    vectorInit(combined);
    if(combined->cap < a->size + b->size){
        resize(combined, a->size + b->size);
    }
    for(int i = 0; i < a->size; i++){
        combined->st[i] = a->st[i];
        combined->size++;
    }
    for(int i = 0; i < b->size; i++){
        combined->st[a->size + i] = b->st[i];
        combined->size++;
    }
    return;
}

void slice(vector *sliced, vector *source, int start, int end){
    vectorInit(sliced);
    if(start > end || start < 0 || end > source->size){
        return;
    }
    if(sliced->cap < end - start){
        resize(sliced, end - start);
    }
    for(int i = start; i < end; i++){
        sliced->st[i - start] = source->st[i];
        sliced->size++;
    }
    return;
}

void vectorInit(vector *v){
    v->size = 0;
    v->cap = 10;
    v->st = (char*) malloc(sizeof(char) * v->cap);
    return;
}

void printVector(vector *v){
    for(int i = 0; i < v->size; i++){
        printf("%c", v->st[i]);
    }
    return;
}

void resize(vector *v, int size){
    int newCap;
    if(size == -1){
        newCap = v->size * 2;
    }else{
        newCap = size;
    }

    char* newSt = (char*) malloc(sizeof(char) * newCap);
    for(int i = 0; i < v->size; i++){
        newSt[i] = v->st[i];
    }

    v->cap = newCap;
    free(v->st);
    v->st = newSt;
    return;
}

int strLen(char *st){
    int i;
    for(i = 0; st[i] != '\0'; i++);
    return i;
}

int main(){
    vector a, b, c;
    char st[15];
    int input, start, end;
    scanf("%i", &input);

    switch(input){
        case 1:
            scanf("%s", st);
            if(strLen(st) <= 15){
                initString(&a, st);
            }else{ break; }

            scanf("%s", st);
            if(strLen(st) <= 15){
                initString(&b, st);
            }else{ break; }

            concatenate(&c, &a, &b);
            printVector(&c);
            break;
        case 2:
            scanf("%s", st);
            if(strLen(st) <= 15){
                initString(&a, st);
            }else{ break; }

            scanf("%i %i", &start, &end);
            slice(&b, &a, start, end);
            printVector(&b);
            break;
    }

    return 0;
}