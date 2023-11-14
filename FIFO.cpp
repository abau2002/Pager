// FILE: FIFO.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#include "Pager.h"
#include "Table.h"
#include "FIFO.h"
#include <queue>
#include <iostream>

using namespace std;

FIFO::FIFO(){
	pageFaults = 0;
}
FIFO::~FIFO(){}

void FIFO::fifoPager(queue<int>& addresses, Table& table){
	int freeFrame, address, victimFrame, victimPage, page; 
	int iteration = 0;
	while(!addresses.empty()){
		cout << "iteration: " << iteration++ << endl;
		table.print();

		address = addresses.front();
		addresses.pop();
		page = table.addressPage(address);
		if(!table.valid(page)){
			pageFaults++;
			freeFrame = table.freeFrame();
			if(freeFrame != -1){
				cout << "\t\tfreeFrame: " << freeFrame << endl;
				frames.push(freeFrame);
				table.load(page,freeFrame);
				table.setValid(page);
			}
			// page replacement must be conducted
			else{
				victimFrame = selectVictimFrame(table);
				victimPage = table.findPage(victimFrame);
				frames.pop();
				frames.push(victimFrame);
				cout << "\t\tvictimPage: " << victimPage << endl;
				table.setInvalid(victimPage);
				table.load(page,victimFrame);
				table.setValid(page);
			}
		}
		cout << "pageFaults: " << pageFaults << endl << endl;
	}
}

int FIFO::selectVictimFrame(Table& table){
	return frames.front();
}