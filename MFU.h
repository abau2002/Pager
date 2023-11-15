// FILE: MFU.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#ifndef MFU_H
#define MFU_H

#include "Pager.h"
#include "Table.h"
#include <vector>
#include <queue>

using namespace std;

class MFU {
	public:
		MFU(); //constructor
		~MFU(); //destructor

		int mfuPager(queue<int>& addresses, Table& table); // pager for MFU that takes in a queue of addresses and a table

	private:
		int pageFaults; // tracks number of page faults
		vector<int> pageFrequency; // vector to track the frequency of each page

		int selectVictim(Table& table); // selects the victim frame from the page table
};

#endif // MFU_H
