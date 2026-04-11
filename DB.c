/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Rythem Sherma, Kevin Wu, Jacques Villeneuve
 * Lab instructor: R.D. Ardy
 * Lecture instructor: R.D. Ardy, Dhara Wagh
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */

#include <stdio.h> //For `printf`.
#include <stdlib.h> //For `size_t`, `malloc`, `calloc`, `free`.
#include <string.h> //For 'strcpy'


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
    if (file == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    char line[256] = {'\0'}; //one line from the csv file, 256 is arbitrary and inspired by windows file name limit
    fgets(line, sizeof(line), file); //initial call of fgets to skip header of csv file

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
        insertbyID(Db->picnicTableTable, element, element->ID);
        insertbyType(Db->tableTypeTable, element, element->tabletype);
        insertbyType(Db->surfaceMaterialTable, element, element->material);
        insertbyType(Db->structuralMaterialTable, element, element->structural);
        insertbyID(Db->neighborhoodTable, element, element->neighbourhoodID);

        insertbyType(Db->countWard, element, element->ward);
        insertbyType(Db->countNN, element, element->neighbourhoodName);
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

    int i = 0; //the last line cannot have a new line, so this prints all but the last line
    fprintf(file, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\n");
    while(i < Db->picnicTableTable->numElems - 1)
    {
        fprintf(file, "%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s\n", 
            Db->picnicTableTable->arr[i]->node->ID, Db->picnicTableTable->arr[i]->node->tabletype, 
            Db->picnicTableTable->arr[i]->node->material, Db->picnicTableTable->arr[i]->node->structural,
            Db->picnicTableTable->arr[i]->node->street, Db->picnicTableTable->arr[i]->node->neighbourhoodID,
            Db->picnicTableTable->arr[i]->node->neighbourhoodName, Db->picnicTableTable->arr[i]->node->ward,
            Db->picnicTableTable->arr[i]->node->latitude, Db->picnicTableTable->arr[i]->node->longitude, 
            Db->picnicTableTable->arr[i]->node->location);
        
        i ++;
    }
    fprintf(file, "%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s",  //print the last line
    Db->picnicTableTable->arr[i]->node->ID, Db->picnicTableTable->arr[i]->node->tabletype, 
    Db->picnicTableTable->arr[i]->node->material, Db->picnicTableTable->arr[i]->node->structural,
    Db->picnicTableTable->arr[i]->node->street, Db->picnicTableTable->arr[i]->node->neighbourhoodID,
    Db->picnicTableTable->arr[i]->node->neighbourhoodName, Db->picnicTableTable->arr[i]->node->ward,
    Db->picnicTableTable->arr[i]->node->latitude, Db->picnicTableTable->arr[i]->node->longitude, 
    Db->picnicTableTable->arr[i]->node->location);
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

int countEntries(char *memberName, char * value)  {
    
    int count = 0;
    hashInd *hashnode = NULL;

    if (strcmp(memberName, "1") == 0) {
        int TTInd = findIndex(Db->tableTypeTable, value);
        hashnode = Db->tableTypeTable->hasharr[TTInd];
        if (hashnode != NULL){
            count = Db->tableTypeTable->hasharr[TTInd]->count;
        }
    } else if (strcmp(memberName, "2") == 0) {
        int SMInd = findIndex(Db->surfaceMaterialTable, value);
        hashnode = Db->surfaceMaterialTable->hasharr[SMInd];
        if (hashnode != NULL){
            count = Db->surfaceMaterialTable->hasharr[SMInd]->count;
        }
    } else if (strcmp(memberName, "3") == 0) {
        int StMInd = findIndex(Db->structuralMaterialTable, value);
        hashnode = Db->structuralMaterialTable->hasharr[StMInd];
        if (hashnode != NULL){
            count = Db->structuralMaterialTable->hasharr[StMInd]->count;
        }
    } else if (strcmp(memberName, "4") == 0) {
        int NIDInd = findIndex(Db->neighborhoodTable, value);
        hashnode = Db->neighborhoodTable->hasharr[NIDInd];
        if (hashnode != NULL){
            count = Db->neighborhoodTable->hasharr[NIDInd]->count;
        }
    } else if (strcmp(memberName, "5") == 0) {
        int NNInd = findIndex(Db->countNN, value);
        hashnode = Db->countNN->hasharr[NNInd];
        if (hashnode != NULL){
            count = Db->countNN->hasharr[NNInd]->count;
        }
    } else if (strcmp(memberName, "6") == 0) {
        int WardInd = findIndex(Db->countWard, value);
        hashnode = Db->countWard->hasharr[WardInd];
        if (hashnode != NULL){
           count = Db->countWard->hasharr[WardInd]->count;
        }
    }
    
    if (hashnode != NULL){
        printf("%s has occured %d times\n", value, count);
    }
    else{
        printf("Value does not exist.\n");
    }
    
    return count;
}

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
void sortByMember(char *memberName){    
    if (strcmp(memberName, "1") == 0) {
        qsort(Db->picnicTableTable->arr, Db->picnicTableTable->numElems, sizeof(list_node *), compare_TT);
        printf("DB exported to table_type.csv to verify\n");
        exportDB("table_type.csv");
    } else if (strcmp(memberName, "2") == 0) {
        qsort(Db->picnicTableTable->arr, Db->picnicTableTable->numElems, sizeof(list_node *), compare_SM);    
        printf("DB exported to surface_material.csv to verify\n");
        exportDB("surface_material.csv");
    } else if (strcmp(memberName, "3") == 0) {
        qsort(Db->picnicTableTable->arr, Db->picnicTableTable->numElems, sizeof(list_node *), compare_StM);
        printf("DB exported to structural_material.csv to verify\n");
        exportDB("structural_material.csv");
    } else if (strcmp(memberName, "4") == 0) {
        qsort(Db->picnicTableTable->arr, Db->picnicTableTable->numElems, sizeof(list_node *), compare_NN);
        printf("DB exported to neighbourhood_name.csv to verify\n");    
        exportDB("neighbourhood_name.csv");
    } else if (strcmp(memberName, "5") == 0) {
        qsort(Db->picnicTableTable->arr, Db->picnicTableTable->numElems, sizeof(list_node *), compare_Ward);  
        printf("DB exported to ward.csv to verify\n");    
        exportDB("ward.csv");  
    }
    
    updateHashValues(Db->picnicTableTable);
    return;
}

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
void editTableEntry(int tableID, char *memberName, char *value) {
    switch (atoi(memberName)) { 
        // Note: I haven't added a check for if user inputs a non-existant value (i.e. "lars")
        // Using switch/case for O(n) time, likely too small a difference to care, feel free to replace with if/else
        case 1: 
            for (int i = 0; i < Db->tableTypeTable->numElems; i++) {
                if (Db->tableTypeTable->arr[i]->node->ID == tableID) {
                    Db->tableTypeTable->arr[i]->node->tabletype = value;
                }
            }
            break;
        case 2:
            for (int i = 0; i < Db->surfaceMaterialTable->numElems; i++) {
                if (Db->surfaceMaterialTable->arr[i]->node->ID == tableID) {
                    Db->surfaceMaterialTable->arr[i]->node->material = value;
                }
            }
            break;
        case 3:
            for (int i = 0; i < Db->structuralMaterialTable->numElems; i++) {
                if (Db->structuralMaterialTable->arr[i]->node->ID == tableID) {
                    Db->structuralMaterialTable->arr[i]->node->structural = value;
                }
            }
            break;
    }
    return;
}


/*
 * print a listing of picnic tables grouped by neigbourhoods in ascending 
 * alphabetical order.
 */
void reportByNeighbourhood(){

    // Sort table by neighbourhood name
    qsort(Db->picnicTableTable->arr,Db->picnicTableTable->numElems,sizeof(list_node *),compare_NN);

    char *currentNeighbourhood = NULL;

    for (int i = 0; i < Db->picnicTableTable->numElems; i++){

        individual_table *n = Db->picnicTableTable->arr[i]->node;

        if (currentNeighbourhood == NULL || strcmp(currentNeighbourhood, n->neighbourhoodName) != 0) {
            currentNeighbourhood = n->neighbourhoodName;
            printf("%s\n", currentNeighbourhood);
        }

        // Printing loop
        printf("%d, %s, %s, %s, %s, %d, %s, %s, %s, %s, (%s)\n",
            n->ID,
            n->tabletype,
            n->material,
            n->structural,
            n->street,
            n->neighbourhoodID,
            n->neighbourhoodName,
            n->ward,
            n->latitude,
            n->longitude,
            n->location
        );
    }
}

/*
 * print a listing of picnic tables grouped by wards in ascending order.
 */
void reportByWard(int critReport) {

    //Checks if user want neighbour or ward
    //Then qsort() will sort them.
    if (critReport == 1) {
        // Sort by neighborhood name ascending.
        qsort(Db->picnicTableTable->arr,Db->picnicTableTable->numElems,sizeof(list_node *),compare_NN);
    } else if (critReport == 2) {
        // Sort by ward ascending
        qsort(Db->picnicTableTable->arr,Db->picnicTableTable->numElems,sizeof(list_node *),compare_Ward);
    }else{
        printf("Invalid report option.\n");
        return;
    }

    //Printing loop
    for (int i = 0; i < Db->picnicTableTable->numElems; i++){
        individual_table *n = Db->picnicTableTable->arr[i]->node;
        printf("%d, %s, %s, %s, %s, %d, %s, %s, %s, %s, (%s)\n",
            n->ID,
            n->tabletype,
            n->material,
            n->structural,
            n->street,
            n->neighbourhoodID,
            n->neighbourhoodName,
            n->ward,
            n->latitude,
            n->longitude,
            n->location
        );
    }
}

/*
 * Frees all dynamic memory associated with each table upon exit. 
 */
void freeDB()
{
    //FREE REG TABLE ELEMENTS
    for (int i = 0; i < Db->picnicTableTable->numElems; i++)
    {
        if (Db->picnicTableTable->arr[i] != NULL)
        {
            free(Db->picnicTableTable->arr[i]->node->tabletype);
            free(Db->picnicTableTable->arr[i]->node->material);
            free(Db->picnicTableTable->arr[i]->node->structural);
            free(Db->picnicTableTable->arr[i]->node->street);
            free(Db->picnicTableTable->arr[i]->node->neighbourhoodName);
            free(Db->picnicTableTable->arr[i]->node->ward);
            free(Db->picnicTableTable->arr[i]->node->latitude);
            free(Db->picnicTableTable->arr[i]->node->longitude);
            free(Db->picnicTableTable->arr[i]->node->location);
            free(Db->picnicTableTable->arr[i]->node);

            //free the linked list
            list_node *curr = Db->picnicTableTable->arr[i];
            while (curr != NULL) {
                list_node *tmp = curr;
                curr = curr->next;
                free(tmp);
            }
            Db->picnicTableTable->arr[i] = NULL;
        }
    }


    for (int i = 0; i < Db->picnicTableTable->capacity; i++)
    {
        if (Db->picnicTableTable->hasharr[i] != NULL)
        {
            free(Db->picnicTableTable->hasharr[i]->key);
            free(Db->picnicTableTable->hasharr[i]);
            Db->picnicTableTable->hasharr[i] = NULL;
        }
    }

    free(Db->picnicTableTable->arr); 
    free(Db->picnicTableTable->hasharr); 
    
    free(Db->tableTypeTable->arr);
    free(Db->tableTypeTable->hasharr); 

    free(Db->surfaceMaterialTable->arr);
    free(Db->surfaceMaterialTable->hasharr); 

    free(Db->structuralMaterialTable->arr);
    free(Db->structuralMaterialTable->hasharr); 

    free(Db->neighborhoodTable->arr);
    free(Db->neighborhoodTable->hasharr); 

    free(Db->countWard->arr);
    free(Db->countWard->hasharr); 

    free(Db->countNN->arr);
    free(Db->countNN->hasharr); 

    free(Db->tableTypeTable);
    free(Db->surfaceMaterialTable);
    free(Db->structuralMaterialTable);
    free(Db->neighborhoodTable);
    free(Db->picnicTableTable);
    free(Db->countNN);
    free(Db->countWard);

    free(Db);
}