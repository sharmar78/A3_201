/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Rythem Sherma, Kevin Wu, Jacques Villeneuve
 * Lab instructor: R.D. Ardy
 * Lecture instructor: R.D. Ardy, Dhara Wagh
 */

#include "DB.h"    
#include "DB_impl.h"  /* Import the public database header. */

#include <stdio.h> //For `printf`.
#include <stdlib.h> //For `size_t`, `malloc`, `calloc`, `free`.
#include <stddef.h> //For 'size_t'
#include <string.h> //For 'strcpy'
#include <stdbool.h> //For `bool`.

/**
 * This function comresses the file and exports it into another file
 * We can use the logic used in A1 in the squeeze.c program
 * Each caracter occuring more than once will be counted and then removed then when new letter happens
 * it resets count, eg. Hello -> hel2o
 */
int compressDB(char fileName[20]) {

    FILE *file = fopen(fileName, "wb");

    if (file == NULL) {
        printf("Failed to write into file.\n");
        return 1;
    }

    fclose(file);
    return 0;
}

//===================RESIZING FUNTIONS=================================
bool is_prime(int num) {
    if (num <= 1) {   return false;}

    for (int i = 2; i * i <= num; i++)  // 2 to root numbers(i) of 'num'; i * i = i^2 = num, so i = sqrt(num). avoids type conversion to double with sqrt() function.  
    {   if (num % i == 0)  // any numbers that leave no remainder after dividing by root is not a prime number
        return false;
    }

    return true;  // if this line is reached, its is a prime number
}

/**
 * This function resizes the hashtable and the regular table once it is full.
 */
void resize(Table *table) {
    int newSize = table->capacity * 2;
    while (!is_prime(newSize)) {
        newSize++;
    }

    bool regTable = resizeTable(table, newSize);
    bool hashTable = resizeHashtable(table, newSize);

    if (!regTable || !hashTable){
        printf("Rehashing failed. Table size not increased.");
        return;
    }
    
    table->capacity = newSize;
}

/**
 * Reallocates memory 
 */
bool resizeTable(Table *table, int newSize) {

    table->arr = realloc(table->arr, newSize * sizeof(*table->arr));

    if (table->arr == NULL){
        return false;
    }
    return true;
}


bool resizeHashtable(Table *table, int newSize) {

    hashInd **newArr = malloc(newSize * sizeof(*newArr));

    if (newArr == NULL){
        return false;
    }
    
    for (int i = 0; i < table->capacity; i++) {   
        newArr[i] = NULL;
    }

    for (int i = 0; i < table->capacity; i++) {
        if (table->hasharr[i] != NULL){
            int newHashInd = hash(table->hasharr[i]->key) % newSize;

            while (newArr[newHashInd] != NULL){   
                newHashInd++;                   
                if (newHashInd >= newSize)  //wrap around if index number goes past the new table size
                {   newHashInd -= newSize;}
            }
            newArr[newHashInd] = table->hasharr[i];
        }
    }

    free(table->hasharr);
    table->hasharr = newArr;

    return true;
}
//==================================================================================



//===================INSERTING NODE FUNCTIONS=================================

/**
 * Implemented the djb2 hashing algorithm.
 */
unsigned long hash(const char *s) {
    unsigned long ret = 5381;
    char c;

    while ((c = *s++))
    {
        ret = (unsigned char)(c) + (33 * ret);
    }
    return ret;
}

char *convertInt_impl(int ID)
{
    char convertedInt[10];
    snprintf(convertedInt, 9, "%d", ID);

    char *key = malloc(strlen(convertedInt) + 1);
    if (key == NULL) {return NULL;}
    strcpy(key, convertedInt);

    return key;
}


/*Probes a given table for a slot, either NULL or the existing key*/
int findIndex(Table *table, const char *key)
{
    int keyIndex = hash(key) % table->capacity;
    while (table->hasharr[keyIndex] != NULL && strcmp(table->hasharr[keyIndex]->key, key) != 0)
    {   keyIndex++;                   
        if (keyIndex >= table->capacity)  //wrap around if index number goes past the table size
        {   keyIndex -= table->capacity;}
    }
    return keyIndex;
}


/*insert into sub tables with material name or table type*/
void insertbyType(Table *table, individual_table *element, char *key)
{
    int checkSize = table->numElems + 1;
    if ((checkSize * 3) > (table->capacity * 2))
    {
        resize(table);
    }

    int keyIndex = findIndex(table, key);
    insertElement(table, element, key, keyIndex);
}

/*insert into main table with ID number*/
void insertbyID(Table *table, individual_table *element, int ID)
{
    int checkSize = table->numElems + 1;
    if ((checkSize * 3) > (table->capacity * 2))
    {
        resize(table);
    }

    char *key = convertInt_impl(ID);
    int keyIndex = findIndex(table, key);
    insertElement(table, element, key, keyIndex);
}


/*
* inserts the node into the desired table.
* arguments
* table: the target hash table
* element: the unique table information node
* hashindex: hashtable slot calculated after probing
* key: ID or material type 
*/
void insertElement(Table *table, individual_table *element, char *key, int hashindex)
{
    if (table->hasharr[hashindex] == NULL) //empty slot in the table
    {
        hashInd *hashnode = malloc(sizeof(*hashnode));
        hashnode->key = key;   //hashnode key points to the same key as inputted
        hashnode->index = table->numElems;   //index for the ACTUAL table is amount of nodes currently in place. if it is the first element, index = 0. second element, index = 1...
        hashnode->count = 1;   //first instance of this key
        table->hasharr[hashindex] = hashnode;   //insert new entry into hashtable at the hashindex

        list_node *head = malloc(sizeof(*head));  //create a bucket for the elements
        head->node = element;      //bucket points to the inputted element 
        head->next = NULL;         //bucket used for linked lists
        table->arr[table->numElems] = head;  //insert bucket into actual table at respective index
        table->numElems++;  //increment element count for the next index position and resizing calculation
    }
 
    else if (strcmp(table->hasharr[hashindex]->key, key) == 0) //key already exists in the table
    {
        table->hasharr[hashindex]->count++; //add more instances of this key to the total count

        list_node *newhead = malloc(sizeof(*newhead));  //create a new bucket
        newhead->node = element;   //store element 
        newhead->next = table->arr[table->hasharr[hashindex]->index];  //new head's next points at old head in actual table
        table->arr[table->hasharr[hashindex]->index] = newhead;  //insert head into actual list as first 

    }
}
//==================================================================================



//===================TABLE AND NODE SET UP FUNTIONS=================================
/*
*helper function for database create
*sets up the actual tables of the database
*/
Table *setupTable_impl(int capacity)
{
    Table *table = malloc(sizeof(*table));
    if (table == NULL)
    {
        return NULL;
    }
    table->numElems = 0;
    table->capacity = capacity;

    //SET UP REGULAR AND HASH TABLES
    table->arr = malloc(table->capacity * sizeof(*table->arr));
    table->hasharr = malloc(table->capacity * sizeof(*table->hasharr));
    if (table->arr == NULL || table->hasharr == NULL)
    {
        free(table->arr);
        free(table->hasharr);
        free(table);
        return NULL;
    }

    //SET INDIVIDUAL ELEMENTS TO NULL
    for (int i = 0; i < table->capacity; i ++)
    {
        table->arr[i] = NULL;
        table->hasharr[i] = NULL;
    }
    return table;
}

/*sets up the database table
* five database struct points to five table structs that contains the array
*/
DataBase *db_create_impl(void)
{
    DataBase *db = malloc(sizeof(*db)); //set up database struct
    if (db == NULL)
    {
        return NULL; //allocation failed
    }

    // set up tables
    db->tableTypeTable = setupTable_impl(7);
    db->surfaceMaterialTable = setupTable_impl(7);
    db->structuralMaterialTable = setupTable_impl(7);
    db->neighborhoodTable = setupTable_impl(19);
    db->picnicTableTable = setupTable_impl(19);
    if (db->tableTypeTable == NULL || db->surfaceMaterialTable == NULL || db->structuralMaterialTable == NULL || db->neighborhoodTable == NULL ||db->picnicTableTable == NULL)
    {
        freeDB();
        return NULL;
    }
    return db;
}

/*
*helper function to parse lines
*adds str to element's node's field value
*ex: round table to table type field
*/
char *setStr_impl(char *value)
{
    if (value == NULL){
        return NULL;
    }
    char *field = malloc(strlen(value) + 1);
    if (field == NULL) {
        return NULL;
    }
    strcpy(field, value);
    return field;
}
//==================================================================================