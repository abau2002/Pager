// FILE: Pager.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Driver for 
//
// 
//

#include "Pager.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main(int argc, char **argv){
	ifstream inputFile;
	string fileLine;
	char type[INPUT_MAX], frames[INPUT_MAX], fileName[INPUT_MAX], pages[INPUT_MAX], frameSize[INPUT_MAX];
	int fileIndex,id;

	strcpy(type,DEFAULT_TYPE);
	strcpy(frames,DEFAULT_FRAMES);
	strcpy(fileName,DEFAULT_FILE);
	strcpy(pages,DEFAULT_PAGES);
	strcpy(frameSize,DEFAULT_SIZE);

	fileIndex = commandErrorCheck(argc, argv);
	if(fileIndex == -1){
		exit(1);
	}
	else if(fileIndex){
		strcpy(fileName,argv[fileIndex]);
	}

	for(int i=1;i<argc;i++){
		if(!strcmp(argv[i],TYPE)){
			strcpy(type,argv[i+1]);
		}
		else if(!strcmp(argv[i],PAGES)){
			strcpy(pages,argv[i+1]);
		}
		else if(!strcmp(argv[i],FRAMES)){			
			strcpy(frames,argv[i+1]);             
		}
		else if(!strcmp(argv[i],FRAME_SIZE)){
			strcpy(frameSize,argv[i+1]);            
		}
	}

	if(!inputErrorCheck(pages,frames,frameSize)){
		inputFile.open(fileName);
		if(inputFile){
			string fileInput;
			int address;
			inputFile >> fileInput;
			if(idErrorCheck(fileInput)) exit(1);
			id = atoi(fileInput.substr(2,fileInput.length()).c_str());

			inputFile >> fileInput;
		    while(!inputFile.eof()){
		    	address = atoi(fileInput.c_str());
    			if(loadErrorCheck(address,atoi(frameSize),atoi(pages))) exit(1);

    			addresses.push(address);

    			inputFile >> fileInput;
			}
			inputFile.close();
		}
		else{
			cout << "\tERROR: File not opened\n";
			exit(1);
		}
	}
	else{
		exit(1);
	}

	if(!strcmp(type,FIRST_IN_FIRST_OUT)){
		cout << id << " FIFO\n";
	}
	else if(!strcmp(type,LEAST_RECENT_USED)){
		cout << "LRU\n";
	}
	else if(!strcmp(type,RANDOM)){
		cout << "RANDOM\n";
	}
	else if(!strcmp(type,MOST_FREQUENT_USED)){
		cout << "MFU\n";
	}
	cout << fileName << endl;

	return 0;
}

bool inputErrorCheck(string pages, string frames, string frameSize){
	bool error = false;
	if(atoi(pages.c_str()) <= 0){
		cout << "\tERROR: Pages must be a positive number\n";
		error = true;
	}
	else if(atoi(frames.c_str()) <= 0){
		cout << "\tERROR: Frames must be a positive number\n";
		error = true;
	}
	else if(atoi(frameSize.c_str()) <= 0){
		cout << "\tERROR: Frame size must be a positive number\n";
		error = true;
	}
	return error;		
}

int commandErrorCheck(int argc, char** argv){
	bool error = false;
	int fileIndex = 0;
	if(!strcmp(argv[argc-1],TYPE) || !strcmp(argv[argc-1],PAGES) || !strcmp(argv[argc-1],FRAMES) || !strcmp(argv[argc-1],FRAME_SIZE)){
		cout << "\tERROR: " << argv[argc-1] << " requires an input\n";
		error = true;
	}
	else{
		for(int i=1;i<argc;i++){
			// if one of the inputs is not a valid option and does not come after an option with a parameter then error
			if(strcmp(argv[i],TYPE) && strcmp(argv[i],PAGES) && strcmp(argv[i],FRAMES) && strcmp(argv[i],FRAME_SIZE)){
				if(strcmp(argv[i-1],TYPE) && strcmp(argv[i-1],PAGES) && strcmp(argv[i-1],FRAMES) && strcmp(argv[i-1],FRAME_SIZE)){
					if(i!=argc-1){
						cout << "\tERROR: " << argv[i] << " is not a valid option\n";
						error = true;
					}
					else{
						fileIndex = i;
					}
				}
			}
			else if(!strcmp(argv[i],TYPE)){
				if(strcmp(argv[i+1],FIRST_IN_FIRST_OUT) && strcmp(argv[i+1],LEAST_RECENT_USED) && strcmp(argv[i+1],MOST_FREQUENT_USED) && strcmp(argv[i+1],RANDOM)){
					cout << "\tERROR: " << argv[i+1] << " is not a valid type\n";
					error = true;
				}
			}
		}
	}
	if(error){
		return -1;
	}
	return fileIndex;
}

// framesize is in bytes
bool loadErrorCheck(int address,int pageSize, int pages){
    bool error = false;
    // check if address is possible within given frames and size
    if((address/pageSize) > pages){
    	cout << "\tERROR: Address " << address << " cannot exist within " << pages << " " << pageSize << " byte pages\n";
    	error = true;
    }
    return error;
}

bool idErrorCheck(string fileInput){
	bool error = false;
	if(fileInput.find("P_") != 0 || fileInput.length() < 3){
			cout << "\tERROR: Process id is not of form P_#\n";
			error = true;
	}
	else if(atoi(fileInput.substr(2,fileInput.length()).c_str()) < 0){
		cout << "\tERROR: Process id must be a non-negative number\n";
		error = true;
	}
	return error;
}