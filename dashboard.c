/*
 * dashboard.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Rythem Sherma, Kevin Wu, Jacques Villeneuve
 * Lab instructor: R.D. Ardy
 * Lecture instructor: R.D. Ardy, Dhara Wagh
*/

//You may include other original headers as you see fit
#include "DB.h"
#include "DB_impl.h"

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    int loop = 1; // Loop flag for checking options
    int option = 8;
    int sortBy;
    int numTabEntry;
    char memberCode[10];
    int numTableEntry;
    char value[40];
    char fileName[20];
    int critReport;
    char export[20];

    if (argc < 3) {
        printf("Usage: %s <input> <file>\n", argv[0]);
        return 1;
    }

    Db = db_create_impl();
    importDB(argv[2]);
    
    printf("Capacity of picnic table: %d\n", Db->picnicTableTable->capacity);
    
    printf("Capacity of picnic table: %d\n", Db->picnicTableTable->capacity);


      //============================examples of how to access the tables======================================
    printf("\n");
    
    /**
    int index = findIndex(Db->tableTypeTable, Db->picnicTableTable->arr[7]->node->tabletype); //Round table entry
    printf("Number of Round Tables: %d\n", Db->tableTypeTable->hasharr[index]->count); //Number of Round Tables: 1
    int index2 = findIndex(Db->tableTypeTable, Db->picnicTableTable->arr[8]->node->tabletype); //Square table entry
    printf("Number of Square Tables: %d\n", Db->tableTypeTable->hasharr[index2]->count); //Number of Round Tables: 9

    for (int i = 0; i < Db->tableTypeTable->numElems; i++) {
        printf("ID: %d, Type: %s\n", i, Db->tableTypeTable->arr[i]->node->tabletype);
    }
    

    int index3 = findIndex(Db->surfaceMaterialTable, Db->picnicTableTable->arr[7]->node->material); //Metal table entry
    printf("Number of Metal Surfaces: %d\n", Db->surfaceMaterialTable->hasharr[index3]->count); //Number of Metal Tables: 1
    int index4 = findIndex(Db->surfaceMaterialTable, Db->picnicTableTable->arr[8]->node->material); //Square table entry
    printf("Number of Wood Surfaces: %d\n", Db->surfaceMaterialTable->hasharr[index4]->count); //Number of Wood Tables: 10

    for (int i = 0; i < Db->surfaceMaterialTable->numElems; i++) {
        printf("ID: %d, Type: %s\n", i, Db->surfaceMaterialTable->arr[i]->node->material);
    }

*/
    while (loop) {
        
        printf("1. Export Database\n2. Count Entries\n3. Sort By\n4. Edit Entry\n5. Report\n6. Compress database\n7. Exit\n\noption: ");
        scanf("%d", &option);

        //Scanf return 1 if successfull and 0 if not, therefore is scanf is not successful it will print invalid input
        //then  it will remove all the character until new line, idea was proposed by Ardy RD. 
        if (scanf("%d", &option) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue; //Once the OPTION not get the input it goes back at the top printing the loop again displaying the whole menu.
        }

        printf("\n");

        switch (option) {
            //Exports the database file content into another file
            case 1:
                printf("File name to export into: ");
                scanf("%s", export);
                exportDB(export);
                break;

            //Prnts occurences of the value in the databse
            case 2:
                printf("Enter member code (1.TT 2.SM 3.StM 4.NID 5.NN 6.W): ");
                scanf("%s", memberCode);

                printf("Enter Value: ");
                scanf(" %[^\n]", value);

                countEntries(memberCode, value);
                break;

            //Sorts the db according to the given criteria, most likely using qsort()
            case 3:
                printf("Enter a criteria to sort by (1.TT 2.SM 3.StM 4.NID 5.NN 6.W): ");
                scanf("%d", &sortBy);
                break;

            //Edit a table entry
            case 4:
                printf("Enter a numerical table entry to edit: ");
                scanf("%d", &numTabEntry);

                while (numTabEntry > 3 || numTabEntry < 0) {
                    printf("Invalid entry. Enter a value between 0 and 3: ");
                    scanf("%d", &numTabEntry);
                }

                printf("Enter member code (1.TT 2.SM 3.StM): ");
                scanf("%d", &numTableEntry);
                break;

            //Reports a criteria
            case 5:
                printf("Enter a criteria to report by (1. Neighborhood 2. Ward): ");
                scanf("%d", &critReport);
                break;

            //Compresses the db into another file
            case 6:
                printf("Enter filename: ");
                scanf("%s", fileName);
                compressDB(fileName);
                break;

            //Exits the program by freein the allocated memory
            case 7:
                loop = 0;
                freeDB();
                exit(0);

            //Invalid option
            default:
                printf("Invalid option. Try again.\n");
        }
    }
    
    return 0;
}