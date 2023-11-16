// FILE: MFU.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#include "MFU.h"
#include <iostream>

MFU::MFU(){
  pageFaults = 0;
}

MFU::~MFU() {
}

int MFU::mfuPager(queue<int>& addresses, Table& table) {
  int address, page, freeFrame, victimPage, victimFrame;
  int iteration = 0;
  
  while (!addresses.empty()) {
    cout << "Iteration: " << iteration++ << endl;
    table.print();
    
    address = addresses.front();
    addresses.pop();
    page = table.addressPage(address);
    
    if (page >= pageFrequency.size()) {
      pageFrequency.resize(page + 1, 0);
    }
    
    if (!table.valid(page)) {
      pageFaults++;
      freeFrame = table.freeFrame();
      if (freeFrame != -1) {
	cout << "\t\tfreeFrame: " << freeFrame << endl;
	table.load(page, freeFrame);
	table.setValid(page);
      } 
      
      // no free frame, must find victim and replace it
      else {
	victimFrame = selectVictim(table);
	victimPage = table.findPage(victimFrame);
	cout << "\t\tvictimPage: " << victimPage << " with frequency: " << pageFrequency[victimPage] << endl;
	table.setInvalid(victimPage);
	table.load(page, table.getFrame(victimPage));
	table.setValid(page);
	pageFrequency[victimPage] = 0;
      }
    }
    
    pageFrequency[page]++;
    cout << " pageFaults: " << pageFaults << endl << endl;
  }
  
  return pageFaults;
}

int MFU::selectVictim(Table& table) {
  int maxFrequency = 0;
  int victimPage = -1;
  int victimFrame = -1;
  
  // iterate through to find highest frequency
  for (int i = 0; i < pageFrequency.size(); i++) {
    if (pageFrequency[i] > maxFrequency) {
      maxFrequency = pageFrequency[i];
      victimPage = i;
    }
  }
  
  // iterate through frames to find the relative frame for highest frequency
  if (victimPage != -1) {
    for (int i = 0; i < table.size(); i++) {
      if (table.valid(i) && i == victimPage) {  // Check if the page is valid and matches victimPage
	victimFrame = table.getFrame(i);  // Get the frame number for the victimPage
	break;
      }
    }
  }
  
  
  return victimFrame;
}

