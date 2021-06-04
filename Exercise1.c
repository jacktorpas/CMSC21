#include <stdio.h>
#include <stdlib.h>

int dayOfYear(int, int, int);
int leapYear(int);
int gaussMethod(int);
int weekDay(int, int);

int main(){
    int yr, mth, day;

    do{
        printf("Enter the year, month, and day:\n");
        scanf("%i %i %i", &yr, &mth, &day);
    }while(mth <= 0 || mth > 12 || day <= 0 || day > 31);
    
    int lpYr = leapYear(yr);
    if(mth == 2){
        if((lpYr == 0 && day > 28) || (lpYr == 1 && day > 29)){
            printf("This date does not exist");
            exit(0);
        }
    }else if(mth == 4 || mth == 6 || mth == 9 || mth == 11){
        if(day > 30){
            printf("This date does not exist");
            exit(0);
        }
    }
    int nthDay = dayOfYear(lpYr, mth, day);
    int wkDay = weekDay(yr, nthDay);

    switch(wkDay){
        case 0:
            printf("Sunday, ");
            break;
        case 1:
            printf("Monday, ");
            break;
        case 2:
            printf("Tuesday, ");
            break;
        case 3:
            printf("Wednesday, ");
            break;
        case 4:
            printf("Thursday, ");
            break;
        case 5:
            printf("Friday, ");
            break;
        default:
            printf("Saturday, ");
            break;
    }

    if(nthDay % 100 == 11 || nthDay % 100 == 12 || nthDay % 100 == 13){
        printf("%ith day of the year", nthDay);
    }else if(nthDay % 10 == 1 || nthDay == 1){
        printf("%ist day of the year", nthDay);
    }else if(nthDay % 10 == 2 || nthDay == 2){
        printf("%ind day of the year", nthDay);
    }else if(nthDay % 10 == 3 || nthDay == 3){
        printf("%ird day of the year", nthDay);
    }else{
        printf("%ith day of the year", nthDay);
    }
    return 0;
}

int leapYear(int yr){ //to determine if it's a leap year
    int leapFlag = 0;
    if(yr % 4 == 0){
        if(yr % 100 == 0){
            if(yr % 400 == 0){
                leapFlag = 1;
            }
        }else{
            leapFlag = 1;
        }
    }
    return leapFlag;
}

int dayOfYear(int lp, int mth, int day){ //calculate the nth day of the year
    int nthday = day;
    if(mth != 1){
        int mthCount = mth - 1;
        for( ; mthCount > 0; mthCount--){
            if(mthCount == 2){
                if(lp == 1){
                    nthday += 29;
                }else{
                    nthday += 28;
                }
            }else if(mthCount == 4 || mthCount == 6 || mthCount == 9 || mthCount == 11){
                nthday += 30;
            }else{
                nthday += 31;
            }
        }
    }
    return nthday;
}

int gaussMethod(int yr){ //calculate week day of January 1 given a year
    //R(1 + 5R(A-1, 4) + 4R(A-1, 100) + 6R(A-1, 400), 7)
    int weekDayJan1 = (1 + 5 * ((yr - 1) % 4) + 4 * ((yr - 1) % 100) + 6 * ((yr - 1) % 400)) % 7;
    return weekDayJan1;
}

int weekDay(int yr, int day){ //calculate week day of any day of year
    int firstWeekDay = gaussMethod(yr);
    int i;
    int j = firstWeekDay;

    for(i = 0; i < day - 1; i++){
        if(j == 6){
            j = 0;
        }else{
            j++;
        }
    }
    return j;
}


