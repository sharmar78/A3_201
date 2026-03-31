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



/*
 * DECLARE AND TYPEDEF HERE THE STRUCTS Table, NeighbourhoodTable, AND PicnicTable
 * WHICH WILL BE FIELDS IN THE STRUCT DataBase BELOW. YOU MAY DECLARE ADDITIONAL
 * STRUCTS AS NEEDED.
 */
typedef struct{
    int ID;
    char tabletype[20];
    char material[20];
    char structural[20];
    char neighbourhood[20];

    individual_table *tableType_next;
    individual_table *surfaceMaterial_next;
    individual_table *structuralMaterial_next;
    individual_table *neighborhood_next;
    individual_table *picnicTable_next;
} individual_table;

typedef struct{
    int numElems;
    int capacity;
    struct node ** arr;
} Table;

typedef struct{
    int numElems;
    int capacity;
    struct node ** arr;
} NeighbourhoodTable;

typedef struct{
    int numElems;
    int capacity;
    struct node ** arr;
} PicnicTable;

/*
 * The INIT_SIZE is only relevant if you are using arrays for your data structures. 
 * If you are using linked lists you will not need it
 */
#define INIT_SIZE 5  


/*
 * You may change the internal details of the struct below,
 * only keep it typedef'ed to DataBase
 */
typedef struct {
    // You can add anything you see fit here
    Table *tableTypeTable;
    Table *surfaceMaterialTable;
    Table *structuralMaterialTable;
    NeighbourhoodTable *neighborhoodTable;
    PicnicTable *picnicTableTable;
} DataBase;

/* Declare a global DataBase variable*/
/* That should be the only global variable declared*/
/* DB.c should have the definition of this variable*/
DataBase *Db;

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
    char line[256] = {'\0'}; //one line from the csv file
    fgets(line, 256, file); //initial call of fgets to skip header of csv file
    char *element = malloc(sizeof(char)); //part of a csv line to be inserted into Db
    char seek = '\0'; //one char of a line of a csv file

    while (seek != EOF) {
        int i = 0; //i iterates through a line of the csv file
        int j = 0; //tracks which category of the line is being read

        fgets(line, 256, file); 

        while (seek != '\0') { //iterate until the end of the line
            if (seek != ',') {
                seek = line[i];
                element = realloc(element, sizeof(char));
                element[i] = seek;
                i++;
            } else { //if another category of the line is found
                switch (j) {
                case 0: //ID was read
                    printf("ID: %s\n", &element[j]);
                    break;
                case 1: //Table Type was read
                    printf("Table Type: %s\n", &element[j]);
                    break;
                case 2: //Surface Material was read
                    printf("Surface Material: %s\n", &element[j]);
                    break;
                case 3: //Structural Material was read
                    break;
                case 4: //Street / Avenue was read
                    break;
                case 5: //Neighbourhood ID was read
                    break;
                case 6: //Neighbourhood Name was read
                    break;
                case 7: //Ward was read
                    break;
                case 8: //Latitude was read
                    break;
                case 9: //Longitude was read
                    break;
                }

                j++;
                i++; //continue iterating until the end of line
            }
        }
    }
    fclose(file);
}

/*
 * Takes the name of a .csv file as parameter and creates a .csv file containing
 * the information of the DataBase. The exported .csv file must be EXACTLY the
 * same as the original .csv file from which the DataBase was created (diff
 * command should find no differences).
 */
void exportDB(char *fileName);

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
void freeDB();