#include "Cache.h"


namespace G 
{	
	typedef bitset<32> bits;
	
	Cache::Cache(int& C, int&b, int&N) 
	{
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
		free(bank);
		
//		int h =0;
//		for(int i=0; i<setVector.size(); i++)
//		{
//			for(list<entry>::iterator j= setVector.at(i).begin(); j != setVector.at(i).end(); j++)
//			{
//				h++;
//				cout << i << ":" << h << endl;
//				cout << *j << endl;
////				if(!(*j == nullptr))
////				{
////					cout << "DELETING: " << (*j)->tag << endl;
////					delete *j;
////					*j = nullptr;
////				}
//				
//				
//			}
//		}
//		delete bank2;
	}
	
	void Cache::testMem() 
	{
		/*Allocate buckets for total memory addresses into array of structs
			Will allocate 16 bytes per bucket, for 4 bitsets per struct
			Total memory allocated = 695521 * 16 bytes
		*/
		bank = (mem_address*)malloc(sizeof(mem_address)*memoryLength);
//		bank2 = new mem_address[memoryLength];

//		cout << memory.at(memoryLength-1).to_string() << endl;
		
//		cout << &bank[0] << endl;
//		cout << &bank[1] << endl; 
//		cout << sizeof(bank[1]) << endl;
		

		for(int i=0; i<memoryLength; i++)
		{
			bank[i].mem 	= memory.at(i);
			bank[i].tag 	= getTag(memory.at(i));
			bank[i].index 	= getIndex(memory.at(i));
			bank[i].offset 	= getOffset(memory.at(i));
			
//			if(i == memoryLength - 1)
//			{
//				printMemAdr(bank[i]);		
//			}

		}
		
		pair<bits,mem_address*> insertion; //for inserting into hashmap
		
		/*BEGIN CACHE OPERATION*/
		int i=0;
		for(; i<memoryLength; i++)
		{
//			cout << "__________________Checking______________" << endl;
			
//			printMemAdr(bank[i]);
			
//			insertion = make_pair(bank[i].tag, &bank[i]);
//			
//			mapCache.insert(insertion);
//			
//			cout << "MEM INSERTED: " <<mapCache.at(insertion.first)->mem << endl;
//			checkEntry(bank[i].tag);
			checkEntry(bank[i]);
//			cout << "________END CHECKING____________________" << endl;
		}
		
		cout << "NUM ACCESSES " << i << endl;
		cout << "HITS: " << hits << endl;
		cout << "MISSES: " << misses << endl;
		cout << "HIT RATE: " << (double)(hits)/(double)(i) << endl;
		
		
	}
	void Cache::checkEntry(bits& tag)
	{
		
	}
	void Cache::printMemAdr(mem_address& adr)
	{
		cout << "MEM:\t" << adr.mem <<
				"\nTAG:\t" << adr.tag << 
				"\nINDEX:\t" << adr.index << 
				"\nOFFSET:\t" << adr.offset << endl;
	}
	
	void Cache::checkEntry(mem_address& adr)
	{
		int currentIndex 					= bitsToInt(adr.index);			//grab our current set index from the cache

		list<tagentry>* currentSet 			= &tagCache.at(currentIndex); 	//make a pointer for the set an n index
		
		list<tagentry>::iterator* currentIt = &tagIt.at(currentIndex);		//iterator for the nth set
		
		list<tagentry>::iterator search;
		
//		cout << "Set size: " << currentSet->size() << endl;
		
		*currentIt = find(currentSet->begin(), currentSet->end(), adr.tag);	//search for the tag in the set at n index
		
		/*Cache FULL*/
		if(currentSet->size() == assoc)
		{
			/*Cache MISS*/
			if( (*currentIt == currentSet->end()) )
			{
//				cout << "------->MISS, will replace at LRU" << endl;
				misses++;
				
				*currentIt = currentSet->begin();	//set iterator pointer to LRU
				currentSet->erase(*currentIt);		//erase LRU
				currentSet->push_back(adr.tag);		//push back the tag as the new MRU
				
				/*Calculate position for iterator*/
				*currentIt = currentSet->begin();
				advance(*currentIt, distance(*currentIt, currentSet->end())-1); //advance to the last placement
				
//				cout << "Pushed " << **currentIt << endl;
				
	//			cout << "PUSHED IN: " <<  << endl;
			}
			
			/*Cache HIT*/
			else
			{
//				cout << "------->ITS A HIT!!!" << endl;
				hits++;
				
				currentSet->erase(*currentIt);
				
				currentSet->push_back(adr.tag);
				
				/*Calculate position for iterator*/
				*currentIt = currentSet->begin();
				advance(*currentIt, distance(*currentIt, currentSet->end())-1); //advance to the last placement
				
//				cout << "Pushed " << **currentIt << endl;
				
			}
		}
		/*Cache NOT FULL*/
		else if ( (currentSet->size() != 0) && (currentSet->size() < assoc))
		{
			/*Cache MISS*/
			if( (*currentIt == currentSet->end()) )
			{
//				cout << "------->Compulsory Miss GG" << endl;
				misses++;
				
				currentSet->push_back(adr.tag);
				
				/*Calculate position for iterator*/
				*currentIt = currentSet->begin();
				advance(*currentIt, distance(*currentIt, currentSet->end())-1); //advance to the last placement
				
				
				
//				cout << "Pushed " << **currentIt << endl; //print the inserted tag
			}
			/*Cache HIT*/
			else
			{
//				cout << "------->Cache hit, not empty" << endl;
				hits++;
				
				currentSet->erase(*currentIt);	//erase spot to move to MRU now

				currentSet->push_back(adr.tag);
//				*currentIt = currentSet->end();	//set iterator to the MRU position
				
//				cout << "Pushed " << **currentIt << endl; //print the inserted tag
				
			}
		}
		/*Cache NEW*/
		else if( (currentSet->size() == 0) && (*currentIt == currentSet->end()) )
		{
//			cout << "------->Compulsory Miss" << endl;
			misses++;
			
			currentSet->push_back(adr.tag);		//append to the back (MRU)
			*currentIt = currentSet->begin();	//set iterator to this position since set is NEW
			
//			cout << "Pushed " << **currentIt << endl; //print the inserted tag
//				printMemAdr(adr);
		}
		
		
		/*Check if iterator does not point to the same tag*/
		if( (**currentIt) != adr.tag)
		{
			cout << "ERROR @ " << currentIndex << " mem:" << endl;
			printMemAdr(adr);
			printSet(*currentSet);
			exit(0);
		}
		
		
//		cout << "SET #: " << currentIndex << "\tSIZE: " << currentSet->size() << endl;
//		cout << "MISSES: " << misses << "\tHITS: " << hits << endl;
		

//		printSet(*currentSet);

		currentSet = nullptr;
		currentIt = nullptr;
		delete currentSet;
		
		
		delete currentIt;
	}
	
	
//	void Cache::checkEntry(mem_address& adr)
//	{
//		cout << "IN CHECK ENTRY" << endl;
//		int currentIndex = bitsToInt(adr.index);	//grab our current set index from the cache
//
//		list<entry>* currentSet = &setVector.at(currentIndex); //for easier code
//		
//		list<entry>::iterator* currentIt = &it.at(currentIndex);
//		//need iterator for operations
//		list<entry>::iterator search;
//		
//		
//		cout << "INDEX: " << currentIndex << endl;
//		cout << "Set vector size: " << setVector.size() << endl; 
//	
//		
//		
////		mem_address* G = &adr;
//		
//		
//		
//		/*Search for the memory address in the list*/
//		*currentIt = find(currentSet->begin(), currentSet->end(), &adr);
//		
//		
//		
//		cout << "CURRENT SET SIZE: " << currentSet->size() << endl;
//		
//		
//		/*IF cache misses and the set is full, then replace LRU*/
//		if((*currentIt == currentSet->end()) && (currentSet->size() == assoc))
//		{
//			cout << "Conflict Miss" << endl;
//			misses++;		//increment misses
//			
////			/*Reset set iterator to beginning, then increment 1 to replace LRU*/
////			(*currentIt) = currentSet->begin();	//increment currentIt to keep track of LRU
////			(*currentIt)++;
//			
//			
//			
//			search = currentSet->begin(); 	//put iterator to begin for delete
//			deleteMemEntry((*search));		//delete mem_address pointer 
//			
//			currentSet->erase(search);		//delete entry in the list
//			currentSet->push_front(&adr);	//push mem_address to the front
//			
//			search = currentSet->begin();	//restore iterator to new LRU, same as = currentIt
//			*currentIt = search;
//			
//			cout << "After cache miss: " << (**currentIt)->tag << endl;
//			cout << "After cache miss: " << (*search)->tag << endl;
////			cout << (**currentIt)->mem << endl;	//** because iterator is a ptr, and to deref its another *
//			
//		}
//		/*Cache miss but we have an empty set: COMPULSORY MISS*/
//		else if(*currentIt == currentSet->end())
//		{
//			cout << "Compulsory Miss " << endl;
//			misses++;
//			
//			currentSet->push_front(&adr);
//			*currentIt = currentSet->begin();
//			
//			cout << "After compulsory miss: " << ((**currentIt))->tag << endl;
//			
//			
//		}
//		else if(*currentIt != currentSet->end())
//		{
//			cout << "Cache hit " << endl;
//		}
//		
//		printSet(*currentSet);
//		
//		
//		
//		
//		/*Here, pointers are set to null because they are automatically managed by the vector and list classes*/
//		currentSet = nullptr;
//		currentIt = nullptr;
//		
//		/*Just delete our empty pointers now*/
//		delete currentSet;
//		delete currentIt;
//		
//		/*This would throw exit codes if delete was before setting to null ptr*/
//	}
	
//	void Cache::printSet(list<entry>& l)
//	{
//		int i=0;
//		for(list<entry>::iterator j= l.begin(); j != l.end(); j++)
//		{
//			cout << "Index: " << i << "\t" << (*j)->mem << endl;
//		}
//	}
	
	void Cache::printSet(list<tagentry>& l)
	{
		int i=0;
		for(list<tagentry>::iterator j= l.begin(); j != l.end(); j++)
		{
			cout << "Index: " << i << " " << *j << endl;
			i++;
		}
	}
	
	/*Must delete the memory allocated for the mem_address pointer before deleting the entry from the list*/
	void Cache::deleteMemEntry(mem_address*& adr)
	{
		cout << "Deleting ptr: " << adr << endl;
		adr = nullptr;
		delete adr;
	}
	
	void Cache::createCache() 
	{
		blocks = capacity/block_size;
		sets = blocks/assoc;
		offset = log(block_size)/log(2);
		index = log(sets)/log(2);
		tag = 32 - offset - index;
		
		hits		= 0;
		misses		= 0;

//		setVector.resize(sets);	//allocate n sets for the vector length
//		it.resize(sets);			//allocate n iterators for each 
		tagCache.resize(sets);
		tagIt.resize(sets);
//		setVector.at(0)
		
		/*Initialize all iterators to their respective set's begin*/
		for(int i=0; i<sets; i++)
		{
//			it.at(i) = setVector.at(i).begin();
			tagIt.at(i) = tagCache.at(i).begin();
		}
	}
	
	void Cache::readMemory() {
		ifstream file;
		string line;
		
		file.open("example.trc", ios::in);
		
		int j=0;
		while(!file.eof())
		{
			getline(file,line);

			/*Break file read if there is only an \n character left in the file!*/
			if(line.length()<2)
			{
				break;
			}
			memory.push_back(hexToBin(line));
			
//			/*Store tags*/
//			tags.push_back(getTag(memory.at(j)));
//			intTags.push_back(bitsToInt(tags.at(j)));
//			
//			/*Store indexes*/
//			indexes.push_back(getIndex(memory.at(j)));
//			intIndexes.push_back(bitsToInt(indexes.at(j)));
//			
//			/*Store offsets*/
//			offsets.push_back(getOffset(memory.at(j)));
//			intOffsets.push_back(bitsToInt(offsets.at(j)));
			
			

//			cout << "FROM FILE: " << line << endl;
//			cout << "MEM: " << memory.at(j) << endl;
//			cout << "TAG: " << tags.at(j) << endl;
//			cout << "INTTAG : " << intTags.at(j) << endl;
			
//			cout << j << endl;
			j++;
		}
		
		//Delete extra line read in
		
		cout << "Read in " << j << " memory addresses from the file" << endl;
		
		memoryLength = j;
		
		
		
		file.close();
	}
	
	/*Returns a bitset<32> for analyzing the memory address*/
	bits Cache::hexToBin(string& s)
	{
		stringstream ss;
		unsigned int n;	
		
		ss << hex << s;
		ss >> n;
		bitset<32> b(n);

		
		return b;
	}
	
	/*Returns the tag of the mema address as a bitset*/
	bits Cache::getTag(bits& h)
	{
		bitset<32> b(h.to_string(), 0, tag);
		
		return b;
	}
	
	bits Cache::getIndex(bits& h)
	{
		bitset<32> b(h.to_string(), tag, index);
		
		return b;
	}
	
	bits Cache::getOffset(bits& h)
	{
		bitset<32> b(h.to_string(), index+tag, 31);
		
		return b;
	}
	
	/*Returns int from a bitset*/
	int Cache::bitsToInt(bits& h)
	{
		int b = stoi(h.to_string(), nullptr, 2);
		//can also use b.to_ulong();
		
		return b;
	}
	
	
	
	
}
