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

//Double the capacity of a Table structure
Table *resize(Table *table) {

    //Get the capacity of the table and double it
    int newCapacity = table->capacity * 2;

    //Realloc memory for the table.
    Table *newTable = realloc(table, 2 * newCapacity);

    //Check if realloc failed.
    if (newTable == NULL) {
        return table;
    }

    newTable->capacity = newCapacity;

    return newTable;
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

//This count the entry of the given member.
int countEntries(char *memberName, char * value) {

    //Traverse the LL or array and once it encounter given member increase counter.
    printf("Given: %s\n", memberName);
    printf("Given: %s\n", value);

return 0;

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
