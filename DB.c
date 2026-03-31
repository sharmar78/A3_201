/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */

#include <stdio.h> //For `printf`.
#include <stdlib.h> //For `size_t`, `malloc`, `calloc`, `free`.
#include <string.h> //For 'strcpy'



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

/* Declare a global DataBase variable*/
/* That should be the only global variable declared*/
/* DB.c should have the definition of this variable*/
DataBase *Db;

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
 * Takes the name of a .csv file as parameter and creates and populates the
 * DataBase with the corresponding dataset information. All five DataBase tables
 * must be populated after a call to this function. All strings stored in the
 * DataBase must use dynamic memory. Each line of the .csv file can only be read
 * once, in other words, the four lookup tables must be created at the same time
 * as the main picnicTableTable.
 */
void importDB(char *fileName) {
    FILE *file = fopen(fileName, "r"); //pointer to csv file
    if (file == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    char line[256] = {'\0'}; //one line from the csv file
    fgets(line, sizeof(line), file); //initial call of fgets to skip header of csv file

    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        individual_table *element = malloc(sizeof(*element)); //setting up individial elements
        char *IDstr = strtok(line, ",");
        int ID = atoi(IDstr);
        element->ID = ID;


        Db->picnicTableTable->arr[count] = element;
        Db->picnicTableTable->numElems++;
        count ++;
    }

    fclose(file);
}

/*
 * Takes the name of a .csv file as parameter and creates a .csv file containing
 * the information of the DataBase. The exported .csv file must be EXACTLY the
 * same as the original .csv file from which the DataBase was created (diff
 * command should find no differences).
 */
void exportDB(char *fileName)
{
    return;
}

/*
 * Take the name of a member of the picnicTable entry and a value for that member 
 * as parameters and return the number of entries in the picnicTable which have 
 * that value for the memberName.
 * 
 * This is to be implemented for the following members:
 *  1- Table Type
 *  2- Surface Material
 *  3- Structural Material
 *  4- Neighborhood ID
 *  5- Neighborhood Name
 *  6- Ward
 */

int countEntries(char *memberName, char * value);

/*
 * Take the name of a member of the picnicTable entry as an argument 
 * and sort the table in ascending order of the entry values of that member. 
 * The function must be implemented for:
 *   1- Table Type
 *   2- Surface Material
 *   3- Structural Material
 *   4- Neighborhood Name
 *   5- Ward
 */
void sortByMember(char *memberName);

/*
 * Take a tableID, the name of a member of the picnicTable entry and a value for that 
 * member as parameters, and find the entry which has that tableID and 
 * change its memberName value to newValue. 
 * Members that can be modified:
 *  1- Table Type
 *  2- Surface Material
 *  3- Structural Material 
 * If the new value is not found in the existing tables, this value must be added to the 
 * corresponding table.
 */
void editTableEntry(int tableID, char *memberName, char *value);


/*
 * print a listing of picnic tables grouped by neigbourhoods in ascending 
 * alphabetical order.
 */
void reportByNeighbourhood();

/*
 * print a listing of picnic tables grouped by wards in ascending order.
 */
void reportByWard();

/*
 * Frees all dynamic memory associated with each table upon exit. 
 */
void freeDB()
{
    if (Db == NULL)
    {
        return;
    }

    if(Db->picnicTableTable != NULL)
    {
        for (int i = 0; i < Db->picnicTableTable->capacity; i++)
        {
            if (Db->picnicTableTable->arr[i] != NULL)
            {
                    free(Db->picnicTableTable->arr[i]->tabletype);
                    free(Db->picnicTableTable->arr[i]->material);
                    free(Db->picnicTableTable->arr[i]->structural);
                    free(Db->picnicTableTable->arr[i]->street);
                    free(Db->picnicTableTable->arr[i]->neighbourhoodName);
                    free(Db->picnicTableTable->arr[i]->ward);
                    free(Db->picnicTableTable->arr[i]->location);
                    free(Db->picnicTableTable->arr[i]);
            }
        }
        free(Db->picnicTableTable->arr);
    }


    if(Db->tableTypeTable != NULL)
    {
        //for (int i = 0; i < Db->tableTypeTable->capacity; i++)
        //{
            //if(Db->tableTypeTable->arr[i] != NULL)
            //{
            //    free(Db->tableTypeTable->arr[i]);
            //}
        //}
        if(Db->tableTypeTable->arr != NULL)
        {
            free(Db->tableTypeTable->arr);
        }
    }

    if(Db->surfaceMaterialTable != NULL)
    {
        if(Db->surfaceMaterialTable->arr != NULL)
        {
            free(Db->surfaceMaterialTable->arr);
        }
    }

    if(Db->structuralMaterialTable != NULL)
    {
        if(Db->structuralMaterialTable->arr != NULL)
        {
            free(Db->structuralMaterialTable->arr);
        }
    }

    if(Db->neighborhoodTable != NULL)
    {
        if(Db->neighborhoodTable->arr != NULL)
        {
            free(Db->neighborhoodTable->arr);
        }
    }


    free(Db->tableTypeTable);
    free(Db->surfaceMaterialTable);
    free(Db->structuralMaterialTable);
    free(Db->neighborhoodTable);
    free(Db->picnicTableTable);
    free(Db);
}