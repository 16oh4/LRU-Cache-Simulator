#ifndef CACHE_H
#define CACHE_H

#include <cstdint>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "Set.h"
#include "Block.h"

using namespace std;

namespace G 
{
struct mem_address {
	int64_t address;
	
};

class Cache {

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
		
	public:
		/*Constructor and Destructor*/
		Cache(double& C, double& b, double& N);
		Cache(int& C, int& b, int& N);
		~Cache();
		
		void createCache();
		void readConfig();
		
		
		
	//Cache(cache_size, block_size, set_assoc, replacement_policy);	//{constructor of the cache class}
};
}

#endif
