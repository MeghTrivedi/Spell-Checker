#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/hashTableApi.h"
//#include "../include/linkedList.h"


HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char* key),void (*destroyData)(void *data),void (*printNode)(void *toBePrinted)){

	HTable * table = malloc(sizeof(HTable));
	/*Set initial value of the struct members*/
	table->size = size;
	table->table = malloc((table -> size)*sizeof(Node));
	table->destroyData = destroyData;
  	table->hashFunction = hashFunction;
  	table->printNode = printNode;
  	return table;

}

Node *createNode(char* key, void *data){

	Node * newNode;
	newNode = malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->key = key;
	newNode->data = data;
	return newNode;

}

void destroyTable(HTable *hashTable){

	Node * newNode;
	Node * delete = NULL;

	if (hashTable == NULL){
		return;
	}
	for (int i = 0; i < hashTable->size; i++){

		newNode = hashTable->table[i];
		while(newNode != NULL){
			newNode = newNode->next;
			hashTable->destroyData(delete->next);
			free(delete);
		}
	}
	free(hashTable->table);
	free(hashTable);
}

void destroyNodeData(void *data){

	free(data);

}


void insertData(HTable *hashTable, char* key, void *data){
 	Node * temp = NULL;
    Node * nodeTwo = NULL;
    int i = 0;
    int flag = 0;

    int index = -1;

    if(hashTable == NULL) {
        flag = 1;
    }
    
    index = hashTable->hashFunction(hashTable->size, key);
    if(index >= hashTable->size || index < 0) {
        flag = 1;
    }
    
    if(flag == 1){
        return;
    }
    temp = createNode(key, data);
    if(hashTable->table[index] == NULL){ 
        hashTable->table[index] = temp;
    } else {
        nodeTwo = hashTable->table[index];
        while(nodeTwo->next != NULL) {
            nodeTwo = nodeTwo->next;
        }
        nodeTwo->next = temp;
        while(i < hashTable -> size){
            if(hashTable->table[index] == NULL){
                hashTable -> table[index] = temp;
                //printf("%d\n", index); 
                return;
            }
            index = (index + i + i^2) % (hashTable -> size);
            i++;
            // printf("%d\n", index);
            // printf("---\n");
            // printf("%s\n", key);
         }
    }

}

void insertDataInMap(HTable *hashTable, void *data){

	insertData(hashTable, data, data);
}

void removeData(HTable *hashTable, char* key){
		
    /*Declaring Variables*/
		Node * newNode = NULL;
		Node * lastNode = NULL;

		int index = hashCode(hashTable->size, key);
		newNode = hashTable->table[index];
		int flag = 0;

		if (newNode == NULL){
			flag = 1;
		}
		if (index >= hashTable->size || index < 0 ){
			flag = 1;
		}
		if (flag == 1){
			return;
		}
		if (lastNode == NULL){
            printf("1");
            newNode = hashTable->table[index];
            hashTable->table[index] =  hashTable->table[index]->next;
            free(newNode);
            
			//hashTable->table[index] = newNode->next;
            //free(hashTable->table[index]);
            //hashTable->table[index] = NULL;
            
			return;
		}
		lastNode->next = newNode->next;

		while(newNode->key != key){
            printf("2");
			if(newNode->next == NULL){
				return;
			}
			lastNode=newNode;
			newNode = newNode->next;
		}
		hashTable->destroyData(newNode->data);
		free(newNode);

}

void *lookupData(HTable *hashTable, char* key){
 

    int index;
    Node *temp = NULL;
    index = hashCode(hashTable->size,key);
    if(hashTable->table[index] == NULL){
        return NULL;
    }
    else{
        
        temp = hashTable->table[index];

        while(temp != NULL){
            //printf("Temp->data:%s\n", (char*)temp->data);
            //printf("key:%s\n",key);
            if(strcmp((char*)temp->data,key)==0){
                return temp->data;
            }
            temp= temp->next;
            //index %= hashTable->size;
        }
        
        
    }
    return NULL;
    
}

int hashCode(size_t tableSize, char* key){

	char ch = tolower(key[0]);

	return(ch-'a')%tableSize;

}


void destroyData(void *data){
    free(data);
}

void printTable(HTable * toBePrintedTable){

    for(int i = 0; i < toBePrintedTable->size; i++){
        if(toBePrintedTable->table[i] != NULL){
            printf("index:%d \t key:%s\t",i, toBePrintedTable -> table[i] -> key);
        }
        if(toBePrintedTable -> table[i] != NULL){
            toBePrintedTable -> printNode(toBePrintedTable -> table[i] -> data);
        }  else {
            //printf("node is not allocated\n");
        }
    }

}

void printData(void *toBePrinted){
    if(toBePrinted != NULL ){
        char * newPrint = toBePrinted;
        printf("word:%s\n", newPrint);
    }else{
        printf("the data is NULL\n");
    }
}
