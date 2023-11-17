// FILE: LRU.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for LRU that contains all functions needed to page a process using the LRU algorithm
//

#ifndef LRU_H
#define LRU_H

#include "Pager.h"
#include "Table.h"

using namespace std;

class LRU {
public: 
  LRU();
  ~LRU();

  //takes in a queue of addresses and a page table
  //it then conducts page replacement using the least recently used algorithm
  int LRUpager(queue<int>& addresses, Table& table);

private:
  int pageFaults;
  //keeps track of the time that each page is accessed in memory
  vector<int> timestamps;
  
  // takes in the page table
  //it then finds the frame that was accessed with the lowest time value and returns it
  int selectVictim(Table& table);
};

#endif
