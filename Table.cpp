// FILE: Table.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
//  Implementation for Table that creates the table and contains all functions needed to access 
//  and operate on the table
//

#include "Table.h"
#include <iostream>
using namespace std;

Table::Table(int pages, int frames, int frameSize){
  freeFrames = 0;
  frameCount = frames;
  pageSize = frameSize;
  emptyEntry.frame = -1;
  emptyEntry.valid = false;
  table.assign(pages,emptyEntry);
}

Table::Table(){}

Table::~Table(){}

void Table::print(){
  for(int i=0;i<size();i++) cout << "\tPage " << i << ": " << table.at(i).frame << " " << table.at(i).valid << endl;
}

int Table::addressPage(int address){ return (address/pageSize); }

int Table::freeFrame(){
  if(freeFrames<frameCount) return freeFrames++;
  return -1;
}

int Table::size(){ return table.size(); }

void Table::load(int page, int frame){ table.at(page).frame = frame; }

void Table::setValid(int page){ table.at(page).valid = true; }

void Table::setInvalid(int page){ table.at(page).valid = false; }

bool Table::valid(int page){ return table.at(page).valid; }

int Table::totalFrames(){ return frameCount; }

int Table::findPage(int frame){
  for(int i=0;i<size();i++){
    if(table.at(i).frame==frame && table.at(i).valid) return i;
  }
  return -1;
}

int Table::getFrame(int page){ return table.at(page).frame; }
