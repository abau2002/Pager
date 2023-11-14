// FILE: FIFO.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#ifndef FIFO_H
#define FIFO_H

#include "Pager.h"
#include "Table.h"
#include <queue>
using namespace std;

class FIFO{
	public:
		// constructor
		FIFO();

		// destructor
		~FIFO();

		// pages for the given queue of addresses using the given Table instance using the first in first out algorithm
		int fifoPager(queue<int>& addresses, Table& table);

	private:
		int pageFaults;
		queue<int> frames;

		// returns the first frame in the frames queue
		int selectVictimFrame(Table& table);
};

#endif // FIFO_H