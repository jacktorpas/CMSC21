#include <stdio.h>
#include <stdlib.h>

typedef struct Date{
    int yr, mth, day;
} Date;

int checkFortune(int);
void getLine(FILE*, int[]);
int checkZodiacSign(Date);
void printZodiacSign(int);
void printFortune(FILE*, int, int, int[]);

int main(){
    Date dt;
    int zodiacSign;
    int line[60], repeat;
    FILE* fp1 = fopen("data.for", "rb");
    FILE* fp2 = fopen("data.in", "ab");
    if(fp1 == NULL){
        printf("Couldn't open data.for\n");
        exit(-1);
    }
    if(fp2 == NULL){
        printf("Couldn't open data.in\n");
        exit(-1);
    }
    do{
        printf("Enter the date: ");
        scanf("%i %i %i", &dt.yr, &dt.mth, &dt.day);
    }while(dt.mth < 1 || dt.mth > 12 || dt.day < 1 || dt.day > 31);

    zodiacSign = checkZodiacSign(dt);
    fprintf(fp2, "%i-%02i-%02i\n", dt.yr, dt.mth, dt.day);
    fclose(fp2);
    printZodiacSign(zodiacSign);
    getLine(fp1, line);
    repeat = checkFortune(zodiacSign);
    rewind(fp1);
    printFortune(fp1, zodiacSign, repeat, line);
    fclose(fp1);
    return 0;
}

int checkFortune(int zodiac){
    FILE* fp = fopen("data.in", "rb");
    Date dt2;
    int repeat = 0; //default is 0
    char deet[12], month[3], day[3];

    while(fscanf(fp, "%s", deet) != EOF){
        dt2.yr = atoi(deet);
        month[0] = deet[5]; month[1] = deet[6]; month[2] = '\0';
        day[0] = deet[8]; day[1] = deet[9]; day[2] = '\0';
        dt2.mth = atoi(month);
        dt2.day = atoi(day);
        if(checkZodiacSign(dt2) == zodiac){
            repeat++;
        }
    }
    fclose(fp);
    return repeat;
}

void getLine(FILE *fp, int line[]){
    char temp;
    int charN = 0;
    for(int i = 0; i < 60; i++){
        while(1){
            temp = fgetc(fp);
            charN++;
            if(temp == '\n' || temp == EOF){
                line[i] = charN;
                charN = 0;
                break;
            }
        }
    }
}

int checkZodiacSign(Date dt){ //0 for Aquarius, 1 for Pisces, ..., 11 for Capricorn
    switch(dt.mth){
        case 1:
            if(dt.day <= 19) return 11;
            else return 0;
            break;
        case 2:
            if(dt.day <= 18) return 0;
            else return 1;
            break;
        case 3:
            if(dt.day <= 20) return 1;
            else return 2;
            break;
        case 4:
            if(dt.day <= 19) return 2;
            else return 3;
            break;
        case 5:
            if(dt.day <= 20) return 3;
            else return 4;
            break;
        case 6:
            if(dt.day <= 20) return 4;
            else return 5;
            break;
        case 7:
            if(dt.day <= 22) return 5;
            else return 6;
            break;
        case 8:
            if(dt.day <= 22) return 6;
            else return 7;
            break;
        case 9:
            if(dt.day <= 22) return 7;
            else return 8;
            break;
        case 10:
            if(dt.day <= 22) return 8;
            else return 9;
            break;
        case 11:
            if(dt.day <= 21) return 9;
            else return 10;
            break;
        case 12:
            if(dt.day <= 21) return 10;
            else return 11;
            break;
    }
}

void printZodiacSign(int zodiac){
    printf("\n");
    switch(zodiac){
        case 0:
            printf("Aquarius: ");
            break;
        case 1:
            printf("Pisces: ");
            break;
        case 2:
            printf("Aries: ");
            break;
        case 3:
            printf("Taurus: ");
            break;
        case 4:
            printf("Gemini: ");
            break;
        case 5:
            printf("Cancer: ");
            break;
        case 6:
            printf("Leo: ");
            break;
        case 7:
            printf("Virgo: ");
            break;
        case 8:
            printf("Libra: ");
            break;
        case 9:
            printf("Scorpio: ");
            break;
        case 10:
            printf("Sagittarius: ");
            break;
        case 11:
            printf("Capricorn: ");
            break;
    }
}

void printFortune(FILE* fp, int zodiac, int repeat, int line[]){
    int seek = 0;
    int lineToPrint = zodiac; //same line as the zodiac, but if there is repeat, add it by 12
    
    if(repeat > 1){
        for(int i = 0; i < repeat - 1; i++){
            lineToPrint += 12;
        }
    }

    if(lineToPrint > 59){
        printf("Sorry, we've run out of fortunes today :(\n");
        return;
    }else{
        for(int i = 0; i < lineToPrint; i++){
            seek += line[i];
        }
        char *st = malloc((line[lineToPrint] + 1));
        fseek(fp, seek, SEEK_SET);
        fgets(st, line[lineToPrint], fp);
        puts(st);
    }
}



