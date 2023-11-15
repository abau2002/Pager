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
  
  void LRUpager(queue<int>& addresses, Table& table);

private:
  int pageFaults;
  vector<int> frames;
  vector<int> timestamps;
  // returns the frame that was last used in the frames stack
  int selectVictim(Table& table);
};

#endif
