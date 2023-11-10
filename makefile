# FILE: makefile

pager: Pager.o
	g++ Pager.o -o pager

Pager.o: Pager.cpp Pager.h
	g++ -c Pager.cpp