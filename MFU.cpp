// FILE: MFU.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Implementation for MFU that contains all functions needed to page a process using the MFU algorithm
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
        cout << "iteration: " << iteration++ << endl;
        table.print();

        address = addresses.front();
        addresses.pop();
        page = table.addressPage(address);

        if (page >= pageFrequency.size()) {
            pageFrequency.resize(page + 1, 0);
        }

        if (table.valid(page)) {
            pageFrequency[page]++;
        }

        if (!table.valid(page)) {
            pageFaults++;
            freeFrame = table.freeFrame();
            if (freeFrame != -1) {
                cout << "\t\tfreeFrame: " << freeFrame << endl;
                table.load(page, freeFrame);
                table.setValid(page);
                loadOrder.push_back(page);
            } 
			
			else {
                victimFrame = selectVictim(table);

                // if there are no victims left, print current page faults and break loop
                if (victimFrame == -1) {
                    cout << "pageFaults: " << pageFaults << endl << endl;
                    break; 
                }

                victimPage = table.findPage(victimFrame);
                cout << "\t\tVictim page: " << victimPage << " with frequency: " << pageFrequency[victimPage] << endl;
                table.setInvalid(victimPage);
                table.load(page, victimFrame);
                table.setValid(page);
                pageFrequency[victimPage] = 0; // resetting frequency of victim page
            }
            pageFrequency[page] = 1; 
        }
    cout << "pageFaults: " << pageFaults << endl << endl;
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

    if (loadOrder.empty()) {
        return -1; // No victim page to evict
    }

    for (int i = 0; i < loadOrder.size(); ++i) {
        int page = loadOrder[i];
        if (page < pageFrequency.size() && pageFrequency[page] == maxFrequency) {
            victimPageIndex = i;
            break;
        }
    }

    if (victimPageIndex != -1) {
        int victimPage = loadOrder[victimPageIndex];
        int victimFrame = table.getFrame(victimPage);

        // shift elements in loadOrder to remove the victim page
        for (int i = victimPageIndex; i < loadOrder.size() - 1; ++i) {
            loadOrder[i] = loadOrder[i + 1];
        }

        loadOrder.pop_back(); 

        return victimFrame;
    } 
    return -1; // returning -1 if no victim is found
}