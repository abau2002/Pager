// FILE: Table.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#ifndef TABLE_H
#define TABLE_H

#include <vector>
using namespace std;

class Table{
	private:
		struct Entry{
			int frame;
			bool valid;
		};
		vector<Entry> table;
		Entry emptyEntry;
		int pageSize, frameCount, freeFrames;

	public:
		// constructor that fills the table "empty" entries 
		Table(int pages, int frames, int frameSize);

		// constructor
		Table();

		// destructor
		~Table();

		// prints out the table
		void print();

		// returns the page the given address refers to
		int addressPage(int address);

		// updates the given page to be in given frame
		void load(int page, int frame);

		// returns the number of a free frame, returns -1 if none available
		int freeFrame();

		// returns the size of the table, equivalent to number of pages
		int size();

		// sets the given page to be valid
		void setValid(int page);

		// sets the given page to be invalid
		void setInvalid(int page);

		// returns true if the given page is valid
		bool valid(int page);

		// returns frameCount
		int totalFrames();

		// finds the valid page in the given frame
		int findPage(int frame);
};

#endif // TABLE_H