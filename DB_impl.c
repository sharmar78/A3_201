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




void resize(Table *table) {
    int currSize = table->capacity;
    table = realloc(table, 2 * currSize);
}



int compressDB(char fileName[20]) {

    FILE *file = fopen(fileName, "wb");

    if (file == NULL) {
        printf("Failed to write into file.\n");
        return 1;
    }

    fclose(file);
    return 0;
}



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



/*
*Probes a given table for a slot, either NULL or the existing key
*/
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
    db->neighborhoodTable = setupTable_impl(7);
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
    if (value == NULL)
    {
        return NULL;
    }
    char *field = malloc(strlen(value) + 1);
    if (field == NULL) {
        return NULL;
    }
    strcpy(field, value);
    return field;
}
