#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashTableApi.h"

#define SIZE 250

int main(int argc, char** argv){


	HTable * testTable = createTable(SIZE, &hashCode,&destroyNodeData,&printData);

	char testString1[50] = "one";
    char testString2[50] = "two";


    char *StringPtr1 = malloc(100*sizeof(char));
    char *stringPtr2 = malloc(100*sizeof(char));

    strcpy(StringPtr1, testString1);
    strcpy(stringPtr2, testString2);

    void * voidTest1 = (void*)StringPtr1;
    void * voidTest2 = (void*)stringPtr2; 

    /*Test Table*/  
    testTable = createTable(SIZE, &hashCode, &destroyNodeData, &printData);
    printf("Insert Data Test \n") ;
    /*Test Insert Data Func*/
    insertData(testTable, StringPtr1, voidTest1);
    insertData(testTable, stringPtr2, voidTest2);


    //destroyData(testTable); 

}
