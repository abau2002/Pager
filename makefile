# FILE: makefile

pager: Pager.o Table.o Random.o
	g++ Pager.o Table.o Random.o -o pager

Pager.o: Pager.cpp Pager.h Table.h Random.h
	g++ -c Pager.cpp

Table.o: Table.cpp Table.h
	g++ -c Table.cpp

Random.o: Random.cpp Random.h Pager.h
	g++ -c Random.cpp