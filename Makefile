






CC = gcc
CFLAGS= -Wall -g -std=c99

DB.o: DB.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c $<

dashboard: dashboard.c DB.o
	$(CC) $(CFLAGS) $^ -o $@

testdashboardcsv:
	./dashboard -c PicnicTableSmall.csv

testdashboardbin:
	./dashboard -b PicnicTable.bin

testexportDB:
	diff output.txt PicnicTableSmall.csv

valgrinddashboard: dashboard
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$^

clean:
	rm -f dashboard
	rm -f DB.o
	rm -f output.txt