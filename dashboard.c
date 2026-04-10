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
    char sortBy[10];
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
    
    while (loop) {
        
        printf("1. Export Database\n2. Count Entries\n3. Sort By\n4. Edit Entry\n5. Report\n6. Compress database\n7. Exit\n\noption: ");
   
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
                scanf("%s", sortBy);

                sortByMember(sortBy);
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
                reportByWard(critReport);
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