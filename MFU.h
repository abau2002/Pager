// FILE: MFU.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for MFU that contains all functions needed to page a process using the MFU algorithm
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
  MFU();
  ~MFU();
  
  int mfuPager(queue<int>& addresses, Table& table); // pager for MFU that takes in a queue of addresses and a table

private:
  int pageFaults; // tracks number of page faults
  vector<int> pageFrequency; // vector to track the frequency of each page
  vector<int> loadOrder; //vector used for FIFO tiebreaker if two or more pages have the same frequency
  
  int selectVictim(Table& table); // selects the victim frame from the page table
};

#endif // MFU_H
