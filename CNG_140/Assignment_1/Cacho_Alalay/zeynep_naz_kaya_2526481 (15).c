//Zeynep Naz Kaya 2526481
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LF 10

int roll_a_dice();
int play_computer(int, int);
int play_user(int, int);
void scoreSheet();
int checkUnFull(int, int, int, int, int);
int checkPoker(int, int, int, int, int);
int checkSixes(int, int, int, int, int);
int checkFives(int, int, int, int, int);
int checkFours(int, int, int, int, int);
int checkThrees(int, int, int, int, int);
int checkTwos(int, int, int, int, int);
int checkOnes(int, int, int, int, int);

int main() {

    srand(time(NULL));
    int equality=0;
    printf("Welcome to the Cacho Alalay game.\n");
    printf("Let's get started!\n");

    //This do-while loop is for break the tie round if the score of the user and the computer are equal at the end of the game.
    do{
        int roundnumber, start_user, start_computer;
        printf("\nHow many rounds would you like to play?");
        scanf("%d",&roundnumber);

        start_computer = roll_a_dice();
        printf("\nI have rolled the dice and got %d!\n",start_computer);

        start_user = roll_a_dice();
        printf("I have rolled the dice for you and you got %d!\n",start_user);

        //if dices are equal, while loop will run until equality is broken
        while (start_computer == start_user) {

            printf("\nRerolling again!\n");

            start_computer = roll_a_dice();
            printf("\nI have rolled the dice and got %d!\n",start_computer);

            start_user = roll_a_dice();
            printf("I have rolled the dice for you and you got %d!\n",start_user);
        }


        int computer =0, user =0; //scores are initially zero for both computer and user

        //if computer's dice is bigger than user, computer will start
        if (start_computer > start_user) {
            printf("\nI go first!\n");
            for (int i = 1; i <= roundnumber; i++) {
                printf("\nRound %d --- Computer:", i);
                printf("\n---------------------");

                computer = play_computer(computer,roundnumber);//I want to update score so I write "computer" inside the function

                printf("\n\nRound %d --- Player:", i);
                printf("\n---------------------");

                user = play_user(user, roundnumber); //updateing score
                printf("\n");
                scoreSheet(computer, user, roundnumber, i);
            }
        }

        //if user's dice is bigger than computer, user will start
        else if (start_user > start_computer) {
            printf("\nYou go first!\n");
            for (int i = 1; i <= roundnumber; i++) {
                printf("\nRound %d --- Player:", i);
                printf("\n---------------------");
                printf("\nGet ready to play!");
                printf("\nI rolled dices for you and you got");

                user = play_user(user, roundnumber);

                printf("\n\nRound %d --- Computer:", i);
                printf("\n---------------------");

                computer = play_computer(computer, roundnumber);
                printf("\n");
                scoreSheet(computer, user, roundnumber, i);
            }
        }

        printf("\n");

        //checking who wins the game
        if (user > computer) {
            printf("\nPLAYER WINS!");
            equality=0;
        } else if (computer > user) {
            printf("\nCOMPUTER WINS!");
            equality=0;
        } else {
            printf("\nEQUAL!");
            equality=1;
        }

    }while(equality!=0);

    return 0;
}


//this function generates random number between 1 and 6
int roll_a_dice() {

    int randomnumber;
    randomnumber = 1 + rand() % 6;
    return randomnumber;
}


//"computer" means score of computer.
int play_computer(int computer, int roundnumber){

    int score, loop=1;
    int keepD1=0, keepD2=0, keepD3=0, keepD4=0, keepD5=0;
    int check5=0, check4=0, check3=0, check2=0, checkAll=0;
    //this checks help me to control dices. For example, if 4 dices come same value, check4 helps me to control and giving error.
    //For example check3 can help me to control dices when 3 dices come same value.

    //while condition is: When I have no dices to roll ,and after 3 times roll LOOP will stop. (I used same loop for play_user function)
    while((keepD1<1 || keepD2<1 ||keepD3<1 || keepD4<1 || keepD5<1) && (loop<=3)) {

        int DICE1, DICE2, DICE3, DICE4, DICE5;
        int count =0;
        count++;
        check5=0, check4=0, check3=0, check2=0, checkAll=0;
        score=0;

        printf("\n");
        printf("I got ->");
        if(keepD1==0){
            DICE1= roll_a_dice();
            printf("[Dice 1]: %d ",DICE1);
        }
        if(keepD2==0){
            DICE2= roll_a_dice();
            printf("[Dice 2]: %d ",DICE2);
        }
        if(keepD3==0){
            DICE3= roll_a_dice();
            printf("[Dice 3]: %d ",DICE3);
        }
        if(keepD4==0){
            DICE4= roll_a_dice();
            printf("[Dice 4]: %d ",DICE4);
        }
        if(keepD5==0){
            DICE5= roll_a_dice();
            printf("[Dice 5]: %d ",DICE5);
        }


        //if all dices are equal I print Grande
        if (DICE1 == DICE2 && DICE1 == DICE3 && DICE1 == DICE4 && DICE1 == DICE5) {
            printf("\nI got Grande!");
            score= 50;
        }

        //checking poker condition. For this, I wrote new function.
        else if (checkPoker(DICE1, DICE2, DICE3, DICE4, DICE5) == 1) {
            printf("\nI got Poker!");
            if (count == 1) {
                score= 45;  //first round score
            } else {
                score= 40; //NOT first round score (TWO OR THREE..)
            }
        }

        //checking Un Full condition. For this, I wrote new function.
        else if (checkUnFull(DICE1, DICE2, DICE3, DICE4, DICE5) == 1) {
            printf("\nI got Un Full!");
            if (count == 1) {
                score= 35; //first round score
            } else {
                score= 30; //NOT first round score (TWO OR THREE..)
            }
        }

        //checking Escalera condition.
        else if (DICE1 == 1 && DICE2 == 2 && DICE3 == 3 && DICE4 == 4 && DICE5 == 5) {
            printf("\nI got Escalera!");
            printf("\nI am keeping dice 1, 2, 3, 4, and 5!");
            if (count == 1) {
                score= 25; //first round score
            } else {
                score= 20; //NOT first round score (TWO OR THREE)
            }
        } else if (DICE1 == 2 && DICE2 == 3 && DICE3 == 4 && DICE4 == 5 && DICE5 == 6) {
            printf("\nI got Escalera!");
            printf("\nI am keeping dice 1, 2, 3, 4, and 5!");
            if (count == 1) {
                score= 25;
            } else {
                score= 20;
            }
        }

        //checking Sixes, Fives, Fours, Threes, Twos, Ones conditions. For these, I wrote new functions.
        else if (checkSixes(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkSixes(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkFives(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkFives(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkFours(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkFours(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkThrees(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkThrees(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkTwos(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkTwos(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkOnes(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkOnes(DICE1, DICE2, DICE3, DICE4, DICE5);
        }


        //All the if statements at the bottom are related to which of the dice rolls are the same
        //5 dices are same
        if (DICE1 == DICE2 && DICE1== DICE3 && DICE1== DICE4 && DICE1== DICE5 && check5==0 && checkAll==0) {
            keepD1++;
            keepD2++;
            keepD3++;
            keepD4++;
            keepD5++;
            printf("\nI am keeping all dices!");
            check5=1;
            checkAll=1;
        }

        //4 dices are same
        if (DICE1 == DICE2  && DICE1== DICE3 && DICE1== DICE4 && check4==0 && checkAll==0) {
            keepD1++;
            keepD2++;
            keepD3++;
            keepD4++;
            printf("\nI am keeping dice 1,2,3 and 4!");
            check4=1;
            checkAll=1;

        }
        if (DICE1 == DICE2 && DICE1 == DICE3 && DICE1 == DICE5 && check4==0 && checkAll==0) {
            keepD1++;
            keepD2++;
            keepD3++;
            keepD5++;
            printf("\nI am keeping dice 1,2,3 and 5!");
            check4=1;
            checkAll=1;

        }
        if (DICE1 == DICE2 && DICE1 == DICE4 && DICE1 == DICE5 && check4==0 && checkAll==0) {
            keepD1++;
            keepD2++;
            keepD4++;
            keepD5++;
            printf("\nI am keeping dice 1,2,4 and 5!");
            check4=1;
            checkAll=1;
        }
        if (DICE1 == DICE3 && DICE1 == DICE4 && DICE1 == DICE5 && check4==0 && checkAll==0) {
            keepD1++;
            keepD3++;
            keepD4++;
            keepD5++;
            printf("\nI am keeping dice 1,3,4 and 5!");
            check4=1;
            checkAll=1;
        }
        if (DICE2 == DICE3 && DICE2 == DICE4 && DICE2== DICE5 && check4==0 && checkAll==0) {
            keepD2++;
            keepD3++;
            keepD4++;
            keepD5++;
            printf("\nI am keeping dice 2,3,4 and 5!");
            check4=1;
            checkAll=1;
        }

        //three dices are same
        if (DICE1 == DICE2 && DICE1 == DICE3 && check3==0 && checkAll==0){
            keepD1++;
            keepD2++;
            keepD3++;
            printf("\nI am keeping dice 1,2 and 3!");
            check3=1;
            checkAll=1;
        }
        if (DICE1 == DICE2 && DICE1 == DICE4 && check3==0 && checkAll==0){
            keepD1++;
            keepD2++;
            keepD4++;
            printf("\nI am keeping dice 1,2 and 4!");
            check3=1;
            checkAll=1;
        }
        if (DICE1 == DICE2 && DICE1 == DICE5 && check3==0 && checkAll==0){
            keepD1++;
            keepD2++;
            keepD5++;
            printf("\nI am keeping dice 1,2 and 5!");
            check3=1;
            checkAll=1;
        }
        if (DICE1 == DICE3 && DICE1 == DICE4 && check3==0 && checkAll==0){
            keepD1++;
            keepD3++;
            keepD4++;
            printf("\nI am keeping dice 1,3 and 4!");
            check3=1;
            checkAll=1;
        }
        if (DICE1 == DICE3 && DICE1 == DICE5 && check3==0 && checkAll==0){
            keepD1++;
            keepD3++;
            keepD5++;
            printf("\nI am keeping dice 1,3 and 5!");
            check3=1;
            checkAll=1;
        }
        if (DICE1 == DICE4 && DICE1 == DICE5 && check3==0 && checkAll==0){
            keepD1++;
            keepD4++;
            keepD5++;
            printf("\nI am keeping dice 1,4 and 5!");
            check3=1;
            checkAll=1;
        }
        if (DICE2 == DICE3 && DICE2 == DICE4 && check3==0 && checkAll==0){
            keepD2++;
            keepD3++;
            keepD4++;
            printf("\nI am keeping dice 2,3 and 4!");
            check3=1;
            checkAll=1;
        }
        if (DICE2 == DICE3 && DICE2 == DICE5 && check3==0 && checkAll==0){
            keepD2++;
            keepD3++;
            keepD5++;
            printf("\nI am keeping dice 2,3 and 5!");
            check3=1;
            checkAll=1;
        }
        if (DICE2 == DICE4 && DICE2 == DICE5 && check3==0 && checkAll==0){
            keepD2++;
            keepD4++;
            keepD5++;
            printf("\nI am keeping dice 2,4 and 5!");
            check3=1;
            checkAll=1;
        }
        if (DICE3 == DICE4 && DICE3 == DICE5 && check3==0 && checkAll==0){
            keepD3++;
            keepD4++;
            keepD5++;
            printf("\nI am keeping dice 3,4 and 5!");
            check3=1;
            checkAll=1;
        }

        //two dices are same
        if (DICE1 == DICE2 && check2==0 && checkAll==0) {
            keepD1++;
            keepD2++;
            printf("\nI am keeping dice 1 and 2!");
            check2=1;
            checkAll=1;
        }
        if (DICE1 == DICE3 && check2==0 && checkAll==0) {
            keepD1++;
            keepD3++;
            printf("\nI am keeping dice 1 and 3!");
            check2=1;
            checkAll=1;
        }
        if (DICE1 == DICE4 && check2==0 && checkAll==0) {
            keepD1++;
            keepD4++;
            printf("\nI am keeping dice 1 and 4!");
            check2=1;
            checkAll=1;
        }
        if (DICE1 == DICE5 && check2==0 && checkAll==0) {
            keepD1++;
            keepD5++;
            printf("\nI am keeping dice 1 and 5!");
            check2=1;
            checkAll=1;
        }
        if (DICE2 == DICE3 && check2==0 && checkAll==0) {
            keepD2++;
            keepD3++;
            printf("\nI am keeping dice 2 and 3!");
            check2=1;
            checkAll=1;
        }
        if (DICE2 == DICE4 && check2==0 && checkAll==0) {
            keepD2++;
            keepD4++;
            printf("\nI am keeping dice 2 and 4!");
            check2=1;
            checkAll=1;
        }
        if (DICE2 == DICE5 && check2==0 && checkAll==0) {
            keepD2++;
            keepD5++;
            printf("\nI am keeping dice 2 and 5!");
            check2=1;
            checkAll=1;
        }
        if (DICE3 == DICE4 && check2==0 && checkAll==0) {
            keepD3++;
            keepD4++;
            printf("\nI am keeping dice 3 and 4!");
            check2=1;
            checkAll=1;
        }
        if (DICE3 == DICE5 && check2==0 && checkAll==0) {
            keepD3++;
            keepD5++;
            printf("\nI am keeping dice 3 and 5!");
            check2=1;
            checkAll=1;
        }
        if (DICE4 == DICE5 && check2==0 && checkAll==0) {
            keepD4++;
            keepD5++;
            printf("\nI am keeping dice 4 and 5!");
            check2=1;
            checkAll=1;
        }
        loop++;
    }
    computer=computer +score;
    printf("\nMy score: %d, Total score: %d",score,computer);
    return score;
}


//"user" means score of user.
int play_user(int user, int roundnumber){

    int score, loop=1;
    int keepD1=0, keepD2=0, keepD3=0, keepD4=0, keepD5=0;
    int count =0;

    while((keepD1<1 || keepD2<1 ||keepD3<1 || keepD4<1 || keepD5<1) && (loop<=3)){

        score=0;
        count++;
        int DICE1, DICE2, DICE3, DICE4, DICE5;
        printf("\nI rolled the remaining and you got:");
        printf("\n->");
        //if keepDices are zero, it means I don't want to keep it, so this part makes me to reroll unwanted dices.
        if(keepD1==0){
            DICE1= roll_a_dice();
            printf("[Dice 1]: %d ",DICE1);
        }
        if(keepD2==0){
            DICE2= roll_a_dice();
            printf("[Dice 2]: %d ",DICE2);
        }
        if(keepD3==0){
            DICE3= roll_a_dice();
            printf("[Dice 3]: %d ",DICE3);
        }
        if(keepD4==0){
            DICE4= roll_a_dice();
            printf("[Dice 4]: %d ",DICE4);
        }
        if(keepD5==0){
            DICE5= roll_a_dice();
            printf("[Dice 5]: %d ",DICE5);
        }


        //if all dices are equal I print Grande
        if (DICE1 == DICE2 && DICE1== DICE3 && DICE1== DICE4 && DICE1== DICE5) {
            printf("\nI got Grande!");
            score= 50;
        }

        //checking poker condition. For this, I wrote new function.
        else if (checkPoker(DICE1, DICE2, DICE3, DICE4, DICE5) == 1) {
            printf("\nI got Poker!");
            if (count == 1) {
                score= 45;  //first round score
            } else {
                score= 40;  //NOT first round score (TWO OR THREE..)
            }
        }

        //checking Un Full condition. For this, I wrote new function.
        else if (checkUnFull(DICE1, DICE2, DICE3, DICE4, DICE5) == 1) {
            printf("\nI got Un Full!");
            if (count == 1) {
                score= 35; //first round score
            } else {
                score= 30; //NOT first round score (TWO OR THREE..)
            }
        }

        //checking Escalera condition.
        else if (DICE1 == 1 && DICE2 == 2 && DICE3 == 3 && DICE4 == 4 && DICE5 == 5) {
            printf("\nI got Escalera!");
            if (count == 1) {
                score= 25; //first round score
            } else {
                score= 20; //NOT first round score (TWO OR THREE)
            }
        } else if (DICE1 == 2 && DICE2 == 3 && DICE3 == 4 && DICE4 == 5 && DICE5 == 6) {
            printf("\nI got Escalera!");
            if (count == 1) {
                score= 25;
            } else {
                score= 20;
            }
        }

        //checking Sixes, Fives, Fours, Threes, Twos, Ones conditions. For these, I wrote new functions.
        else if (checkSixes(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkSixes(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkFives(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkFives(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkFours(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkFours(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkThrees(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkThrees(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkTwos(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkTwos(DICE1, DICE2, DICE3, DICE4, DICE5);
        }
        else if (checkOnes(DICE1, DICE2, DICE3, DICE4, DICE5) > 0) {
            score= checkOnes(DICE1, DICE2, DICE3, DICE4, DICE5);
        }

        //with invalid input I am checking conditions
        int inputvalid=0;
        do {
            //Reading input till end of line
            char selection;
            printf("\nWhich ones do you want to keep?");
            scanf(" %c", &selection);

            while (selection != LF) {

                if (selection == '0') {
                    printf("Rerolling remaining dices again!\n");
                }
                if (selection == '1') {
                    keepD1++;
                }
                if (selection == '2') {
                    keepD2++;
                }
                if (selection == '3') {
                    keepD3++;
                }
                if (selection == '4') {
                    keepD4++;
                }
                if (selection == '5') {
                    keepD5++;
                }

                scanf("%c", &selection);
                inputvalid=1;
                //after ask user again
                if (keepD1 > 1) {
                    printf("\nYou have already excluded Dice 1! Please re-try\n");
                    inputvalid=0;
                    //I am decreasing keepD values, because when I don't decrease them, they always printed error, so I find a solution like this.
                    keepD1--;
                }
                if (keepD2 > 1) {
                    printf("\nYou have already excluded Dice 2! Please re-try\n");
                    inputvalid=0;
                    keepD2--;
                }
                if (keepD3 > 1) {
                    printf("\nYou have already excluded Dice 3! Please re-try\n");
                    inputvalid=0;
                    keepD3--;
                }
                if (keepD4 > 1) {
                    printf("\nYou have already excluded Dice 4! Please re-try\n");
                    inputvalid=0;
                    keepD4--;
                }
                if (keepD5 > 1) {
                    printf("\nYou have already excluded Dice 5! Please re-try\n");
                    inputvalid=0;
                    keepD5--;
                }
            }
        }while(inputvalid==0); //this do-while loop is control the error part

        printf("Current round score:%d",score);
        loop++;
    }
    user= user+ score;
    printf("\nYour score: %d, Total score: %d",score,user);
    return score;
}


int checkUnFull(int DICE1, int DICE2, int DICE3, int DICE4, int DICE5){

    int countOne=0, countTwo=0, countThree=0, countFour=0, countFive=0, countSix=0;

    if(DICE1==1){
        countOne++;
    }
    else if(DICE1==2){
        countTwo++;
    }
    else if(DICE1==3){
        countThree++;
    }
    else if(DICE1==4){
        countFour++;
    }
    else if(DICE1==5){
        countFive++;
    }
    else if(DICE1==6){
        countSix++;
    }


    if(DICE2==1){
        countOne++;
    }
    else if(DICE2==2){
        countTwo++;
    }
    else if(DICE2==3){
        countThree++;
    }
    else if(DICE2==4){
        countFour++;
    }
    else if(DICE2==5){
        countFive++;
    }
    else if(DICE2==6){
        countSix++;
    }


    if(DICE3==1){
        countOne++;
    }
    else if(DICE3==2){
        countTwo++;
    }
    else if(DICE3==3){
        countThree++;
    }
    else if(DICE3==4){
        countFour++;
    }
    else if(DICE3==5){
        countFive++;
    }
    else if(DICE3==6){
        countSix++;
    }


    if(DICE4==1){
        countOne++;
    }
    else if(DICE4==2){
        countTwo++;
    }
    else if(DICE4==3){
        countThree++;
    }
    else if(DICE4==4){
        countFour++;
    }
    else if(DICE4==5){
        countFive++;
    }
    else if(DICE4==6){
        countSix++;
    }


    if(DICE5==1){
        countOne++;
    }
    else if(DICE5==2){
        countTwo++;
    }
    else if(DICE5==3){
        countThree++;
    }
    else if(DICE5==4){
        countFour++;
    }
    else if(DICE5==5){
        countFive++;
    }
    else if(DICE5==6){
        countSix++;
    }


    if(countOne>=3 && (countTwo==2 || countThree==2 || countFour==2 || countFive==2 || countSix==2)){
        return 1;
    }
    else if(countTwo>=3 && (countOne==2 || countThree==2 || countFour==2 || countFive==2 || countSix==2)){
        return 1;
    }
    else if(countThree>=3 && (countOne==2 || countTwo==2 || countFour==2 || countFive==2 || countSix==2)){
        return 1;
    }
    else if(countFour>=3 && (countOne==2 || countTwo==2 || countThree==2 ||  countFive==2 || countSix==2)){
        return 1;
    }
    else if(countFive>=3 && (countOne==2 || countTwo==2 || countThree==2 || countFour==2 || countSix==2)){
        return 1;
    }
    else if(countSix>=3 && (countOne==2 || countTwo==2 || countThree==2 || countFour==2 || countFive==2)){
        return 1;
    }

    return 0;
}


int checkPoker(int DICE1, int DICE2, int DICE3, int DICE4, int DICE5){

    int countOne=0, countTwo=0, countThree=0, countFour=0, countFive=0, countSix=0;

    if(DICE1==1){
        countOne++;
    }
    else if(DICE1==2){
        countTwo++;
    }
    else if(DICE1==3){
        countThree++;
    }
    else if(DICE1==4){
        countFour++;
    }
    else if(DICE1==5){
        countFive++;
    }
    else if(DICE1==6){
        countSix++;
    }


    if(DICE2==1){
        countOne++;
    }
    else if(DICE2==2){
        countTwo++;
    }
    else if(DICE2==3){
        countThree++;
    }
    else if(DICE2==4){
        countFour++;
    }
    else if(DICE2==5){
        countFive++;
    }
    else if(DICE2==6){
        countSix++;
    }


    if(DICE3==1){
        countOne++;
    }
    else if(DICE3==2){
        countTwo++;
    }
    else if(DICE3==3){
        countThree++;
    }
    else if(DICE3==4){
        countFour++;
    }
    else if(DICE3==5){
        countFive++;
    }
    else if(DICE3==6){
        countSix++;
    }


    if(DICE4==1){
        countOne++;
    }
    else if(DICE4==2){
        countTwo++;
    }
    else if(DICE4==3){
        countThree++;
    }
    else if(DICE4==4){
        countFour++;
    }
    else if(DICE4==5){
        countFive++;
    }
    else if(DICE4==6){
        countSix++;
    }


    if(DICE5==1){
        countOne++;
    }
    else if(DICE5==2){
        countTwo++;
    }
    else if(DICE5==3){
        countThree++;
    }
    else if(DICE5==4){
        countFour++;
    }
    else if(DICE5==5){
        countFive++;
    }
    else if(DICE5==6){
        countSix++;
    }


    if(countOne>=4){
        return 1;
    }
    else if(countTwo>=4){
        return 1;
    }
    else if(countThree>=4){
        return 1;
    }
    else if(countFour>=4){
        return 1;
    }
    else if(countFive>=4){
        return 1;
    }
    else if(countSix>=4){
        return 1;
    }

    return 0;
}


int checkOnes(int DICE1, int DICE2, int DICE3, int DICE4, int DICE5){
    int countOne=0;

    if(DICE1==1){
        countOne+=1;
    }
    if(DICE2==1){
        countOne+=1;
    }
    if(DICE3==1){
        countOne+=1;
    }
    if(DICE4==1){
        countOne+=1;
    }
    if(DICE5==1){
        countOne+=1;
    }

    if(countOne>=2){
        return countOne;
    }

    return 0;
}


int checkTwos(int DICE1, int DICE2, int DICE3, int DICE4, int DICE5){
    int countTwo=0;

    if(DICE1==2){
        countTwo+=2;
    }
    if(DICE2==2){
        countTwo+=2;
    }
    if(DICE3==2){
        countTwo+=2;
    }
    if(DICE4==2){
        countTwo+=2;
    }
    if(DICE5==2){
        countTwo+=2;
    }
    //(count >= min value)
    if(countTwo>=4){
        return countTwo;
    }

    return 0;
}



int checkThrees(int DICE1, int DICE2, int DICE3, int DICE4, int DICE5){
    int countThree=0;
    if(DICE1==3){
        countThree+=3;
    }
    if(DICE2==3){
        countThree+=3;
    }
    if(DICE3==3){
        countThree+=3;
    }
    if(DICE4==3){
        countThree+=3;
    }
    if(DICE5==3){
        countThree+=3;
    }

    if(countThree>=6){
        return countThree;
    }

    return 0;
}


int checkFours(int DICE1, int DICE2, int DICE3, int DICE4, int DICE5){
    int countFour=0;

    if(DICE1==4){
        countFour+=4;
    }
    if(DICE2==4){
        countFour+=4;
    }
    if(DICE3==4){
        countFour+=4;
    }
    if(DICE4==4){
        countFour+=4;
    }
    if(DICE5==4){
        countFour+=4;
    }

    if(countFour>=8){
        return countFour;
    }

    return 0;
}


int checkFives(int DICE1, int DICE2, int DICE3, int DICE4, int DICE5){
    int countFive=0;

    if(DICE1==5){
        countFive+=5;
    }
    if(DICE2==5){
        countFive+=5;
    }
    if(DICE3==5){
        countFive+=5;
    }
    if(DICE4==5){
        countFive+=5;
    }
    if(DICE5==5){
        countFive+=5;
    }

    if(countFive>=10){
        return countFive;
    }

    return 0;
}


int checkSixes(int DICE1, int DICE2, int DICE3, int DICE4, int DICE5){
    int countSix=0;

    if(DICE1==6){
        countSix+=6;
    }
    if(DICE2==6){
        countSix+=6;
    }
    if(DICE3==6){
        countSix+=6;
    }
    if(DICE4==6){
        countSix+=6;
    }
    if(DICE5==6){
        countSix+=6;
    }

    if(countSix>=12){
        return countSix;
    }

    return 0;
}


void scoreSheet(int computer, int user, int roundnumber, int i){
    printf("\nOur scoresheet after round %d:",i);
    printf("\n=============================");
    printf("\nComputer\tPlayer\n");
    printf(" %d\t\t%d",computer,user);
    printf("\n");
}

