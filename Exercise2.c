#include <stdio.h>

int main(){
    int input[25];
    char space;
    printf("Enter the input: ");
    int i = 0;
    do{
        scanf("%i%c", &input[i], &space);
        i++;
    }while(space != '\n');
    if(input[0] == 1){
        printf("%i", division(input[1], input[2]));
    }else if(input[0] == 2){
        int n1, n2;
        if(input[1] > input[2]){
            n1 = input[1];
            n2 = input[2];
        }else{
            n1 = input[2];
            n2 = input[1];
        }
        if(relPrime(n1, n2) == 1){
            printf("1");
        }else{
            printf("0");
        }
    }else if(input[0] == 3){
        printf("%i", search(input, 2, input[1] + 1, input[input[1] + 2]));
    }
    return 0;
}

int division(int a, int b){
    if(a < b){
        return 0;
    }else{
        return 1 + division(a-b, b);
    }
}

int relPrime(int a, int b){
    if(b == 0){
        return a;
    }else{
        return relPrime(b, a % b);
    }
}

int search(int input[], int f, int l, int x){
    if(l < 2){
        return 0;
    }
    if(input[f] == x){
        return 1;
    }
    if(input[l] == x){
        return 1;
    }
    return search(input, f+1, l-1, x);
}