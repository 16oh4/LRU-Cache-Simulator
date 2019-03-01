#ifndef CACHE_H
#define CACHE_H

#include <cstdint>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <bitset>
#include <sstream>

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
	
	};
	
	
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
		
		vector<bits> memory;
		vector<bits> tags;
		vector<int> intTags;
		
		int bitsToInt(bits h);
		
		bits getTag(bits h);
		bits hexToBin(string s);
		void createCache();
		
	public:
		/*Constructor and Destructor*/
		Cache(int& C, int& b, int& N);
		~Cache();
		
		
		void readMemory();
		
		
		
	//Cache(cache_size, block_size, set_assoc, replacement_policy);	//{constructor of the cache class}
};
}

#endif
