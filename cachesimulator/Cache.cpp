#include "Cache.h"


namespace G {
	Cache::Cache(double& C, double&b, double&N) {
		capacity 	= C;
		block_size	= b;
		assoc		= N;
		
		
		createCache();
		cout << "Capacity: " << C << endl;
		cout << "Block Size: " << b << endl;
		cout << "Associativity: " << N << endl;
		cout << "Total blocks: " << blocks << endl;
		cout << "Total sets: " << sets << endl;
		cout << "Offset bits: " << offset << endl;
		cout << "Index bits: " << index << endl;
		cout << "Tag bits: " << tag << endl;
	}
	
	Cache::~Cache() {
		
	}
	
	Cache::Cache(int& C, int&b, int&N) {
		capacity 	= C;
		block_size	= b;
		assoc		= N;
		
		
		createCache();
		cout << "Capacity: " << C << endl;
		cout << "Block Size: " << b << endl;
		cout << "Associativity: " << N << endl;
		cout << "Total blocks: " << blocks << endl;
		cout << "Total sets: " << sets << endl;
		cout << "Offset bits: " << offset << endl;
		cout << "Index bits: " << index << endl;
		cout << "Tag bits: " << tag << endl;
	}
	
	void Cache::createCache() {
		cout << "Dividing " << capacity << " by " << block_size << endl;
		blocks = capacity/block_size;
		
		cout << "Blocks: " << blocks << endl;
		sets = blocks/assoc;
		offset = log(block_size)/log(2);
		index = log(sets)/log(2);
		tag = 32 - offset - index;
	}
	
	
	
}
