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
#include <string.h> //For 'strcpy'


Table resize(Table *table) {
    int currSize = table->capacity;
    table = realloc(table, 2 * currSize);
}

int compressDB(char fileName[20]) {

    FILE *file = fopen(fileName, "wb");

    if (file == NULL) {
        printf("Failed to write into file.\n");
        return 0;
    }

    fclose(file);
}

Table *setupTable_impl()
{
    Table *table = malloc(sizeof(*table));
    if (table == NULL)
    {
        return NULL;
    }
    table->numElems = 0;
    table->capacity = 20;
    table->arr = malloc(table->capacity * sizeof(*table->arr));
    if (table->arr == NULL)
    {
        free(table);
        return NULL;
    }
    for (int i = 0; i < table->capacity; i ++)
    {
        table->arr[i] = NULL;
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
    db->tableTypeTable = setupTable_impl();
    db->surfaceMaterialTable = setupTable_impl();
    db->structuralMaterialTable = setupTable_impl();
    if (db->tableTypeTable == NULL || db->surfaceMaterialTable == NULL || db->structuralMaterialTable == NULL)
    {
        return NULL;
    }

    db->neighborhoodTable = malloc(sizeof(*db->neighborhoodTable));
    db->neighborhoodTable->numElems = 0;
    db->neighborhoodTable->capacity = 20;
    db->neighborhoodTable->arr = malloc(db->neighborhoodTable->capacity * sizeof(*db->picnicTableTable->arr));
    if (db->neighborhoodTable->arr == NULL)
    {
        free(db->neighborhoodTable);
        return NULL;
    }
    for (int i = 0; i < db->neighborhoodTable->capacity; i ++)
    {
        db->neighborhoodTable->arr[i] = NULL;
    }

    db->picnicTableTable = malloc(sizeof(*db->picnicTableTable));
    db->picnicTableTable->numElems = 0;
    db->picnicTableTable->capacity = 20;
    db->picnicTableTable->arr = malloc(db->picnicTableTable->capacity * sizeof(*db->picnicTableTable->arr));
    if (db->picnicTableTable->arr == NULL)
    {
        free(db->picnicTableTable);
        return NULL;
    }
    for (int i = 0; i < db->picnicTableTable->capacity; i ++)
    {
        db->picnicTableTable->arr[i] = NULL;
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
