/*

LRU Cache Simulator
3/4/19

Developers: Bruno E. Gracia Villalobos
			Ryan Walker
*/
#include <iostream>
#include <stdint.h>
#include <vector>		//array of cache sets
#include <list>			//for the cache sets
#include <iterator>		//iterating through lists
#include <algorithm>	//for find function
#include <unordered_map>
#include <utility>
#include "Cache.h"

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
	int c,b,n;
	readConfig(c,b,n);	//read in configuration values from file

	/*Instantiate cache class with config file params*/
	Cache cache2(c,b,n);
	cache2.readMemory();
	cache2.testMem();
	
	return 0;
}
