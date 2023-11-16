# FILE: makefile
# A Bautista, B Franco, E Mora
# OS, Fall 2023, Transy U
#
# makefile for Group 3 Pager
#

pager: Pager.o Table.o Random.o FIFO.o MFU.o LRU.o
	g++ Pager.o Table.o Random.o FIFO.o MFU.o LRU.o -o pager

Pager.o: Pager.cpp Pager.h Table.h Random.h FIFO.h LRU.h MFU.h
	g++ -c Pager.cpp

Table.o: Table.cpp Table.h
	g++ -c Table.cpp

Random.o: Random.cpp Random.h Table.h
	g++ -c Random.cpp

LRU.o: LRU.cpp Table.h LRU.h
	g++ -c LRU.cpp

MFU.o: MFU.cpp Table.h MFU.h
	g++ -c MFU.cpp

FIFO.o: FIFO.cpp Table.h FIFO.h
	g++ -c FIFO.cpp
