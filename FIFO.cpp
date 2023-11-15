// FILE: FIFO.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#include "Table.h"
#include "FIFO.h"
#include <queue>
#include <iostream>

using namespace std;

FIFO::FIFO(){
	pageFaults = 0;
}
FIFO::~FIFO(){}

int FIFO::fifoPager(queue<int>& addresses, Table& table){
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
				pages.push(page);
				table.load(page,freeFrame);
				table.setValid(page);
			}
			// page replacement must be conducted
			else{	
				victimPage = selectVictim();
				table.setInvalid(victimPage);
				cout << "\t\tvictimPage: " << victimPage << endl;
				
				pages.pop();
				pages.push(page);
				
				table.load(page,table.getFrame(victimPage));
				table.setValid(page);
			}
		}
		cout << "pageFaults: " << pageFaults << endl << endl;
	}
	return pageFaults;
}

int FIFO::selectVictim(){
	return pages.front();
}
