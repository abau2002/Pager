// FILE: Pager.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
//
// 
//

#ifndef PAGER_H
#define PAGER_H

#include <string>
#include <limits.h>
#include <queue>

using namespace std;

#define INPUT_MAX CHAR_MAX
#define TYPE "--type"
#define FRAMES "--frames"
#define FRAME_SIZE "--framesize"
#define PAGES "--pages"
#define FIRST_IN_FIRST_OUT "FIFO"
#define LEAST_RECENT_USED "LRU"
#define MOST_FREQUENT_USED "MFU"
#define RANDOM "RANDOM"
#define DEFAULT_TYPE FIRST_IN_FIRST_OUT
#define DEFAULT_FRAMES "3"
#define DEFAULT_PAGES "8"
#define DEFAULT_SIZE "512"
#define DEFAULT_FILE "pager.in"

// checks if input is valid and returns false if no errors found
bool inputErrorCheck(string pages, string frames, string frameSize);

// checks if command line set up is valid and returns false if no issues found
int commandErrorCheck(int argc, char**argv);

// checks if the values are valid, returns false if no errors found
bool loadErrorCheck(int address,int pageSize, int pages);

// checks if the process id is valid and in the proper format, returns false if no issues found
bool idErrorCheck(string fileInput);

// pushes the given address into the end of the given queue
void push(int address, queue<int>& queue);

// pops the first element of the queue
void pop(queue<int>& queue);

// returns the first element of the queue
int get(queue<int>& queue);

// returns true if the queue is empty
bool empty(queue<int>& queue);

// returns the size of the given queue
int size(queue<int>& queue);

#endif // PAGER_H