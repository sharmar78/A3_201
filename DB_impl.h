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


#ifndef DB_IMPL_H
#define DB_IMPL_H

<<<<<<< HEAD
PicnicTable *resize(PicnicTable *table);
=======
void resize();
>>>>>>> 3cd64a76f1cc713b08b289bfe75dd1be686c524d


void exportDB(char *fileName);

void compressDB(char fToComp[20]);

unsigned long hash(const char *s); //finds the hash index value

int findIndex(Table *table, const char *key); //probes a table for an empty or identical key

void insertbyType(Table *table, individual_table *element, char *key);

void insertbyID(Table *table, individual_table *element, int ID);

void insertElement(Table *table, individual_table *element, char *key, int index);

Table *setupTable_impl(int capacity); //setups up inner tables

DataBase *db_create_impl(void); //sets up the entirety of all tables. uses setupTable_impl() inside.

char *setStr_impl(char *value); //adds fields to the individual table struct


#endif