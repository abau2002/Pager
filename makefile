# FILE: makefile

pager: Pager.o Table.o Random.o FIFO.o
	g++ Pager.o Table.o Random.o FIFO.o -o pager

Pager.o: Pager.cpp Pager.h Table.h Random.h FIFO.h
	g++ -c Pager.cpp

Table.o: Table.cpp Table.h
	g++ -c Table.cpp

Random.o: Random.cpp Random.h Table.h
	g++ -c Random.cpp

FIFO.o: FIFO.cpp Table.h FIFO.h
	g++ -c FIFO.cpp