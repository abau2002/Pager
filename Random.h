// FILE: Random.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for Random that contains all functions needed to page a process using the Random algorithm
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
  int randomPager(queue<int>& addresses,Table& table);
  
private:
  int pageFaults;
  
  // returns a random frame in the table
  int selectVictim(Table& table);
};

#endif // RANDOM_H
