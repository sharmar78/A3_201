#Makefile for A3

#Flags
CC = gcc
CFLAGS= -Wall -g -std=c99

DB.o: DB.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c $<

#Compile dashboard
dashboard: dashboard.c DB.o DB.h DB_impl.h
	$(CC) $(CFLAGS) $^ -o $@

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
	rm -f *.o dashboard