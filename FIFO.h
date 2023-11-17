// FILE: FIFO.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for FIFO that contains all functions needed to page a process using the FIFO algorithm
//

#ifndef FIFO_H
#define FIFO_H

#include "Pager.h"
#include "Table.h"
#include <queue>
using namespace std;

class FIFO{
public:
  
  FIFO();

  ~FIFO();
  
  // pages for the given queue of addresses using the given Table instance using the first in first out algorithm
  int fifoPager(queue<int>& addresses, Table& table);
  
private:
  int pageFaults;
  queue<int> pages;
  
  // returns the first page in the pages queue
  int selectVictim();
};

#endif // FIFO_H
