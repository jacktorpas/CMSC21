#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

class Fraction {
    public:
        int num;
        int den;

        void input(){
            char chr;
            scanf("%i", &this->num); //scanf is used for now to handle tricky inputs such as this
            scanf("%c", &chr);
            if(chr == '/'){
                scanf("%i", &this->den);
            }else{
                this->den = 1;
            }
        }

        Fraction add(Fraction f){
            Fraction sum;
            if(this->den == f.den){
                sum.num = this->num + f.num;
                sum.den = f.den;
            }else{
                sum.den = this->den * f.den;
                sum.num = ((sum.den / this->den) * this->num) + ((sum.den / f.den) * f.num);
            }
            sum.simplify();
            return sum;
        }

        Fraction subtract(Fraction f){
            Fraction diff;
            if(this->den == f.den){
                diff.num = this->num - f.num;
                diff.den = f.den;
            }else{
                diff.den = this->den * f.den;
                diff.num = ((diff.den / this->den) * this->num) - ((diff.den / f.den) * f.num);
            }
            diff.simplify();
            return diff;
        }

        Fraction multiply(Fraction f){
            Fraction prod;
            prod.num = this->num * f.num;
            prod.den = this->den * f.den;
            prod.simplify();
            return prod;
        }

        Fraction divide(Fraction f){
            Fraction quot;
            if(f.num != 0){
                quot.num = this->num * f.den;
                quot.den = this->den * f.num;
            }
            quot.simplify();
            return quot;
        }

        void simplify(){
            if(this->den < 0){
                this->den *= -1;
                this->num *= -1;
            }
            int gcdN = __gcd(this->num, this->den);
            this->num /= gcdN;
            this->den /= gcdN;
        }

        void output(){
            if(this->den == 1){
                cout << this->num << endl;
            }else{
                cout << this->num << "/" << this->den << endl;
            }
        }
};

int main(){
    Fraction fractionA, fractionB, result;
    int choice;
    cin >> choice;
    switch(choice){
        case 1:
            fractionA.input();
            fractionB.input();
            result = fractionA.add(fractionB);
            result.output();
            break;
        case 2:
            fractionA.input();
            fractionB.input();
            result = fractionA.subtract(fractionB);
            result.output();
            break;
        case 3:
            fractionA.input();
            fractionB.input();
            result = fractionA.multiply(fractionB);
            result.output();
            break;
        case 4:
            fractionA.input();
            fractionB.input();
            result = fractionA.divide(fractionB);
            result.output();
            break;
        case 5:
            fractionA.input();
            fractionA.simplify();
            fractionA.output();
            break;
        default:
            cout << "Invalid input!" << endl;
            break;
    }
}