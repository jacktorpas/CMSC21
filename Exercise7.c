#include <stdio.h>
#include <stdlib.h>

typedef struct Fraction{
    int num;
    int den;
} Fraction;

Fraction fracInput(){
    Fraction f;
    char chr;
    scanf("%i", &f.num);
    scanf("%c", &chr);
    if(chr == '/'){
        scanf("%i", &f.den);
    }else{
        f.den = 1;
    }
    return f;
}

Fraction add(Fraction a, Fraction b){
    Fraction sum;
    if(a.den == b.den){
        sum.num = a.num + b.num;
        sum.den = a.den;
    }else{
        sum.den = a.den * b.den;
        sum.num = ((sum.den / a.den) * a.num) + ((sum.den / b.den) * b.num);
    }
    simplify(&sum);
    return sum;
}

Fraction subtract(Fraction a, Fraction b){
    Fraction diff;
    if(a.den == b.den){
        diff.num = a.num - b.num;
        diff.den = a.den;
    }else{
        diff.den = a.den * b.den;
        diff.num = ((diff.den / a.den) * a.num) - ((diff.den / b.den) * b.num);
    }
    simplify(&diff);
    return diff;
}

Fraction multiply(Fraction a, Fraction b){
    Fraction prod;
    prod.num = a.num * b.num;
    prod.den = a.den * b.den;
    simplify(&prod);
    return prod;
}

Fraction divide(Fraction a, Fraction b){
    Fraction quot;
    if(b.num != 0){ //to prevent division by zero
        quot.num = a.num * b.den;
        quot.den = a.den * b.num;
    }
    simplify(&quot);
    return quot;
}

void fracOut(Fraction f){
    if(f.den == 1){
        printf("%i", f.num);
    }else{
        printf("%i/%i", f.num, f.den);
    }
}

void simplify(Fraction *f){
    if(f->den < 0){
        f->den *= -1;
        f->num *= -1;
    }
    int gcdNum = gcd(f->num, f->den);
    f->num /= gcdNum;
    f->den /= gcdNum;
}

int gcd(int a, int b){
    if(b == 0){
        return a;
    }else if(a >= b && b > 0){
        return gcd(b, a % b);
    }else{
        return gcd(abs(b), abs(a));
    }
}

int abs(int n){
    if(n < 0){
        return n * -1;
    }else{
        return n;
    }
}

int main(){
    Fraction a, b;
    int input;
    scanf("%i", &input);
    
    switch(input){
        case 1:
            a = fracInput();
            b = fracInput();
            fracOut(add(a, b));
            break;
        case 2:
            a = fracInput();
            b = fracInput();
            fracOut(subtract(a, b));
            break;
        case 3:
            a = fracInput();
            b = fracInput();
            fracOut(multiply(a, b));
            break;
        case 4:
            a = fracInput();
            b = fracInput();
            fracOut(divide(a, b));
            break;
        case 5:
            a = fracInput();
            simplify(&a);
            fracOut(a);
            break;
        default:
            printf("Invalid choice of input\n");
            break;
    }
    
    return 0;
}



