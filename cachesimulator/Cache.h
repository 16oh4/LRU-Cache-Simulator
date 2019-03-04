#ifndef CACHE_H
#define CACHE_H

#include <cstdint>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <bitset>
#include <sstream>
#include <stdio.h>
#include <unordered_map>
#include <list>
#include <algorithm> //for finding in a list

#include "Set.h"
#include "Block.h"

using namespace std;

namespace G 
{
class Cache {

	typedef bitset<32> bits;
	
	struct mem_address 
	{
		bits mem;
		bits tag;
		bits index;
		bits offset;
	};
	
//	typedef unordered_map<mem_address, int> entry;
	typedef mem_address* entry;
	typedef bits tagentry;
	
	private:
		/*User input values*/
		int capacity;
		int block_size;
		int assoc;
		
		/*Calculated values*/
		int blocks;
		int sets;
		int offset;
		int index;
		int tag;
		int memoryLength;
		
		/*Results*/
		int hits;
		int misses;
		
		/*LRU Implementation*/
		int blocksfilled;

//		vector<list<entry>> setVector;
//		vector<list<entry>::iterator> it;
		vector<list<tagentry>> tagCache;
		
		vector<list<tagentry>::iterator> tagIt;
		unordered_map<bits, mem_address*> mapCache;
		
		/*Cache storage*/
		vector<bits> memory;		//Stores the entire memory from example.trc
		
		vector<bits> tags;			//Stores the tag bits as a bitset
		vector<int> intTags;		//Stores the tag bits as ints
		
		vector<bits> indexes;		//Stores the index bits as a bitset
		vector<int> intIndexes;		//Stores the index bits as ints
		
		vector<bits> offsets;		//Stores the offset bits as a bitset
		vector<int> intOffsets;		//Stores offset bits as ints
		
		mem_address* bank;			//Array of structures representing each memory address
		mem_address* bank2;
		
		/*Member functions*/
		int bitsToInt(bits& h);
		
		bits getTag(bits& h);
		bits getIndex(bits& h);
		bits getOffset(bits& h);
		bits hexToBin(string& s);
		
		void createCache();
		
		/*LRU Functions*/
		void checkEntry(mem_address& adr);
//		void deleteMemEntry(mem_address*& adr, list<entry>::iterator*& it, list<entry>*& set);
		void deleteMemEntry(mem_address*& adr);
		void printMemAdr(mem_address& adr);
		void printSet(list<entry>& l);
		void checkEntry(bits& tag);
		void printSet(list<tagentry>& l);
		
	public:
		/*Constructor and Destructor*/
		Cache(int& C, int& b, int& N);
		~Cache();
		
		
		void readMemory();
		void testMem();
		
		
		
	//Cache(cache_size, block_size, set_assoc, replacement_policy);	//{constructor of the cache class}
};
}

#endif
