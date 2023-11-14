// FILE: Random.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#include "Random.h"
#include "Table.h"
#include <iostream>

using namespace std;

Random::Random(){
	pageFaults = 0;
	srand(time(NULL));
}

Random::~Random(){}

void Random::randomPager(queue<int>& addresses,Table& table){
	int freeFrame, address, victimPage, victimFrame, page; 
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
				table.load(page,freeFrame);
				table.setValid(page);
			}
			// page replacement must be conducted
			else{
				victimFrame = selectVictimFrame(table);
				victimPage = table.findPage(victimFrame);
				cout << "\t\tvictimPage: " << victimPage << endl;
				table.setInvalid(victimPage);
				table.load(page,victimFrame);
				table.setValid(page);
			}
		}
		cout << "pageFaults: " << pageFaults << endl << endl;
	}
}

int Random::selectVictimFrame(Table& table){
	return rand()%table.totalFrames();
}