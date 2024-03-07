//Zeynep Naz Kaya 2526481

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function prototypes
void displayMenu();
void startQuiz(int *, char[5][30], int[5]);
void viewHighScores(char[5][30], int[5], int);
void loadQuestions(char[10][1000], char[10][50]);
int loadHighScores(char[5][30], int[5]);
void saveHighScores(char[5][30], int[5], int *);
int askQuestions(char[10][1000], char[10][50]);
void getUserInput(char []);


int main() {

    int exit=0;
    char choice;
    char input[20];
    int numElements;
    int scores[5];
    char userNames[5][30];

    printf("Welcome to the C Programming Quiz Game!\n");
    do
    {
        //calling displayin menu
        displayMenu();
        //calling loadHighScores function
        numElements=loadHighScores(userNames,scores);
        printf("Enter your choice:");
        //calling getUserInput to take input from user
        getUserInput(input);
        //Here I only want input's first element. Because, for example, when my choice is 2, "2" is only 1 character and first element
        choice = input[0];

        if(choice=='1'){
            //When my choice is 1, Quiz should start so, I called StartQuiz
            startQuiz(&numElements,userNames,scores);
        }
        else if(choice=='2'){

            printf("\nTop 5 High Scores:\n");
            //This viewHighScores function show us scores
            viewHighScores(userNames,scores,numElements);
        }
        else if(choice=='3'){

            printf("\nGoodbye!\n");
            exit=1;
        }
        else{

            printf("\nPlease try again");
        }
    }
    while(exit!=1);

    return 0;
}

//Basic display Function, it only prints
void displayMenu(){
    printf("\nMenu:\n");
    printf("1.Start Quiz\n");
    printf("2.View High Scores\n");
    printf("3.Quit\n\n");
}


void getUserInput(char input[]){
    //I wrote fflush so that there is no problem in the buffer
    fflush(stdin);
    //taking input with gets
    gets(input);
}


void loadQuestions(char questions[10][1000], char answers[10][50]){

    printf("\nLoading quiz questions...");
    //Since I didn't know if it was empty or not, I emptied it so I could fill it correctly.,
    for(int i=0; i<10; i++){
        strcpy(questions[i],"");
        strcpy(answers[i],"");
    }

    //opening file
    FILE *inFile;

    char line[200];
    int lineCounter=0, questionsCounter=0;

    inFile= fopen("questions.txt","r");

    if(inFile == NULL){
        printf("\nFailed to open file.\n");
        exit(1);
    }

    printf("\nThe file has been successfully opened for reading.\n\n");
    //Here, in while loop, fgets read lines
    while(fgets(line, 200,inFile)){
        //in txt after 5 lines there is answer
        if(lineCounter==5){
            strcat(answers[questionsCounter],line);
            lineCounter++;
            continue;
        }
        //This part after 6 lines, a new question comes
        if(lineCounter==6){
            questionsCounter++;
            lineCounter=0;
            continue;
        }
        lineCounter++;
        strcat(questions[questionsCounter],line);
    }
    fclose(inFile);
}


int askQuestions(char questions[10][1000], char answers[10][50]){

    int score=0,i;
    char input[2];
    char correctAnswer;

    //prints questions
    for(i=0; i<10; i++) {
        puts(questions[i]);

        //Asking user what's their answer
        printf("Your answer:");
        getUserInput(input);

        //For last question's answer is:
        if(i==9){
            correctAnswer=answers[i][strlen(answers[i]) - 1];
        }
            //For Other questions' answer is:
        else{
            correctAnswer=answers[i][strlen(answers[i]) - 2];
        }
        //If the answer entered by the user is the same as the real answer,she has answered the question correctly.
        if (input[0] == correctAnswer) {
            printf("Correct!\n\n");
            //The score increases with each correct answer
            score++;
        } else {
            printf("Wrong!\n\n");
        }

    }

    printf("\nYou completed the quiz! Your score: %d/10\n",score);

    //AskQuestions answers should return score
    return score;
}

//I have 2 data, 1 for holding name and 1 for holding score
void startQuiz(int *numElements, char userNames[5][30], int scores[5]){

    char questions[10][1000];
    char answers[10][50];
    char userAnswer;
    int Score, i;
    char input[30];


    loadQuestions(questions,answers);

    //I use score so, I called askQuestions function
    Score= askQuestions(questions,answers);
    //printf("\nYour score is %d\n",Score);  , this checks if it comes correct from askQuestions or not

    printf("Do you want to save your score?(Y/N):");
    scanf(" %c",&userAnswer);


    int min=scores[0], minIndex=0;
    char minName[30];
    strcpy(minName,userNames[0]);

    //if user want to save their score then, I asked their name
    if(userAnswer=='Y'){
        printf("Enter your name?");
        getUserInput(input);

        //Here my code finds the lowest score and its index.
        //if I have 5 elements (if its full), it finds lowest score and replace the score which I wanted
        //Also I update new score and name
        if(*numElements== 5) {
            for (i=0; i<5; i++) {
                if (min > scores[i]) {
                    min = scores[i];
                    strcpy(minName, userNames[i]);
                    minIndex = i;
                }
            }
            //if score is greater than min score, it updates
            if (Score > min) {
                scores[minIndex] = Score;
                strcpy(userNames[minIndex], input);
            }
        }

            //this condition means there is still space in the array
        else if(*numElements< 5){
            scores[*numElements]=Score;
            strcpy(userNames[*numElements],input);
            //after adding new score, in the score array, elements has increased
            (*numElements)++;
        }

        //To save my scores I called this function
        saveHighScores(userNames,scores,numElements);
    }
}



int loadHighScores(char userNames[5][30], int scores[5]){

    //opening file
    FILE *inFile;

    char *tempScore;
    inFile= fopen("highScore.txt","r");

    //this loop makes all the user names empty
    for(int i=0; i<5; i++){
        strcpy(userNames[i],"");
    }

    //for opening file, I wrote error check
    int i = 0;
    if(inFile == NULL){
        printf("\nFailed to open file.\n");
        inFile= fopen("highScore.txt","w");

    }

    else {

        char temp1[10],temp2[10],temp3[10];

        printf("\nThe file has been successfully opened for reading.\n\n");

        //Reading data from file
        //Format is :  2. naz - 9/10  ->  temp1=2. , userName=zeynep , - = temp2, 9/10 = temp3
        while (fscanf(inFile, "%s %s %s %s", temp1, userNames[i], temp2, temp3) != EOF) {

            //"/" this uses for a delimiter
            tempScore = strtok(temp3,"/");
            //atoi: converts string to an intiger
            scores[i]= atoi(tempScore);
            i++;
        }
    }

    fclose(inFile);

    //The function returns the number of scores successfully loaded from the file
    return i;
}


void saveHighScores(char userNames[5][30], int scores[5],int *numElements){
    FILE *inFile;

    //opening file for writing
    inFile= fopen("highScore.txt","w");

    if(inFile == NULL){
        printf("\nFailed to open file.\n");
        exit(1);
    }

    //writing data from file
    for (int i=0; i<*numElements ; i++) {
        fprintf(inFile, "%d. %s - %d/10\n", i+1,userNames[i],scores[i]);
    }

    fclose(inFile);
}



void viewHighScores(char userNames[5][30], int scores[5], int numElements){

    //this fuction prints users and their scores
    for (int i=0; i<numElements ; i++) {

        printf("%d. %s - %d/10\n", i+1, userNames[i], scores[i]);
    }
}