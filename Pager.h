// FILE: Pager.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for Pager that contains all the definitions and error checking needed to ensure input is valid 
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
#define MAX_FRAMES 65536

// checks if input numbers are valid and returns false if no errors found
bool inputErrorCheck(string pages, string frames, string frameSize);

// checks if command line set up is valid and returns false if no issues found
int commandErrorCheck(int argc, char**argv);

// checks if the memory addresses are possible within given framesize and pages, returns false if no errors found
bool loadErrorCheck(int address,int pageSize, int pages);

// checks if the process id is valid and in the proper format, returns false if no issues found
bool idErrorCheck(string fileInput);

// checks if any options have been repeated, returns false if no repeats found
bool repeatErrorCheck(int typeOption, int pageOption, int frameOption, int sizeOption);

#endif // PAGER_H
