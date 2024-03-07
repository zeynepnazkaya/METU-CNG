//Zeynep Naz Kaya 2526481
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Here I create 2 structures. FishData stores datas, and FishSpecies store name and pointer which helps me to connect these two structures
struct FishData{
    int weight;
    float v_length;
    float d_length;
    float c_length;
    float height;
    float f_length;
    int day;
    int months;
    int year;
    char city[30];
    struct FishData *next;
};
typedef struct FishData *FishData;

struct FishSpecies{
    char fishname[30];
    struct FishData *fishDataList;
    struct FishSpecies *next;
};
typedef struct FishSpecies *FishSpecies;

void addSpeciesList(struct FishSpecies *p);


struct FishSpecies* initializeFishing(char filename[30]){

    //this is for debugging
    setbuf(stdout,0);

    //here I opened file
    FILE *file;
    file=fopen(filename,"r");
    if(file==NULL){
        printf("\nFile cannot open!\n");
        exit(1);
    }

    //these head and last can help me to connect nodes
    struct FishSpecies *head, *last;

    //this ,node is my first node
    struct FishSpecies *node;
    node=(struct FishSpecies*)malloc(sizeof(struct FishSpecies));

    head=node;
    last=node;

    char line[200];
    fgets(line,sizeof(line),file);
    //Here for first node, it read in txt till first ";" this, actually its like node->fishname=Bream (string is cannot written like this but I just write it like this to explain easy)
    sscanf(line, "%[^;]", node->fishname);
    //printf("\nnode->fishname = %s\n",node->fishname);//this puts is for checking if it takes correct or not
    //puts(line); //this puts is for checking if it takes correct or not
    node->next=NULL;

    sscanf(line, ";%d;%f;%f;%f;%f;%f;%d/%d/%d;%[^\n]\n",&node->fishDataList->weight, &node->fishDataList->v_length,
           &node->fishDataList->d_length, &node->fishDataList->c_length, &node->fishDataList->height, &node->fishDataList->f_length, &node->fishDataList->day,
           &node->fishDataList->months, &node->fishDataList->year, node->fishDataList->city);


    struct FishData *fishDataList= (struct FishData*)malloc(sizeof(struct FishData));
    node->fishDataList=NULL;


    //I check all lines in the file with this loop
    while (fgets(line, sizeof(line), file) != NULL) {
        //I allocated species node
        struct FishSpecies *tmpSpecies;
        tmpSpecies = (struct FishSpecies *)malloc(sizeof(struct FishSpecies));
        if (tmpSpecies == NULL) {
            printf("\nOut of memory for tmpSpecies!\n");
            exit(1);
        }

        //I allocated data node
        struct FishData *tmpData;
        tmpData = (struct FishData *)malloc(sizeof(struct FishData));
        if (tmpData == NULL) {
            printf("\nOut of memory for tmpData!\n");
            exit(1);
        }
        tmpData->next = NULL;

        //printf("%s\n",line); //this is also checking for if read line correct or not
        sscanf(line, "%[^;];%d;%f;%f;%f;%f;%f;%d/%d/%d;%[^\n]\n", tmpSpecies->fishname, &tmpData->weight, &tmpData->v_length,
               &tmpData->d_length, &tmpData->c_length, &tmpData->height, &tmpData->f_length, &tmpData->day,
               &tmpData->months, &tmpData->year, tmpData->city);


        if (head == NULL) {
            head = tmpSpecies;
            last = tmpSpecies;
            tmpSpecies->fishDataList = tmpData;
            tmpSpecies->next = NULL;
        }
        else {
            //CHECK IF NEW LİNE İS A NEW SPECİES
            if (strcmp(last->fishname, tmpSpecies->fishname) != 0) {
                //printf("%d\n",tmpData->weight); //this is for checking if it stores datas correct or not
                last->next = tmpSpecies;
                last = tmpSpecies;
                tmpSpecies->fishDataList = tmpData;
                tmpSpecies->next = NULL;
            }
                //IF THEY ARE SAME ADD DATA TO OLD SPECİES
            else {
                struct FishData *lastData = last->fishDataList;
                while (lastData->next != NULL) {
                    lastData = lastData->next;
                }
                lastData->next = tmpData;
            }
        }
    }
    printf("The fishingArchive.txt file has been loaded successfully!\n\n");

    fclose(file);

    return head;
}


void addFishData(struct FishSpecies *p){

    struct FishSpecies *tmp=p;

    int weight, day, months, year;
    float v_length, d_length, c_length, f_length, height;
    char city[30],fishname[30];

    printf("\nSpecies:");
    scanf("%s",fishname);


    strcpy(tmp->fishname,fishname);
    //I am searching species
    while(tmp!=NULL && strcmp(tmp->fishname,fishname) !=0){
        //if species doesn't exist then I create new species and datas with calling this function
        addSpeciesList(p);
        tmp=tmp->next;
    }

    //if fish is have new data I create new data node
    struct FishData *newFishData =(struct FishData *)malloc(sizeof(struct FishData));
    if (newFishData == NULL) {
        printf("\nOut of memory for newFishData!\n");
        exit(1);
    }



    printf("\nWeight of the fish in grams:");
    scanf("%d", &weight);
    printf("\nVertical length in CM:");
    scanf("%f", &v_length);
    printf("\nDiagonal length in CM:");
    scanf("%f", &d_length);
    printf("\nCross length in CM:");
    scanf("%f", &c_length);
    printf("\nHeight in CM:");
    scanf("%f", &height);
    printf("\nFish Length in CM:");
    scanf("%f", &f_length);
    printf("\nFishing date:");
    scanf("%d/%d/%d", &day, &months, &year);
    fflush(stdin);
    printf("\nCity:");
    scanf("%s", city);

    newFishData->weight = weight;
    newFishData->v_length = v_length;
    newFishData->d_length = d_length;
    newFishData->c_length = c_length;
    newFishData->height = height;
    newFishData->f_length = f_length;
    newFishData->day = day;
    newFishData->months = months;
    newFishData->year = year;
    strcpy(newFishData->city, city);
    newFishData->next = NULL;



    //Here I made connections between nodes and data nodes
    if (tmp->fishDataList == NULL) {
        tmp->fishDataList = newFishData;
    }
    else{
        struct FishData *currentData = tmp->fishDataList;
        while (currentData->next != NULL) {
            currentData = currentData->next;
        }
        currentData->next = newFishData;
    }

    printf("\nThe data has been added, successfully!\n");
}


void addSpeciesList(struct FishSpecies *p){


    struct FishSpecies *tmp=p;

    int weight, day, months, year;
    float v_length, d_length, c_length, f_length, height;
    char city[30],fishname[30];
    char answer;


    printf("\nThe new species is: ");
    scanf("%s",fishname);
    fflush(stdin);
    do{

        while(tmp!=NULL && strcmp(tmp->fishname,fishname) !=0){
            tmp=tmp->next;
        }

        //if species which user entered doesn't exist, then I create new node
        if(tmp==NULL){
            struct FishSpecies *newSpecies =(struct FishSpecies *)malloc(sizeof(struct FishSpecies));
            if(newSpecies==NULL){
                printf("\nOut of memory for newSpecies!\n");
                exit(1);
            }

            //here I create connecting last old node and my new node
            strcpy(newSpecies->fishname,fishname);
            newSpecies->fishDataList->next=NULL;
            //İSTERT END YAP
            newSpecies->next=NULL;
            if (p == NULL) {  // If the list is empty, make newSpecies the first node
                p = newSpecies;
            } else {
                struct FishSpecies *current = p;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newSpecies;  // Inserting newSpecies at the end of the list
            }

            //tmp = newSpecies;
        }

        //if fish is have new data I create new data node
        struct FishData *newFishData =(struct FishData *)malloc(sizeof(struct FishData));
        if (newFishData == NULL) {
            printf("\nOut of memory for newFishData!\n");
            exit(1);
        }

        printf("\nWeight of the fish in grams:");
        scanf("%d",&weight);
        printf("\nVertical length in CM:");
        scanf("%f",&v_length);
        printf("\nDiagonal length in CM:");
        scanf("%f",&d_length);
        printf("\nCross length in CM:");
        scanf("%f",&c_length);
        printf("\nHeight in CM:");
        scanf("%f",&height);
        printf("\nFish Length in CM:");
        scanf("%f",&f_length);
        printf("\nFishing date:");
        scanf("%d %d %d",&day,&months,&year);
        fflush(stdin);
        printf("\nCity:");
        scanf("%s",city);

        newFishData->weight = weight;
        newFishData->v_length = v_length;
        newFishData->d_length = d_length;
        newFishData->c_length = c_length;
        newFishData->height = height;
        newFishData->f_length = f_length;
        newFishData->day = day;
        newFishData->months = months;
        newFishData->year = year;
        strcpy(newFishData->city, city);

        newFishData->next = NULL;

        //Here I made connections between nodes and data nodes
        if (tmp->fishDataList == NULL) {
            tmp->fishDataList = newFishData;
        }
        else{
            struct FishData *currentData = tmp->fishDataList;
            while (currentData->next != NULL) {
                currentData = currentData->next;
            }
            currentData->next = newFishData;
        }
        printf("\nDo you want to add more fish (Y/N): ");
        scanf(" %c", &answer);
    }while(answer=='Y');

}


void deleteFish(struct FishSpecies *p, int threshold){

    //currenS holding Species
    //currentD holding Datas

    struct FishSpecies *currentS=p;
    struct FishData *currentD;
    struct FishData *tmp=currentD;

    int i=0;

    while(currentS!=NULL){
        tmp=currentS->fishDataList;
        struct FishData *previousD=NULL;

        while(tmp!=NULL){
            if(tmp->weight <= threshold){

                if(previousD==NULL){
                    currentS->fishDataList=currentS->next->next;
                }
                else{
                    previousD->next=currentS->next;
                }

               // struct FishData *tmp=currentD;
                tmp=tmp->next;
                //free(tmp);

                i++;
            }
            else{
                previousD=tmp;
                tmp=tmp->next;
            }
        }
        currentS=currentS->next;
    }
    printf("\n%d fish data was deleted from your list!\n",i);
}


void printStatistic(struct FishSpecies *p){

    //Here I opened file
    FILE *file=fopen("fishingArchive.txt","r");
    if(file==NULL){
        printf("\nError opening file!\n");
        exit(1);
    }

    char printName[30];
    int i=0;
    printf("\nProvide the species:");
    scanf("%s",&printName);

    //%[^;] This one read data until see ";" this and ;%*[^?\n]\n skip the rest part after fishname and go new line
    while(p!=NULL){
        while( fscanf(file, "%[^;];%*[^\n]\n", p->fishname) == 1) {
            if (strcmp(p->fishname, printName) == 0) {
                i++;
            }
        }
        p=p->next;
    }
    printf("\nThe number of available fist data is %d\n",i);
}



//HOCAM WHEN YOU WANT TO SEARCH PLEASE RUN THE CODE AGAİN AND SEARCH FİRST.(because when you search for example after printing my search function stop I don't understand this part ama its working when you run first search function:(
void searchFishData(struct FishSpecies *p){

    int monthNum,i=0;
    char search, cityName[10];

    printf("\nEnter your search option (C for city/M for month):");
    scanf(" %c",&search);

    //these do-while loops for giving error
    if(search=='M'){
        do{
            printf("\nEnter the month number:");
            scanf("%d",&monthNum);
            if(monthNum<1 || monthNum>12){
                printf("\nYou entered the wrong number!!\n");
            }
        }while(monthNum<1 || monthNum>12);

    }
    else if(search=='C'){
        printf("\nEnter the city name: ");
        scanf("%s", cityName);
    }
//    else{
//        printf("\nYou entered wrong city name!!\n");
//    }

    struct FishSpecies *tmpSpecies =p;

    //Here I am using while loops these while loops helped me to traversing
    while(tmpSpecies!=NULL){
        struct FishData *tmpData= tmpSpecies->fishDataList;
        while(tmpData!=NULL){
            if(search=='C' && strcmp(tmpData->city,cityName)==0){
                //printf("HEREEE");
                //if entered species is found in txt then I incremented i one (i:counting the fish name)
                i++;
                //controling my code
                printf("%s;%d;%.2f;%.2f;%.2f;%.2f;%.2f;%d/%d/%d;%s\n",tmpSpecies->fishname, tmpData->weight, tmpData->v_length,tmpData->d_length, tmpData->c_length, tmpData->height,tmpData->f_length, tmpData->day, tmpData->months,tmpData->year, tmpData->city);

            }
            else if(search=='M' && tmpData->months==monthNum){
                //printf("HEREEE");
                i++;
                printf("%s;%d;%.2f;%.2f;%.2f;%.2f;%.2f;%d/%d/%d;%s\n",tmpSpecies->fishname, tmpData->weight, tmpData->v_length,tmpData->d_length, tmpData->c_length, tmpData->height,tmpData->f_length, tmpData->day, tmpData->months,tmpData->year, tmpData->city);
            }

            tmpData=tmpData->next;
        }
        tmpSpecies=tmpSpecies->next;
    }

    //if entered species is NOT found
    if(i==0){
        printf("\nThere is no fish has this information!\n");
    }
}


void saveUpdatedList(struct FishSpecies *p){
    //Here I opened file to write mode
    FILE *file;
    file=fopen("fishingArchive.txt","w");
    if(file==NULL){
        printf("\nFailed to open file!\n");
        exit(1);
    }

    //TMP CONTROLS FISHSPECIES, TMP2 CONTROLS FISHDATA
    struct FishSpecies *tmp=p;

    //Here I am using while loops these while loops helped me to traversing.
    while(tmp!=NULL){
        //First, I load fishname
        //fprintf(file,"%s;",tmp->fishname);

        //This control helps me two write different line if fishes name are same(for example, in txt I have 2 whitefish but they are in different lines, so this control part helps me to do this)
        int control=1;
        struct FishData *tmp2=tmp->fishDataList;
        while(tmp2!=NULL){

            if(!control){
                fprintf(file,"%s;",tmp->fishname);
            }
            else{
                fprintf(file,"%s;",tmp->fishname);
                control=0;
            }

            //Second, I load Datas
            fprintf(file, "%d;%.2f;%.2f;%.2f;%.2f;%.2f;%d/%d/%d;%s\n",tmp2->weight, tmp2->v_length, tmp2->d_length,tmp2->c_length, tmp2->height, tmp2->f_length,tmp2->day, tmp2->months, tmp2->year,tmp2->city);
            tmp2=tmp2->next;
        }
        tmp=tmp->next;
    }
    fclose(file);
}


int main() {

    struct FishSpecies *speciesList= initializeFishing("fishingArchive.txt");

//    struct Node *tmp;
//    tmp=(struct FishData*)malloc(sizeof(struct FishData));
//    if(tmp==NULL){
//        printf("\nUnsuccessful allocation!");
//        exit(1);
//    }

    int exit=0, option, threshold;
    char newSpecies[30];

    while(exit!=1){

//        fflush(stdin);
        printf("-----MENU---------------------------------------\n"
               "1. Add Fish Data\n"
               "2. Delete Fish Data\n"
               "3. Print Fish Statistics\n"
               "4. Search Fish Data\n"
               "5. Add Species List\n"
               "6. Exit\n");
        printf("Enter your option: ");
        scanf("%d",&option);

        switch (option)
        {
            case 1:
                addFishData(speciesList);
                break;
            case 2:
                printf("\nProvide fish weight threshold in grams:");
                scanf("%d",&threshold);
                deleteFish(speciesList,threshold);
                break;
            case 3:
                printStatistic(speciesList);
                break;
            case 4:
                searchFishData(speciesList);
                break;
            case 5:
                printf("\nThe new species is:");
                scanf(" %c",newSpecies);
                addSpeciesList(speciesList);
                break;
            case 6:
                saveUpdatedList(speciesList);
                exit = 1;
                break;
            default:
                printf("\nOption not recognized!\n");
                break;
        }
    }

    return 0;
}