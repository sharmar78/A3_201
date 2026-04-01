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

#ifndef DB_IMPL_H
#define DB_IMPL_H

Table *setupTable_impl(); //setups up inner tables

DataBase *db_create_impl(void); //sets up the entirety of all tables. uses setupTable_impl() inside.

char *setStr_impl(char *value);

//compary table type
int cmpTT(const void *a, const void *b);

//compare surface material
int cmpSurMat(const void *a, const void *b);

//Compare structural material
int cmpStructMat(const void *a, const void *b);

//Compare neighbourhood name
int cmpNN(const void *a, const void *b);

//TO-DO: Replace this comment with descriptor for cmpWard
int cmpWard(const void *a, const void *b)

#endif