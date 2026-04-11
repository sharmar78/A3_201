# Author: Rythem Sharma, Kevin Wu, Jacques Villeneuve
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

#Run Dashboard (CSV test)
runDashboard:
	./dashboard -c PicnicTable.csv

#Run Dashboard (Binary test)
runDashboardBin:
	./dashboard -b PicnicTable.bin

#Make all (required)
all: dashboard

#Run all tests
tests: runDashboard runDashboardBin

#Checks leaks
valgrindDashboard: dashboard
	valgrind --leak-check=full --track-origins=yes ./$^

#Clean rule removes all .o files
clean:
	rm -f *.o dashboard

#Tar rule
tar:
	cd .. && tar --exclude='.git' -czvf cmpt201_A3_RS.tar.gz A3_201

.PHONY: all tests clean tar runDashboard runDashboardBin valgrindDashboard