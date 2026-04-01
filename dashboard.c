/*
 * dashboard.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
*/

//You may include other original headers as you see fit
#include "DB.h"
#include "DB_impl.h"

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){

    //Prints the arguments given
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    Db = db_create_impl();
    importDB(argv[2]);

    for (int i = 0; i < Db->picnicTableTable->numElems; i++)
    {
        printf("%d, %s, %s, %s, %s, %d, %s, %s, %s, %s, %s\n", 
            Db->picnicTableTable->arr[i]->ID, Db->picnicTableTable->arr[i]->tabletype, 
            Db->picnicTableTable->arr[i]->material, Db->picnicTableTable->arr[i]->structural,
            Db->picnicTableTable->arr[i]->street, Db->picnicTableTable->arr[i]->neighbourhoodID,
            Db->picnicTableTable->arr[i]->neighbourhoodName, Db->picnicTableTable->arr[i]->ward,
            Db->picnicTableTable->arr[i]->latitude, Db->picnicTableTable->arr[i]->longitude, 
            Db->picnicTableTable->arr[i]->location);
    }

    exportDB("output.txt");
    
    int option;
    int sortBy;
    int numTabEntry;
    int memberCode;
    // char value; ???
    char fileName[20];
    int critReport;

    printf("1. Export Database\n2. Count Entries\n3. Sort By\n4. Edit Entry\n5. Report\n6. Compress database\n7. Exit\n");
    scanf("%d", &option);
    printf("\n");

    //Exports the database using the function called exportDB()
    if (option == 1) {
        printf("Export");
        exportDB("export.csv"); //idk if correct
    } else if (option == 2) {   //Count entry in a database by selecting which option
        //count entry;
        //go through the table and print each occurence of the item
    } else if (option == 3) { //Sorts
        printf("Enter a criteria to sort by (1.TT 2.SM 3.StM 4.NID 5.NN 6.W): ");
        scanf("%d", &sortBy);
    } else if (option == 4) { 
        printf("Enter a numerical table entry to edit: ");
        scanf("%d", &numTabEntry);   
        while (numTabEntry > 3 || numTabEntry < 0) {
                printf("Invalid entry. Enter a value between 0 and 3: ");
                scanf("%d", &numTabEntry);
            }
        printf("Enter member code (1.TT 2.SM 3.StM): ");
        scanf("%d", &memberCode);
        // printf("Enter Value: ");
        // scanf("%s", &fileName);
    } else if (option == 5) {     //Reports
        printf("Enter a criteria to report by (1. Neighborhood 2. Ward): ");
        scanf("%d", &critReport);
    //Compressing database into a file.
    } else if (option == 6) {   
        printf("Enter filename: ");
        scanf("%s", fileName);
        compressDB(fileName);
    } else if (option == 7) {
        freeDB();
        exit(0);
    }
    return 0;
}