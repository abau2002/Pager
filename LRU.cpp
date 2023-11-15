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
        cout << "iteration: " << iteration++ << endl;
        table.print();

        address = addresses.front();
        addresses.pop();
        page = table.addressPage(address);

        if (!table.valid(page)) {
            pageFaults++;
            int freeFrame = table.freeFrame();

            if (freeFrame != -1) {
                cout << "\t\tfreeFrame: " << freeFrame << endl;
                table.load(page, freeFrame);
                table.setValid(page);
                frames.push_back(freeFrame);
                timestamps.push_back(time);
            } else {
                int victimFrame = selectVictim(table, time);
                int victimPage = table.findPage(victimFrame);

                table.setInvalid(victimPage);
                table.load(page, victimFrame);
                table.setValid(page);

                // Remove the victim frame from the frames vector
                for (size_t i = 0; i < frames.size(); ++i) {
                    if (frames[i] == victimFrame) {
                        frames.erase(frames.begin() + i);
                        timestamps.erase(timestamps.begin() + i);
                        break;
                    }
                }
            }
        }
	//update the time if the frame is already loaded
	else {
            for (size_t i = 0; i < frames.size(); ++i) {
                if (frames[i] == table.findPageFrame(page)) {
                    timestamps[i] = time;
                    break;
                }
            }
        }
        time++;
    }
    return pageFaults;
}

int LRU::selectVictim(Table& table, int currentTime) {
    int minTimestamp = INT_MAX;
    int victimFrame = -1;

    for (size_t i = 0; i < frames.size(); ++i) {
        if (timestamps[i] < minTimestamp) {
            minTimestamp = timestamps[i];
            victimFrame = frames[i];
        }
    }
    return victimFrame;
}
