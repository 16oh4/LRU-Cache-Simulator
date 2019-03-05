/*
LRU Cache Simulator
3/4/19
Developers: Bruno E. Gracia Villalobos
			Ryan Walker
*/

#include "Cache.h"

namespace G 
{	
	typedef bitset<32> bits;
	
	/*Constructor to initialize given values from the file*/
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
		free(bank);	//Free memory allocated for the array of structs
	}
	
	/*MAIN CONTROL*/
	/*Test each individual memory address read in from the file to see if they're in the cache*/
	void Cache::testMem() 
	{
		/*Allocate buckets for total memory addresses into array of structs
			Will allocate 16 bytes per bucket, for 4 bitsets per struct
			Total memory allocated = 695521 * 16 bytes
		*/
		bank = (mem_address*)malloc(sizeof(mem_address)*memoryLength);

		/*Store mem address, tag, index, offset into an array of structs*/
		for(int i=0; i<memoryLength; i++)
		{
			bank[i].mem 	= memory.at(i);
			bank[i].tag 	= getTag(memory.at(i));
			bank[i].index 	= getIndex(memory.at(i));
			bank[i].offset 	= getOffset(memory.at(i));

		}
		
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
	/*Print out the given mem address structure*/
	void Cache::printMemAdr(mem_address& adr)
	{
		cout << "MEM:\t" << adr.mem <<
				"\nTAG:\t" << adr.tag << 
				"\nINDEX:\t" << adr.index << 
				"\nOFFSET:\t" << adr.offset << endl;
	}
	
	/*Check a specific memory address to see if it's in the cache*/
	void Cache::checkEntry(mem_address& adr)
	{
		int currentIndex 					= bitsToInt(adr.index);			//grab our current set index from the cache

		list<tagentry>* currentSet 			= &tagCache.at(currentIndex); 	//make a pointer for the set an n index
		
		list<tagentry>::iterator* currentIt = &tagIt.at(currentIndex);		//iterator for the nth set
			
		*currentIt = find(currentSet->begin(), currentSet->end(), adr.tag);	//search for the tag in the set at n index
		
		/*Cache FULL*/
		if(currentSet->size() == assoc)
		{
			/*Cache MISS*/
			if( (*currentIt == currentSet->end()) )
			{
				misses++;
				
				*currentIt = currentSet->begin();	//set iterator pointer to LRU
				currentSet->erase(*currentIt);		//erase LRU
				currentSet->push_back(adr.tag);		//push back the tag as the new MRU
				
				/*Calculate position for iterator*/
				*currentIt = currentSet->begin();
				advance(*currentIt, distance(*currentIt, currentSet->end())-1); //advance to the last placement

			}
			
			/*Cache HIT*/
			else
			{
				hits++;
				
				currentSet->erase(*currentIt);
				
				currentSet->push_back(adr.tag);
				
				/*Calculate position for iterator*/
				*currentIt = currentSet->begin();
				advance(*currentIt, distance(*currentIt, currentSet->end())-1); //advance to the last placement
				
			}
		}
		/*Cache NOT FULL*/
		else if ( (currentSet->size() != 0) && (currentSet->size() < assoc))
		{
			/*Cache MISS, Compulsory Miss*/
			if( (*currentIt == currentSet->end()) )
			{
				misses++;
				
				currentSet->push_back(adr.tag);
				
				/*Calculate position for iterator*/
				*currentIt = currentSet->begin();
				advance(*currentIt, distance(*currentIt, currentSet->end())-1); //advance to the last placement
				
			}
			/*Cache HIT*/
			else
			{
				hits++;
				
				currentSet->erase(*currentIt);	//erase spot to move to MRU now

				currentSet->push_back(adr.tag);
				
			}
		}
		/*Cache NEW, Compulsory Miss*/
		else if( (currentSet->size() == 0) && (*currentIt == currentSet->end()) )
		{
			misses++;
			
			currentSet->push_back(adr.tag);		//append to the back (MRU)
			*currentIt = currentSet->begin();	//set iterator to this position since set is NEW
		}
		
		/*Check if iterator does not point to the same tag*/
		if( (**currentIt) != adr.tag)
		{
			cout << "ERROR @ " << currentIndex << " mem:" << endl;
			printMemAdr(adr);
			printSet(*currentSet);
			exit(0);
		}
		
		/*Pointer cleanup*/
		currentSet = nullptr;
		currentIt = nullptr;
		delete currentSet;
		delete currentIt;
	}
	
	/*Print the given list set of blocks in the cache*/	
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
	
	/*Initialize values for the cache*/
	void Cache::createCache() 
	{
		blocks 	= capacity/block_size;
		sets	= blocks/assoc;
		offset 	= log(block_size)/log(2);
		index 	= log(sets)/log(2);
		tag 	= 32 - offset - index;
		
		hits	= 0;
		misses	= 0;
		
		/*Allocate space for the vectors*/
		tagCache.resize(sets);
		tagIt.resize(sets);
		
		/*Initialize all iterators to their respective set's begin*/
		for(int i=0; i<sets; i++)
		{
			tagIt.at(i) = tagCache.at(i).begin();
		}
	}
	
	/*Read in the memory trace and store in a vector*/
	void Cache::readMemory() {
		ifstream file;
		string line;
		string file_name;

		cout<<"Enter name of file with memory addresses: ";
		cin>>file_name;

//		file.open("example.trc", ios::in);
		file.open(file_name, ios::in);
		
		int j=0;
		
		/*Read lines until end of file*/
		while(!file.eof())
		{
			getline(file,line);

			/*Break file read if there is only an \n character left in the file!*/
			if(line.length()<2)
			{
				break;
			}
			
			/*Store hex address as a bitset in the storage vector*/
			memory.push_back(hexToBin(line));
			
			j++;
		}

		cout << "Read in " << j << " memory addresses from the file" << endl;
		
		memoryLength = j;	//keep track of total memory addresses on file

		file.close();
	}
	
	/*Returns a bitset<32> for analyzing the memory address*/
	bits Cache::hexToBin(string& s)
	{
		stringstream ss;
		unsigned int n;	
		
		/*Send the string as hex to the stream*/
		ss << hex << s;
		ss >> n;
		
		/*Construct bitset out of parsed int*/
		bitset<32> b(n);

		return b;
	}
	
	/*Returns the tag of the mema address as a bitset*/
	bits Cache::getTag(bits& h)
	{
		bitset<32> b(h.to_string(), 0, tag);
		
		return b;
	}
	
	/*Returns index bits of the mem address given*/
	bits Cache::getIndex(bits& h)
	{
		bitset<32> b(h.to_string(), tag, index);
		
		return b;
	}
	
	/*Returns offset bits of the mem address given*/
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
