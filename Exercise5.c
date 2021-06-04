#include <stdio.h>
#include <stdbool.h>

void sortArray(int, int*);

int main(){
    int arr[100];
    scanf("%i", arr);
    for(int i = 1; i <= *arr; i++){
        scanf("%i", arr + i);
    }
    sortArray(*arr, arr);
    return 0;
}

void sortArray(int n, int* p){
    int i, j, temp;
    bool swapped = false;
    for(i = 0; i < n - 1; i++){
        swapped = false;
        for(j = 1; j <= n - 1 - i; j++){
            if(*(p + j) > *(p + (j + 1))){
                temp = *(p + j);
                *(p + j) = *(p + (j + 1));
                *(p + (j + 1)) = temp;
                swapped = true;
            }
        }
        if(swapped == false){ break; }
    }
    for(i = 1; i <= n; i++){
        printf("%i ", *(p + i));
    }
}