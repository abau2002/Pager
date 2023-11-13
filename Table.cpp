// FILE: Table.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
//
// 
//

#include "Table.h"
#include <iostream>
using namespace std;

Table::Table(int frames,int frameSize){
	frameCount = frames;
	pageSize = frameSize;
	for(int i=0;i<frameCount;i++){
		table[i].page = -1;
		table[i].valid = false;
	}
}

Table::Table(){}

Table::~Table(){}

int Table::freeFrame(){
	for(int i=0;i<frameCount;i++){
		if(!table[i].valid){
			return i;
		}
	}
	return -1;
}

int Table::member(int page){
	for(int i=0;i<frameCount;i++){
		if(table[i].page==page && table[i].valid==true){
			return i;
		}
	}
	return -1;
}

void Table::load(int frame, int page){
	table[frame].page = page;
}

bool Table::valid(int frame){
	return table[frame].valid;
}

void Table::setValid(int frame){
	table[frame].valid = true;
}

void Table::setInvalid(int frame){
	table[frame].valid = false;
}

int Table::size(){
	return frameCount;
}

int Table::addressPage(int address){
	return (address/pageSize);
}

void Table::print(){
	for(int i=0;i<frameCount;i++){
		cout << "\tFrame " << i << ": " << table[i].page << " " << table[i].valid << endl;
	}
}