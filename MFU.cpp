// FILE: MFU.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#include "MFU.h"
#include <iostream>

MFU::MFU() {
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

        if (table.valid(page)) {
            pageFrequency[page]++;
            cout << "Incremented frequency of Page " << page << " to " << pageFrequency[page] << endl;
        }

        if (!table.valid(page)) {
            pageFaults++;
            freeFrame = table.freeFrame();
            if (freeFrame != -1) {
                cout << "\tFree frame found: " << freeFrame << endl;
                table.load(page, freeFrame);
                table.setValid(page);
                loadOrder.push_back(page);
                cout << "\tLoaded page " << page << " into frame " << freeFrame << endl;
            } 
			
			else {
                victimFrame = selectVictim(table);
                victimPage = table.findPage(victimFrame);
                cout << "\tVictim page: " << victimPage << " with frequency: " << pageFrequency[victimPage] << ", Frame: " << victimFrame << endl;
                table.setInvalid(victimPage);
                table.load(page, victimFrame);
                table.setValid(page);
                pageFrequency[victimPage] = 0; // resetting frequency of victim page
                cout << "\tReplaced page " << victimPage << " with page " << page << endl;
            }
            pageFrequency[page] = 1; 
        }

        cout << "Current page faults: " << pageFaults << endl;
        cout << "Current load order: ";
        for (int p : loadOrder) {
            cout << p << " ";
        }
        cout << endl;
        cout << "Current page frequencies: ";
        for (int i = 0; i < pageFrequency.size(); ++i) {
            cout << "Page " << i << ": " << pageFrequency[i] << ", ";
        }
        cout << endl << endl;
    }

    return pageFaults;
}

int MFU::selectVictim(Table& table) {
    int maxFrequency = 0;
    int victimPageIndex = -1; 

    // iterate through to find max frequency
    for (int i = 0; i < pageFrequency.size(); ++i) {
        if (pageFrequency[i] > maxFrequency) {
            maxFrequency = pageFrequency[i];
        }
    }

    cout << "Maximum frequency found: " << maxFrequency << endl;

    // iterate through loadOrder to find the first page with the max frequency
    for (int i = 0; i < loadOrder.size(); ++i) {
        int page = loadOrder[i];
        if (pageFrequency[page] == maxFrequency) {
            victimPageIndex = i;
            break;
        }
    }

    if (victimPageIndex != -1) {
        int victimPage = loadOrder[victimPageIndex];
        int victimFrame = table.getFrame(victimPage);
        
        cout << "Victim page: " << victimPage << ", Victim frame: " << victimFrame << endl;

        // shift elements in loadOrder to remove the victim page
        for (int i = victimPageIndex; i < loadOrder.size() - 1; ++i) {
            loadOrder[i] = loadOrder[i + 1];
        }
        loadOrder.pop_back(); 

        return victimFrame;
    } 
	
	else {
        cout << "No victim page found with max frequency." << endl;
    }

    return -1; // returning -1 if no victim is found
}
