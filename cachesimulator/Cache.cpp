#include "Cache.h"


namespace G {
	Cache::Cache(int& C, int&b, int&N) {
		capacity 	= C;
		block_size	= b;
		assoc		= N;
		
		createCache();
	}
	void Cache::createCache() {
		blocks = C/b;
		sets = blocks/N;
		offset = log(block_size)/log(2);
		index = log(sets)/log(2);
	}
	
	
}
