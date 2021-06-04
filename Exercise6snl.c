#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct Player{
    char token;
    char square[100];
    int progress;
} Player;

typedef struct Snake{
    char label;
    int square[3];
} Snake;

typedef struct Ladder{
    char label;
    int square[3];
} Ladder;

Snake s0, sf;
Ladder l0, lf;

int dieroll = 0;
int snl = 0;
char sSquare[100], lSquare[100];
bool playerWon = false;

//initialization functions
Player p1Init(Player p1){
    p1.token = 'a';
    *p1.square = p1.token;
    for(int i = 1; i < 100; i++){
        *(p1.square + i) = '\40';
    }
    p1.progress = 0;
    return p1;
}

Player p2Init(Player p2){
    p2.token = 'b';
    *p2.square = p2.token;
    for(int i = 1; i < 100; i++){
        *(p2.square + i) = '\40';
    }
    p2.progress = 0;
    return p2;
}

Player p3Init(Player p3){
    p3.token = 'c';
    *p3.square = p3.token;
    for(int i = 1; i < 100; i++){
        *(p3.square + i) = '\40';
    }
    p3.progress = 0;
    return p3;
}

Player p4Init(Player p4){
    p4.token = 'd';
    *p4.square = p4.token;
    for(int i = 1; i < 100; i++){
        *(p4.square + i) = '\40';
    }
    p4.progress = 0;
    return p4;
}

void boardInit(){
    for(int i = 0; i < 100; i++){
        *(lSquare + i) = '\40';
        *(sSquare + i) = '\40';
    }
    *(lSquare + 99) = '#';
    *(sSquare + 99) = '\40';
}

void snlInit(){
    s0.label = 'S';
    sf.label = 's';
    l0.label = 'L';
    lf.label = 'l';
    *s0.square = rand() % 29 + 1;
    do{
        *l0.square = rand() % 29 + 1;
    }while(*l0.square == *s0.square);
    do{
        *sf.square = rand() % 29 + 1;
        *lf.square = rand() % 29 + 1;
    }while(*sf.square >= *s0.square || *lf.square <= *l0.square + 10 || *l0.square == *sf.square ||
        *s0.square == *lf.square);
    for(int i = 1; i <= 2; i++){
        do{
            *(s0.square + i) = rand() % (98 - 30 + 1) + 30;
            *(l0.square + i) = rand() % (98 - 30 + 1) + 30;
        }while(*(s0.square + i - 1) == *(s0.square + i) || *(l0.square + i - 1) == *(l0.square + i) ||
            *(s0.square + i) == *(l0.square + i));
        do{
            *(sf.square + i) = rand() % (98 - 30 + 1) + 30;
            *(lf.square + i) = rand() % (98 - 30 + 1) + 30;
        }while(*(sf.square + i - 1) == *(sf.square + i) || *(lf.square + i - 1) == *(lf.square + i) ||
            *(sf.square + i) >= *(s0.square + i)|| *(lf.square + i) <= *(l0.square + i) ||
            *(sf.square + i) == *(lf.square + i) || *(s0.square + i) == *(lf.square + i) || 
            *(l0.square + i) == *(sf.square + i));
    }
    //printing the S and Ls
    for(int i = 0; i < 3; i++){
        *(sSquare + *(s0.square + i)) = s0.label;
        *(sSquare + *(sf.square + i)) = sf.label;
        *(lSquare + *(l0.square + i)) = l0.label;
        *(lSquare + *(lf.square + i)) = lf.label;
    }
}

void snlBoard(Player *p1, Player *p2, Player *p3, Player *p4, int turn){
    int row = 1;
    for(int i = 99; i >= 0; i -= 10){
        printf("+----+----+----+----+----+----+----+----+----+----+\n");
        if(row % 2 != 0){
            for(int j = 0; j < 10; j++){
                printf("|%c  %c", *(lSquare + i - j), *(sSquare + i - j));
            }
            printf("|\n");
            for(int k = 0; k < 10; k++){
                printf("|%c%c%c%c", *(p1->square + i - k), *(p2->square + i - k), *(p3->square + i - k),
                    *(p4->square + i - k));
            }
            printf("|\n");
        }else{
            for(int j = 9; j >= 0; j--){
                printf("|%c  %c", *(lSquare + i - j), *(sSquare + i - j));
            }
            printf("|\n");
            for(int k = 9; k >= 0; k--){
                printf("|%c%c%c%c", *(p1->square + i - k), *(p2->square + i - k), *(p3->square + i - k),
                    *(p4->square + i - k));
            }
            printf("|\n");
        }
        row++;
    }
    printf("+----+----+----+----+----+----+----+----+----+----+\n\n");
    if(playerWon == true){
        if(p1->progress == 99){
            printf("a rolls a %i!\n", dieroll);
            printf("a is the winner!\n");
        }else if(p2->progress == 99){
            printf("b rolls a %i!\n", dieroll);
            printf("b is the winner!\n");
        }else if(p3->progress == 99){
            printf("c rolls a %i!\n", dieroll);
            printf("c is the winner!\n");
        }else{
            printf("d rolls a %i!\n", dieroll);
            printf("d is the winner!\n");
        }
    }else{
        if(dieroll > 0){
            switch(turn){
                case 2:
                    printf("a rolls a %i!\n", dieroll);
                    if(snl == 1){
                        printf("a lands on a ladder and goes up!\n");
                    }else if(snl == 2){
                        printf("a lands on a snake and goes down!\n");
                    }
                    break;
                case 3:
                    printf("b rolls a %i!\n", dieroll);
                    if(snl == 1){
                        printf("b lands on a ladder and goes up!\n");
                    }else if(snl == 2){
                        printf("b lands on a snake and goes down!\n");
                    }
                    break;
                case 4:
                    printf("c rolls a %i!\n", dieroll);
                    if(snl == 1){
                        printf("c lands on a ladder and goes up!\n");
                    }else if(snl == 2){
                        printf("c lands on a snake and goes down!\n");
                    }
                    break;
                case 1:
                    printf("d rolls a %i!\n", dieroll);
                    if(snl == 1){
                        printf("d lands on a ladder and goes up!\n");
                    }else if(snl == 2){
                        printf("d lands on a snake and goes down!\n");
                    }
                    break;
            }
        }   
        switch(turn){
            case 1:
                printf("a's turn.\n");
                printf("a, press ENTER to roll.\n\n");
                break;
            case 2:
                printf("b's turn.\n");
                printf("b, press ENTER to roll.\n\n");
                break;
            case 3:
                printf("c's turn.\n");
                printf("c, press ENTER to roll.\n\n");
                break;
            case 4:
                printf("d's turn.\n");
                printf("d, press ENTER to roll.\n\n");
                break;
        }
    }
}

void makeTheMove(Player *p1, Player *p2, Player *p3, Player *p4, int turn){
    dieroll = rand() % 6 + 1;
    getchar();
    switch(turn){
        case 1:
            *(p1->square + p1->progress) = '\40';
            p1->progress += dieroll;
            if(p1->progress > 99){
                p1->progress -= dieroll; //don't move if roll exceeds 100
            }
            *(p1->square + p1->progress) = p1->token;
            break;
        case 2:
            *(p2->square + p2->progress) = '\40';
            p2->progress += dieroll;
            if(p2->progress > 99){
                p2->progress -= dieroll;
            }
            *(p2->square + p2->progress) = p2->token;
            break;
        case 3:
            *(p3->square + p3->progress) = '\40';
            p3->progress += dieroll;
            if(p3->progress > 99){
                p3->progress -= dieroll;
            }
            *(p3->square + p3->progress) = p3->token;
            break;
        case 4:
            *(p4->square + p4->progress) = '\40';
            p4->progress += dieroll;
            if(p4->progress > 99){
                p4->progress -= dieroll;
            }
            *(p4->square + p4->progress) = p4->token;
            break;
    }
    for(int i = 0; i < 3; i++){ //determines if a player has landed on a snake or ladder
        if(turn == 1){
            if(p1->progress == *(l0.square + i)){ //land on ladder
                *(p1->square + p1->progress) = '\40';
                p1->progress += (*(lf.square + i) - *(l0.square + i));
                *(p1->square + p1->progress) = p1->token;
                snl = 1;
                break;
            }else if(p1->progress == *(s0.square + i)){ //land on snake
                *(p1->square + p1->progress) = '\40';
                p1->progress -= (*(s0.square + i) - *(sf.square + i));
                *(p1->square + p1->progress) = p1->token;
                snl = 2;
                break;
            }
        }else if(turn == 2){
            if(p2->progress == *(l0.square + i)){
                *(p2->square + p2->progress) = '\40';
                p2->progress += (*(lf.square + i) - *(l0.square + i));
                *(p2->square + p2->progress) = p2->token;
                snl = 1;
                break;
            }else if(p2->progress == *(s0.square + i)){
                *(p2->square + p2->progress) = '\40';
                p2->progress -= (*(s0.square + i) - *(sf.square + i));
                *(p2->square + p2->progress) = p2->token;
                snl = 2;
                break;
            }
        }else if(turn == 3){
            if(p3->progress == *(l0.square + i)){
                *(p3->square + p3->progress) = '\40';
                p3->progress += (*(lf.square + i) - *(l0.square + i));
                *(p3->square + p3->progress) = p3->token;
                snl = 1;
                break;
            }else if(p3->progress == *(s0.square + i)){
                *(p3->square + p3->progress) = '\40';
                p3->progress -= (*(s0.square + i) - *(sf.square + i));
                *(p3->square + p3->progress) = p3->token;
                snl = 2;
                break;
            }
        }else{
            if(p4->progress == *(l0.square + i)){
                *(p4->square + p4->progress) = '\40';
                p4->progress += (*(lf.square + i) - *(l0.square + i));
                *(p4->square + p4->progress) = p4->token;
                snl = 1;
                break;
            }else if(p4->progress == *(s0.square + i)){
                *(p4->square + p4->progress) = '\40';
                p4->progress -= (*(s0.square + i) - *(sf.square + i));
                *(p4->square + p4->progress) = p4->token;
                snl = 2;
                break;
            }
        }
    }
}

int main(){
    int turn = 1;
    Player p1 = p1Init(p1); Player p2 = p2Init(p2);
    Player p3 = p3Init(p3); Player p4 = p4Init(p4);
    Player* a = &p1; Player* b = &p2; Player* c = &p3; Player* d = &p4;
    srand((unsigned int)time(NULL));
    boardInit();
    snlInit();
    while(a->progress != 99 || b->progress != 99 || c->progress != 99 || d->progress != 99){
        snlBoard(a, b, c, d, turn);
        snl = 0;
        makeTheMove(a, b, c, d, turn);
        while(dieroll== 6){ //if a player rolls a 6, they roll again until they don't roll a 6
            if(a->progress >= 99 || b->progress >= 99 || c->progress >= 99 || d->progress >= 99){
                break;
            }
            printf("Oh, a six is rolled! Press ENTER to roll again.\n");
            makeTheMove(a, b, c, d, turn);
        }
        if(a->progress >= 99 || b->progress >= 99 || c->progress >= 99 || d->progress >= 99){
            break;
        }
        if(turn == 4){ turn = 1; } else { turn++; }
    }
    playerWon = true;
    snlBoard(a, b, c, d, turn);
    return 0;
}











