/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Rythem Sharma, Kevin Wu, Jacques Villeneuve
 * Lab instructor: R.D. Ardy
 * Lecture instructor: R.D. Ardy, Dhara Wagh
 */

#include "DB.h"
#include "DB_impl.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

//Compresses the database into another file.
int compressDB(char fileName[20]) {

    FILE *in = fopen("PicnicTable.csv", "r");
    FILE *out = fopen(fileName, "w");

    if (in == NULL || out == NULL) {
        printf("File error.\n");
        return 1;
    }

    int curr;
    int prev = EOF;
    int count = 0;

    while ((curr = fgetc(in)) != EOF) {
        if (curr == prev) {
            count++;
        } else {
            if (prev != EOF) {
                fputc(prev, out);
                if (count > 1) {
                    fprintf(out, "%d", count);
                }
            }
            prev = curr;
            count = 1;
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}


//The following are comparing functions which later will be passed to qsort()
int compare_TT(const void *a, const void *b){
    const list_node *aa = *(const list_node **)a;
    const list_node *bb = *(const list_node **)b;
    return strcmp(aa->node->tabletype, bb->node->tabletype);
}

int compare_SM(const void *a, const void *b){
    const list_node *aa = *(const list_node **)a;
    const list_node *bb = *(const list_node **)b;
    return strcmp(aa->node->material, bb->node->material);
}

int compare_StM(const void *a, const void *b){
    const list_node *aa = *(const list_node **)a;
    const list_node *bb = *(const list_node **)b;
    return strcmp(aa->node->structural, bb->node->structural);
}

int compare_NN(const void *a, const void *b){
    const list_node *aa = *(const list_node **)a;
    const list_node *bb = *(const list_node **)b;
    return strcmp(aa->node->neighbourhoodName, bb->node->neighbourhoodName);
}

int compare_Ward(const void *a, const void *b){
    const list_node *aa = *(const list_node **)a;
    const list_node *bb = *(const list_node **)b;
    return strcmp(aa->node->ward, bb->node->ward);
}


//This function updated the hash value
int updateHashValues(Table *table) {

    char convertedInt[10];
    int keyIndex;
    for (int i = 0; i < table->numElems; i++){
        snprintf(convertedInt, 9, "%d", table->arr[i]->node->ID);
        keyIndex = findIndex(table, convertedInt);
        table->hasharr[keyIndex]->index = i;
    }
    return 0;
}

/* =========================================================
   RESIZE FUNCTIONS
   ========================================================= */

//This function will make sure the hash table size is prime.
//Reason being for collision managment and even key distribution
bool is_prime(int num) {

    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
        return false;
        }
    }
    return true;
}

//This function resizes the table by increasing the capacity by 2 times
//Before doubling size it checks weather the hash table size is prime.
void resize(Table *table) {

    int newSize = table->capacity * 2;
    while (!is_prime(newSize)) {
        newSize++;
    }

    bool regTable = resizeTable(table, newSize);
    bool hashTable = resizeHashtable(table, newSize);

    if (!regTable || !hashTable) {
        printf("Rehashing failed.\n");
        return;
    }

    table->capacity = newSize;
}

//This function checks weather the table size has increased.
bool resizeTable(Table *table, int newSize) {

    // table->arr = realloc(table->arr, newSize * sizeof(*table->arr));

    //Use temporary pointer so original pointer not lost.
    list_node **temp = realloc(table->arr, newSize * sizeof(*table->arr));

    if (temp ==NULL) {
        return false;
    }

    table->arr = temp;

    return true;
}

//This function checks weather the hash table size has increased
bool resizeHashtable(Table *table, int newSize) {

    hashInd **newArr = malloc(newSize * sizeof(*newArr));

    if (newArr == NULL) {
        return false;
    }

    for (int i = 0; i < newSize; i++) {
        newArr[i] = NULL;
    }

    for (int i = 0; i < table->capacity; i++) {
        if (table->hasharr[i] != NULL) {
            int newHashInd = hash(table->hasharr[i]->key) % newSize;
            while (newArr[newHashInd] != NULL) {
                newHashInd = (newHashInd + 1) % newSize;
            }
            newArr[newHashInd] = table->hasharr[i];
        }
    }

    //Free the hashtable to avoid memory leak
    free(table->hasharr);
    table->hasharr = newArr;

    return true;
}

/* =========================================================
   HASH
   ========================================================= */

//Hashing algorithm
unsigned long hash(const char *s) {

    unsigned long ret = 5381;
    char c;

    while ((c = *s++)) {
        ret = (unsigned char)(c) + (33 * ret);
    }
    return ret;
}

//Converts an integer ID into a string key since hashing uses strings
char *convertInt_impl(int ID) {

    char convertedInt[10];
    snprintf(convertedInt, 9, "%d", ID);

    char *key = malloc(strlen(convertedInt) + 1);
    if (key == NULL) return NULL;

    strcpy(key, convertedInt);

    return key;
}

//Finds wheere a key has to go in the hashtable and places it there
//Linear probing has been used
int findIndex(Table *table, const char *key) {

    //Safety check
    if (key == NULL) {
        return 0;
    } 

    //Linear probing
    int keyIndex = hash(key) % table->capacity;

    while (table->hasharr[keyIndex] != NULL && table->hasharr[keyIndex]->key != NULL &&
           strcmp(table->hasharr[keyIndex]->key, key) != 0)
    {
        keyIndex = (keyIndex + 1) % table->capacity;
    }

    return keyIndex;
}

/* =========================================================
   INSERT FUNCTIONS
   ========================================================= */

//Inserts data using, a string key
void insertbyType(Table *table, individual_table *element, char *key) {

    int checkSize = table->numElems + 1;
    if ((checkSize * 3) > (table->capacity * 2))
        resize(table);

    char *keyCopy = malloc(strlen(key) + 1);
    strcpy(keyCopy, key);
    int keyIndex = findIndex(table, keyCopy);
    insertElement(table, element, keyCopy, keyIndex);
}

//Inserts using ID converted to string
void insertbyID(Table *table, individual_table *element, int ID) {
    int checkSize = table->numElems + 1;
    if ((checkSize * 3) > (table->capacity * 2))
        resize(table);

    char *key = convertInt_impl(ID);
    int keyIndex = findIndex(table, key);
    insertElement(table, element, key, keyIndex);
}

//Insert main picnic table
void insertMainTable(Table *table, individual_table *element, int ID) {
    int checkSize = table->numElems + 1;
    if ((checkSize * 3) > (table->capacity * 2))
        resize(table);

    char *key = convertInt_impl(ID);

    if (key == NULL) {
        return;
    }

    int keyIndex = hash(key) % table->capacity;

    while (table->hasharr[keyIndex] != NULL) {
        keyIndex = (keyIndex + 1) % table->capacity;
    }

    insertElement(table, element, key, keyIndex);
}

//Inserts into the database into an empty slot using linear probing
void insertElement(Table *table, individual_table *element, char *key, int hashindex) {
    if (table->numElems >= table->capacity) {
        resize(table);
    }

    if (table->hasharr[hashindex] == NULL)
    {
        hashInd *hashnode = malloc(sizeof(*hashnode));
        hashnode->key = key;
        hashnode->index = table->numElems;
        hashnode->count = 1;

        table->hasharr[hashindex] = hashnode;

        list_node *head = malloc(sizeof(*head));
        head->node = element;
        head->next = NULL;

        table->arr[table->numElems] = head;
        table->numElems++;
    }
    else if (strcmp(table->hasharr[hashindex]->key, key) == 0)
    {
        free(key);
        table->hasharr[hashindex]->count++;

        list_node *newhead = malloc(sizeof(*newhead));
        newhead->node = element;
        newhead->next = table->arr[table->hasharr[hashindex]->index];

        table->arr[table->hasharr[hashindex]->index] = newhead;
    }
}

//Initializes the table with the given capacity
Table *setupTable_impl(int capacity) {

    Table *table = malloc(sizeof(*table));
    if (table == NULL) return NULL;

    table->numElems = 0;
    table->capacity = capacity;

    table->arr = malloc(capacity * sizeof(*table->arr));
    table->hasharr = malloc(capacity * sizeof(*table->hasharr));

    if (!table->arr || !table->hasharr) {
        free(table->arr);
        free(table->hasharr);
        free(table);
        return NULL;
    }

    for (int i = 0; i < capacity; i++) {
        table->arr[i] = NULL;
        table->hasharr[i] = NULL;
    }

    return table;
}


//Initializes a whole database with lookup tables
DataBase *db_create_impl(void)
{
    DataBase *db = malloc(sizeof(*db));
    if (!db) return NULL;

    db->tableTypeTable = setupTable_impl(7);
    db->surfaceMaterialTable = setupTable_impl(7);
    db->structuralMaterialTable = setupTable_impl(7);
    db->neighborhoodTable = setupTable_impl(19);
    db->picnicTableTable = setupTable_impl(19);
    db->countWard = setupTable_impl(7);
    db->countNN = setupTable_impl(7);

    if (!db->tableTypeTable || !db->surfaceMaterialTable ||
        !db->structuralMaterialTable || !db->neighborhoodTable ||
        !db->picnicTableTable || !db->countWard || !db->countNN)
    {
        freeDB();
        return NULL;
    }

    return db;
}

//Allocates memory and copy each string
char *setStr_impl(char *value) {
    if (!value) return NULL;

    char *field = malloc(strlen(value) + 1);
    if (!field) return NULL;

    strcpy(field, value);
    return field;
}
