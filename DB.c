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
        freeDB();
        return NULL;
    }

    db->neighborhoodTable = malloc(sizeof(*db->neighborhoodTable));
    db->neighborhoodTable->numElems = 0;
    db->neighborhoodTable->capacity = 20;
    db->neighborhoodTable->arr = malloc(db->neighborhoodTable->capacity * sizeof(*db->picnicTableTable->arr));
    if (db->neighborhoodTable->arr == NULL)
    {
        freeDB();
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
        freeDB();
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
    if (field == NULL)
    {
        return NULL;
    }
    strcpy(field, value);
    return field;
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

    int count = 0; //index of the table
    while (fgets(line, sizeof(line), file) != NULL) //read every line of the file
    {
        individual_table *element = malloc(sizeof(*element)); //setting up individial elements

        //assign values into individual nodes
        element->ID = atoi(strtok(line, ",")); // convert str to int guide: https://www.geeksforgeeks.org/c/convert-string-to-int-in-c/
        element->tabletype = setStr_impl(strtok(NULL, ",")); //strtok: split string at "comma", or whatever is in quotes: https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
        element->material = setStr_impl(strtok(NULL, ","));
        element->structural = setStr_impl(strtok(NULL, ","));
        element->street = setStr_impl(strtok(NULL, ","));
        element->neighbourhoodID = atoi(strtok(NULL, ","));
        element->neighbourhoodName = setStr_impl(strtok(NULL, ","));
        element->ward = setStr_impl(strtok(NULL, ","));
        element->latitude = setStr_impl(strtok(NULL, ","));
        element->longitude = setStr_impl(strtok(NULL, ","));
        element->location = setStr_impl(strtok(NULL, "\n")); //NOTE: last field is not split by comma as there is one naturally in the field

        //add the node to the pointers in tables. all pointers point to the same node for space efficiency.
        Db->picnicTableTable->arr[count] = element;
        Db->picnicTableTable->numElems++; //tracks total value for resizing, if needed
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
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    fprintf(file, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\r\n");
    for (int i = 0; i < Db->picnicTableTable->numElems; i++)
    {
            fprintf(file, "%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s\n", 
                Db->picnicTableTable->arr[i]->ID, Db->picnicTableTable->arr[i]->tabletype, 
                Db->picnicTableTable->arr[i]->material, Db->picnicTableTable->arr[i]->structural,
                Db->picnicTableTable->arr[i]->street, Db->picnicTableTable->arr[i]->neighbourhoodID,
                Db->picnicTableTable->arr[i]->neighbourhoodName, Db->picnicTableTable->arr[i]->ward,
                Db->picnicTableTable->arr[i]->latitude, Db->picnicTableTable->arr[i]->longitude, 
                Db->picnicTableTable->arr[i]->location);
    }
    fclose(file);
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
            free(Db->picnicTableTable->arr[i]->latitude);
            free(Db->picnicTableTable->arr[i]->longitude);
            free(Db->picnicTableTable->arr[i]->location);
            free(Db->picnicTableTable->arr[i]);
            Db->picnicTableTable->arr[i] = NULL;
        }
    }
    free(Db->picnicTableTable->arr);    
    free(Db->tableTypeTable->arr);
    free(Db->surfaceMaterialTable->arr);
    free(Db->structuralMaterialTable->arr);
    free(Db->neighborhoodTable->arr);

    free(Db->tableTypeTable);
    free(Db->surfaceMaterialTable);
    free(Db->structuralMaterialTable);
    free(Db->neighborhoodTable);
    free(Db->picnicTableTable);

    free(Db);
}