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
<<<<<<< HEAD
#include <string.h>


//compare table type

/**
int cmpTT(const void *a, const void *b) {

}

//compare surface material
int cmpSurMat(const void *a, const void *b) {
    
}
=======
#include <stddef.h> //For 'size_t'
#include <string.h> //For 'strcpy'




void resize(Table *table) {
    int currSize = table->capacity;
    table = realloc(table, 2 * currSize);
}



int compressDB(char fileName[20]) {
>>>>>>> 3cd64a76f1cc713b08b289bfe75dd1be686c524d

//Compare structural material
int cmpStructMat(const void *a, const void *b) {
    
}

<<<<<<< HEAD
//Compare neighbourhood name
int cmpNN(const void *a, const void *b) {
    
}


int cmpWard(const void *a, const void *b) {
    
}

*/

//Double the capacity of the array (**arr).
PicnicTable *resize(PicnicTable *table) {
    int newCapacity = table->capacity * 2;

    table->arr = realloc(table->arr, newCapacity * sizeof(*table->arr));

    if (table->arr == NULL) {
        return table;
    }

    table->capacity = newCapacity;

    return table;
}

//Mostly putChar logic
void compressDB(char fToComp[20]) {

    //Open the file in binary code.
    FILE *in = fopen(fToComp, "rb");
    if (in == NULL) {
        printf("Failed to read file.\n");
        return;
    }

    //Write binary code into the file.
    FILE *out = fopen("zip.bin", "wb");

    if (out == NULL) {
        printf("Failed to write in file.\n");
        return;
    }

    fclose(in);
    fclose(out);
}


Table *setupTable_impl()
=======
    if (file == NULL) {
        printf("Failed to write into file.\n");
        return 1;
    }

    fclose(file);
    return 0;
}

//===================INSERTING NODE FUNCTIONS=================================
/*djb2*/
unsigned long hash(const char *s)
{
    unsigned long ret = 5381;
    char c;

    while ((c = *s++))
    {
        ret = (unsigned char)(c) + (33 * ret);
    }
    return ret;
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
    int keyIndex = findIndex(table, key);
    insertElement(table, element, key, keyIndex);
}

/*insert into main table with ID number*/
void insertbyID(Table *table, individual_table *element, int ID)
{
    int keyIndex = ID % table->capacity;
    char IDstr[10];
    snprintf(IDstr, 9, "%d", ID);

    char *key = malloc(strlen(IDstr) + 1);
    if (key == NULL) {return;}
    strcpy(key, IDstr);

    while (table->hasharr[keyIndex] != NULL)
    {   
        keyIndex++;                   
        if (keyIndex >= table->capacity)  //wrap around if index number goes past the table size
        {   keyIndex -= table->capacity;}
    }
    
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
>>>>>>> 3cd64a76f1cc713b08b289bfe75dd1be686c524d
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
<<<<<<< HEAD
}
=======
}
//==================================================================================
>>>>>>> 3cd64a76f1cc713b08b289bfe75dd1be686c524d
