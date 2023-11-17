// FILE: FIFO.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Implementation for FIFO that contains all functions needed to page a process using the FIFO algorithm
//

#include "Table.h"
#include "FIFO.h"
#include <queue>
#include <iostream>

using namespace std;

FIFO::FIFO(){
  pageFaults = 0;
}
FIFO::~FIFO(){}

int FIFO::fifoPager(queue<int>& addresses, Table& table){
  int freeFrame, address, victimFrame, victimPage, page; 
  int iteration = 0;
  while(!addresses.empty()){
    // prints all contents inside the table before any manipulation is done 
    cout << "iteration: " << iteration++ << endl;
    table.print();
    
    //push all addresses to its specific page
    address = addresses.front();
    addresses.pop();
    page = table.addressPage(address);

    //if valid bit is not set increase page faults and find a free frame
    if(!table.valid(page)){
      pageFaults++;
      freeFrame = table.freeFrame();
      
      //if frame is empty put page there 
      if(freeFrame != -1){
	cout << "\t\tfreeFrame: " << freeFrame << endl;
	pages.push(page);
	table.load(page,freeFrame);
	table.setValid(page);
      }
      
      // page replacement must be conducted if no frames are declared
      // we find the victim by getting the first page that was loaded in and removing it
      // we then can load the page we wanted to load
      else{	
	victimPage = selectVictim();
	table.setInvalid(victimPage);
	cout << "\t\tvictimPage: " << victimPage << endl;
	
	pages.pop();
	pages.push(page);
	
	table.load(page,table.getFrame(victimPage));
	table.setValid(page);
      }
    }
    cout << "pageFaults: " << pageFaults << endl << endl;
	}
  return pageFaults;
}

int FIFO::selectVictim(){
  return pages.front();
}
