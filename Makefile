# Author: Rythem Sherma, Kevin Wu, Jacques Villeneuve
# Lab instructor: R.D. Ardy
# Lecture instructor: R.D. Ardy, Dhara Wagh
#Makefile for A3

#Flags
CC = gcc
CFLAGS= -Wall -g -std=c99

#Compile dashboard
dashboard: dashboard.c DB.o DB_impl.o
	$(CC) $(CFLAGS) $^ -o $@


DB.o: DB.c DB.h
	$(CC) $(CFLAGS) -c $<

<<<<<<< HEAD
DB_impl.o: DB_impl.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c DB_impl.c

#Compile dashboard
dashboard: dashboard.c DB.o DB.h DB_impl.o DB_impl.h
	$(CC) $(CFLAGS) $^ -o $@
=======
DB_impl.o: DB_impl.c DB_impl.h
	$(CC) $(CFLAGS) -c $<
>>>>>>> refs/remotes/origin/main

#Unsure
testDashboardCsv:
	./dashboard -c PicnicTableSmall.csv

#Export
testDashboardBin:
	./dashboard -b PicnicTablec.bin

#Checks leaks
valgrindDashboard: dashboard
	valgrind --leak-check=full --track-origins=yes ./$^

#Clean rule removes all .0 files
clean:
	rm -f *.o dashboard dashboard output.txt
