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
	int freeFrame, address, victimFrame, page; 
	int iteration = 0;
	while(!empty(addresses)){
		cout << "iteration: " << iteration++ << endl;
		table.print();

		address = get(addresses);
		pop(addresses);
		page = table.addressPage(address);
		if(table.member(page) == -1){
			pageFaults++;
			freeFrame = table.freeFrame();
			if(freeFrame != -1){
				cout << "\t\tfreeFrame: " << freeFrame << endl;
				push(page,pages);
				table.load(freeFrame,page);
				table.setValid(freeFrame);
			}
			// page replacement must be conducted
			else{
				victimFrame = selectVictim(table);
				pop(pages);
				push(page,pages);
				cout << "\t\tvictimFrame: " << victimFrame << endl;
				table.setInvalid(victimFrame);
				table.load(victimFrame,page);
				table.setValid(victimFrame);
			}
		}
		cout << "pageFaults: " << pageFaults << endl << endl;
	}
}

int FIFO::selectVictim(Table& table){
	return table.member(get(pages));
}