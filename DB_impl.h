/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 * 
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: Rythem Sherma, Kevin Wu, Jacques Villeneuve
 * Lab instructor: R.D. Ardy
 * Lecture instructor: R.D. Ardy, Dhara Wagh
 */

#include "DB.h"
#include <stddef.h> //For 'size_t'
#include <stdbool.h> //For `bool`.


#ifndef DB_IMPL_H
#define DB_IMPL_H


//Helper functions
int compressDB(char fileName[20]);

//Resing functions
void resize(Table *table);
bool resizeTable(Table *table, int newSize);
bool resizeHashtable(Table *table, int newSize);

//Hash functions
unsigned long hash(const char *s); //finds the hash index value
char *convertInt_impl(int ID);
int findIndex(Table *table, const char *key); //probes a table for an empty or identical key
void insertbyType(Table *table, individual_table *element, char *key);
void insertbyID(Table *table, individual_table *element, int ID);
void insertElement(Table *table, individual_table *element, char *key, int index);

//Table functions
Table *setupTable_impl(int capacity); //setups up inner tables
DataBase *db_create_impl(void); //sets up the entirety of all tables. uses setupTable_impl() inside.
char *setStr_impl(char *value); //adds fields to the individual table struct


#endif