// FILE: Table.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// 
//

#ifndef TABLE_H
#define TABLE_H

#define MAX_FRAMES 65536

using namespace std;

class Table{
	private:
		struct Entry{
			int page;
			bool valid;
		};

		// inverted page table
		Entry table[MAX_FRAMES];
		int frameCount, pageSize;
	

	public:
		// constructor that fills the table "empty" entries 
		Table(int frames, int frameSize);

		// constructor
		Table();

		// destructor
		~Table();

		// returns the number of a free frame, returns -1 if none found
		int freeFrame();

		// returns frame of given page if it's valid, returns -1 if not found
		int member(int page);

		// updates the given frame to contain the given page
		void load(int frame, int page);

		// returns true if the given frame is valid
		bool valid(int frame);

		// sets the given frame to be valid
		void setValid(int frame);

		// sets the given frame to be invalid
		void setInvalid(int frame);

		// returns the size of the table
		int size();

		// returns the page the given address refers to
		int addressPage(int address);

		// prints out the table
		void print();
};

#endif // TABLE_H