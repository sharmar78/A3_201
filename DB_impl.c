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
#include <string.h>


//compare table type

/**
int cmpTT(const void *a, const void *b) {

}

//compare surface material
int cmpSurMat(const void *a, const void *b) {
    
}

//Compare structural material
int cmpStructMat(const void *a, const void *b) {
    
}

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