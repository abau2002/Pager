// FILE: Random.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#include "Random.h"
#include "Pager.h"
#include <iostream>

using namespace std;

Random::Random(){
	pageFaults = 0;
	srand(time(NULL));
}

Random::~Random(){}

void Random::randomPager(queue<int>& addresses,Table& table){
	int freeFrame, address, victimFrame, page; 
	int iteration = 0;
	while(!empty(addresses)){
		cout << "iteration: " << iteration++ << endl;
		table.print();

		address = get(addresses);
		pop(addresses);
		page = table.addressPage(address);
		if(!table.member(page)){
			pageFaults++;
			freeFrame = table.freeFrame();
			if(freeFrame != -1){
				cout << "\t\tfreeFrame: " << freeFrame << endl;
				table.load(freeFrame,page);
				table.setValid(freeFrame);
			}
			// page replacement must be conducted
			else{
				victimFrame = selectVictim(table);
				cout << "\t\tvictimFrame: " << victimFrame << endl;
				table.setInvalid(victimFrame);
				table.load(victimFrame,page);
				table.setValid(victimFrame);
			}
		}
		cout << "pageFaults: " << pageFaults << endl << endl;
	}
}

int Random::selectVictim(Table& table){
	return rand()%table.size();
}