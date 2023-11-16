// FILE: LRU.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#include "Pager.h"
#include "Table.h"
#include "LRU.h"
#include <iostream>
#include <climits>
using namespace std;

LRU::LRU() {
  pageFaults = 0;
}

LRU::~LRU() {}

int LRU::LRUpager(queue<int>& addresses, Table& table) {
  int address, page;
  int iteration = 0;
  int time = 0;
  
  while (!addresses.empty()) {
    
    //print the table before doing anything
    cout << "iteration: " << iteration++ << endl;
    table.print();
    
    address = addresses.front();
    addresses.pop();
    page = table.addressPage(address);
    
    // if page size is bigger than vector size resize until timestamps is greater 
    if (page >= timestamps.size()) {
      timestamps.resize(page + 1, 0);
    }
    
    if (!table.valid(page)) {
      pageFaults++;
      int freeFrame = table.freeFrame();
      
      if (freeFrame != -1) {
	cout << "\t\tfreeFrame: " << freeFrame << endl;
	table.load(page, freeFrame);
	table.setValid(page);
      }
      //conduct page replacement 
      else {
	int victimFrame = selectVictim(table);
	int victimPage = table.findPage(victimFrame);
	std::cout << "\t\tvictimPage: " << victimPage << " with timestamp: " << timestamps[victimPage] << std::endl;
	table.setInvalid(victimPage);
	table.load(page, victimFrame);
	table.setValid(page);
	//reset the time of victim to largest possible value so that we get a new victim next time
	timestamps[victimPage] = INT_MAX;
      }
    }
    
    //update the time for the page that was accessed
    for (int i = 0; i < timestamps.size(); i++) {
      if (table.valid(i) && i == page) {
	timestamps[i] = iteration;
	break;
      }
    }
    std::cout << " pageFaults: " << pageFaults << std::endl << std::endl;
  }
  return pageFaults;
}

// takes in the page table
//it then finds the frame that was accessed with the lowest time value and returns it
int LRU::selectVictim(Table& table) {
  int minTimestamp = INT_MAX;
  int victimPage = -1;
  int victimFrame = -1;
  
  // iterate through the timestamps vector until we find the page with the lowest time value
  // we then will set this as our victim
  for (int i = 0; i < timestamps.size(); i++) {
    if (timestamps[i] < minTimestamp && table.valid(i)) {
      minTimestamp = timestamps[i];
      victimPage = i;
    }
  }
  
  // Iterate through frames to find the frame for the least recently used page
  if (victimPage != -1) {
    for (int i = 0; i < table.size(); i++) {
      if (table.valid(i) && i == victimPage) {
	victimFrame = table.getFrame(i);
	break;
      }
    }
  }
  
  return victimFrame;
}
