#include <iostream>
#include <stdint.h>
#include <vector>		//array of cache sets
#include <list>			//for the cache sets
#include <iterator>		//iterating through lists
#include <algorithm>	//for find function
#include <unordered_map>
#include <utility>

#include "Block.h"
#include "Cache.h"
#include "Set.h"

using namespace G;
using namespace std;



//Returns a 4 byte vector with the lowest index at the MSB
vector<unsigned char> memBytes(unsigned int a) 
{
	int size = sizeof(a);
	vector<unsigned char> address(sizeof(a));
	
	unsigned char temp;
	unsigned int tempint;
	unsigned char built;
	
	//To print an unsigned char in hex:
	//cout << (unsigned int)*memarray << endl;
	
	for(int i = 0; i < size; i++)
	{
		temp = (a>>(i*8)) & 0xFF;
		address.at(3-i) = temp; 
		cout << "TEMP:" << temp << hex << endl;
//		cout << sizeof(address.at(i)) << endl;
//		cout << sizeof((a>>(i*8)) & 0xFF) << endl;
		cout << hex << ((a>>(i*8)) & 0xFF) << endl;
//		cout << "SIZE:" << address.size() << endl;
	}
	
	
	
	return address;
}

//Returns a char* array of bytes given an int
unsigned char* bytes(unsigned int &a)
{
	unsigned char* ret = (unsigned char*)malloc(sizeof(a));
	memcpy(ret, (unsigned char*)&a, sizeof(a));
	
	return ret;
}

/*Reads in config file*/
void readConfig(int& c, int& b, int& n) {
	/*VARIABLE DECLARATIONS*/
	ifstream file;
	string line;
	size_t found;
	
	/*FLUSH COUT*/
	cout << flush;
	cout.flush();
	cout << dec;
	
	/*Begin configuration file read*/
	file.open("example.cfg", ios::in);
	
	if (file.is_open())
	{
		/*READ FIRST CONFIG LINE - CACHE SIZE */
		getline(file,line);
		found = line.find("=");
		c = stoi(line.substr(found+1, line.length()),nullptr,0);
		
		/*READ SECOND CONFIG LINE - BLOCK SIZE */
		getline(file, line);
		found = line.find("=");
		b = stoi(line.substr(found+1, line.length()),nullptr,0);
		
		/*READ Third Config Line - ASSOCIATIVITY*/
		getline(file, line);
		found = line.find("=");
		n = stoi(line.substr(found+1, line.length()),nullptr,0);
	}
	
	file.close();
}


int main(int argc, char** argv) 
{
	
	int h=4;
	
	list<int> set;
	list<int>::iterator it;
	list<int>::iterator func;
	list<int>::iterator search;
	
	list<int>::iterator LRU;
	unordered_map<int,int> test;
	
	pair<int,int> insertion;
	insertion = make_pair(0,7);
	
//	test.insert(unordered_map<int,int>::value_type(0, 2));
	test.insert(insertion);

	
	cout << "MAP " << test.at(0) << endl;
	test.erase(0);
	
	insertion = make_pair(1,10);
	test.insert(insertion);
	cout << "MAP " << test.at((insertion.first)) << endl;

	
	set.push_back(1);
	set.push_back(2);
	set.push_back(3);
	set.push_back(4);
//	set.push_back(5);
	
	//the first element of the list is always the LRU
	//the last element is always the MRU
	it = set.begin();
	func = set.begin();
	LRU = set.begin();
	
	//
	advance(func, 1);
	
//	set.erase(func);
	
	//check if an int is a hit
	int s = 7;
	search = find(set.begin(), set.end(), s); 
	
	
	//IF CACHE MISS, insert at front
	if(search == set.end())
	{
		cout << "Search failed!" << endl;
		/*Move LRU pointer 1 back*/
		it++;
		
		/*Erase previous LRU*/
		search = set.begin();
		set.erase(search); //now search points to the new front
		
		/*Insert */
		set.push_back(s);
		
		search = set.begin();
		cout << "SEARCH IS NOW : << " << *search << endl;
	}
	//IF CACHE HIT, move tag to back
	else
	{
		cout << "DISTANCE: " << distance(set.begin(),search) << endl;
		set.erase(search);
		set.push_back(s);
	}
	
	//IF the beginning is erased then cannot deference it
	//Good idea to keep two iterators, one for deref, another for operations
	// set.size() == set.end()
	
	int j=0;
	while(it!=set.end())
	{
		cout << *it << endl;
		it++;
		j++;
		if(it == set.end())
		{
			cout << "GG @ " << set.size() << ":" << j;
		}
	}
	return 0;
}
void ptr(int*& i)
{
	delete i;
	i = nullptr;
}
//int main(int argc, char** argv)
//{
//	int c,b,n;
//	readConfig(c,b,n);
//
//	/*Instantiate cache class with config file params*/
//	Cache cache2(c,b,n);
//	cache2.readMemory();
//	cache2.testMem();
//
////	int G = 7;
////	
////	int* h = &G;
////
////	
////	cout << "MEM h: " << h << "\n*: " << *h << endl;
////	cout << "MEM G: " << &G << "\n*: " << G << endl;
////	
////	ptr(h);
////	
////	if(h == nullptr)
////	{
////		cout << "GG" << endl;
////	}
////	
////	cout << "MEM h: " << h << "\n*: " << *h << endl;
////	cout << "MEM G: " << &G << "\n*: " << G << endl;
//	
//	return 0;
//}


