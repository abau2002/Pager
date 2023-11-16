// FILE: LRU.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
//
// 
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
  
  int LRUpager(queue<int>& addresses, Table& table);

private:
  int pageFaults;
  //keeps track of the time that each page is accessed in memory
  vector<int> timestamps;
  
  //takes in the page table as a parameter
  // returns the frame that was least recently used in the frames stack
  int selectVictim(Table& table);
};

#endif
