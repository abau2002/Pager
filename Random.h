// FILE: Random.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
//
// 
//

#ifndef RANDOM_H
#define RANDOM_H

#include "Table.h"
#include <stdlib.h>
#include <time.h>
#include <queue>

using namespace std;

class Random{
	public:
		// constructor
		Random();

		// destructor
		~Random();

		// pages for the given queue of addresses using the given Table instance using the random algorithm
		void randomPager(queue<int>& addresses,Table& table);
		
	private:
		int pageFaults;

		// returns a random frame in the table
		int selectVictimFrame(Table& table);
};

#endif // RANDOM_H