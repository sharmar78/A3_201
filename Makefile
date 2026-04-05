# Author: Rythem Sherma, Kevin Wu, Jacques Villeneuve
# Lab instructor: R.D. Ardy
# Lecture instructor: R.D. Ardy, Dhara Wagh
#Makefile for A3

#Flags
CC = gcc
CFLAGS= -Wall -g -std=c99

dashboard: dashboard.c DB.o DB.h DB_impl.o DB_impl.h
	$(CC) $(CFLAGS) $^ -o $@

DB.o: DB.c DB.h
	$(CC) $(CFLAGS) -c $<

<<<<<<< HEAD
DB_impl.o: DB_impl.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c DB_impl.c

#Compile dashboard

=======
DB_impl.o: DB_impl.c DB_impl.h
	$(CC) $(CFLAGS) -c $<
>>>>>>> 3cd64a76f1cc713b08b289bfe75dd1be686c524d

#Unsure
testDashboardCsv:
	./dashboard -c PicnicTableSmall.csv

#Export
testDashboardBin:
	./dashboard -b PicnicTablec.bin

#Checks leaks
valgrindDashboard: dashboard
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$^

#Clean rule removes all .0 files
clean:
	rm -f *.o dashboard output.txt out.bin
