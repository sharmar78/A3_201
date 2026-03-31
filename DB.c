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

#include <stdio.h>
#include <stdlib.h>

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
void importDB(char *fileName);

/*
 * Takes the name of a .csv file as parameter and creates a .csv file containing
 * the information of the DataBase. The exported .csv file must be EXACTLY the
 * same as the original .csv file from which the DataBase was created (diff
 * command should find no differences).
 */
void exportDB(char *fileName)
{
    game new_game_list[GAMES_LIST_SIZE]; //new array for buffering

    FILE *fp = fopen("out.bin", "rb"); //open file called "out.bin". "rb" to read only.
    if (fp == NULL) //check to make sure the file can be opened
    {
        fprintf(stderr, "Error opening file");
        return;
    }

    fread(new_game_list, sizeof(game), GAMES_LIST_SIZE, fp); //adds bin values to "new_game_list" array for buffering
    fclose(fp); //close file after reading
}