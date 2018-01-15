#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/hashTableApi.h"

#define SIZE 250


int main(int argc, char** argv){

	//char dicWords[100];
	char line[100];
	char lineTwo[100];
	char addWord[100];
	char removeWord[100];
	char fileInput = '\0'; 
	char* key;
    // void * voidDicWord;;
	FILE * fileDictionary;
	int menuInput;
	char * linePtr2; 
	char * linePtr;
	void * voidLine;
    int i  =0;
	int counter1 = 0; 
	int counter2 = 0; 

	/*Create Empty Hash Table*/
	HTable * table = createTable(SIZE, &hashCode,&destroyNodeData,&printData);

	/*Pointer for Dictionary File*/

	FILE * fileForSpellCheck;

	//fileForSpellCheck = fopen("../bin/input.txt", "r")
	printf("Welcome to Spell Checker\n");
	printf("-------------------------------------------------\n");

	/*Read File into Hash Table*/
	if(argc == 2){
        fileDictionary = fopen(argv[1],"r");
        if(fileDictionary != NULL){
	            while(fgets(line, 60, fileDictionary) != NULL){
	                
	                strtok(line,"\n");
	                linePtr = malloc(50*sizeof(char*));
	                strcpy(linePtr, line);
	            	voidLine = (void*)linePtr;
	                insertData(table, linePtr, linePtr);
	                //printTable(table);

	            }
	            fclose(fileDictionary);
	 	}else{
			printf("File can not be read\n");
    	}
	}
	printf("--------------------------------------------------\n");


	/*Menu System*/
	while (1){

		printf("--------------------------------------------------\n");
		printf("DISPLAYING TABLE\n");
        printf("--------------------------------------------------\n");
		printTable(table);
		printf("--------------------------------------------------\n");
		printf("\n");
		printf("Menu\n");
		printf("1. Add a word to the Dictionary\n");
		printf("2. Remove a word from the Dictionary\n");
		printf("3. Spell check a file\n");
		printf("4. Show Dictionary words\n");
		printf("5. Quit\n");
		scanf("%d", &menuInput);

		if (menuInput == 1){

			printf("Enter the word: ");
			scanf("%s", addWord);
			insertData(table, addWord, addWord);
			printTable(table);


		}else if(menuInput == 2){

			printf("Enter word that needs to be removed: ");
			scanf("%s", removeWord);
			removeData(table, removeWord);
			printTable(table);


		}else if(menuInput == 3){

			printf("Enter name of file with location: "); 
			scanf("%s", &fileInput); 

			fileForSpellCheck = fopen(&fileInput, "r");
			/*Read User Input File*/
			if(fileForSpellCheck != NULL){
				while (fgets(lineTwo, 100, fileForSpellCheck)){
                    key = malloc(sizeof(char)*strlen(lineTwo)+1);
                    /*Convert All Characters to Lower Case*/
                    for(i = 0;i<strlen(lineTwo);i++){
                        key[i] = tolower(lineTwo[i]);
                    }
                    /*Search*/
                    key[strcspn(key,"\r\n")] = '\0';
                    lineTwo[strcspn(lineTwo,"\r\n")] = '\0';
					linePtr2 = lookupData(table, key);

					if(linePtr2 == NULL){
                        printf("%s was not found in the dictionary\n",key);
						counter1 ++; 
					}else {
						counter2++; 
					}
				}
                printf("Summary:\n");
				printf("There are %d words that are misspelled\n", counter1);
                printf("There are %d words that are spelled\n", counter2);

			}else if (fileForSpellCheck == NULL){
				printf("Error Reading File!!\n"); 
				
			}
		}else if(menuInput == 4){
			printTable(table);
	

		}else if(menuInput == 5){

			return 0;

		}else {

			printf("Incorrect input Fam. Try that shit again.");
		}



	}
}
