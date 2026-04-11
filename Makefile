# Author: Rythem Sherma, Kevin Wu, Jacques Villeneuve
# Lab instructor: R.D. Ardy
# Lecture instructor: R.D. Ardy, Dhara Wagh
#Makefile for A3

#Flags
CC = gcc
CFLAGS= -Wall -g -std=c99

#Compile dashboard
dashboard: dashboard.c DB.o DB.h DB_impl.o DB_impl.h
	$(CC) $(CFLAGS) $^ -o $@

DB.o: DB.c DB.h
	$(CC) $(CFLAGS) -c $<

DB_impl.o: DB_impl.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c DB_impl.c

#Run Dashboard
runDashboard:
	./dashboard -c PicnicTableSmall.csv

#Export
testDashboardBin:
	./dashboard -b PicnicTable.bin

#Checks leaks
valgrindDashboard: dashboard
	valgrind --leak-check=full --track-origins=yes ./$^

#Clean rule removes all .o files
clean:
	rm -f *.o dashboard

#Tar rule
tar: 
	cd .. && tar --exclude='.git' -czvf cmpt201_A3_RS.tar.gz A3_201