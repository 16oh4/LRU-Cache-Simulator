#include <iostream>
//#include <fstream>
#include <sstream>
#include <stdint.h>
#include <vector>

#include "Block.h"
#include "Cache.h"
#include "Set.h"
/*
	USING Code from this Website as a base
	http://alumni.cs.ucr.edu/~yluo/cs161L/labs/cachenote.txt
*/
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

void readConfig() {
	
}
int main(int argc, char** argv) 
{
	uint64_t memadr;
	unsigned int H;
	
	vector<unsigned int> memory;
	vector<unsigned char> membyte;
	unsigned char* memarray;
	
//	string test = "0x9032BFAB";
//	H = stoul(test, nullptr, 0);
//	cout << hex << H << endl;
	
//	unsigned int test = 0x9032BFAB;
	unsigned int test = 0x7E801111;
	membyte = memBytes(test);
	cout << "SIZE: " << membyte.size() << endl;
	for(int i=0;i<4;i++)
	{
		cout << membyte.at(i) << endl;
		
	}
	
	memarray = bytes(test);
	cout << (unsigned int)*memarray << endl;
	
	
	
	ifstream file;
	string line;
	size_t found;
	int c,b,n;
	
	
	file.open("example.cfg", ios::in);
	
	if (file.is_open())
	{
		getline(file,line);
//		cout << line << endl;
		found = line.find("=");
//		cout << line.substr(found+1, line.length()) << endl;
		
		c = stoi(line.substr(found+1, line.length()),nullptr,16);
		cout << c << endl;
		
		getline(file, line);
		found = line.find("=");
		b = stoi(line.substr(found+1, line.length()),nullptr,16);
		
		getline(file, line);
		found = line.find("=");
		n = stoi(line.substr(found+1, line.length()),nullptr,16);
		
		
		cout << b << endl;
		cout << n << endl;
	}
	
	
	
	
	//			for(int i=0; i<10; i++)
//			{
//	//			getline(file,line);
//	//			memory.push_back(stoul(line, nullptr, 0));
//	//			cout << hex << memory.at(i) << endl;
//				
//	
//			}

	double cap = (double) c;
	double blocks = (double) b;
	double assoc = (double) n;
	
//	Cache file_cache(cap,blocks,assoc);
	Cache cache2(c,b,n);

	
	file.close();
	
	delete memarray;
	return 0;
}

//vector<unsigned char> intToBytes(int paramInt)
//{
//	vector<unsigned char> arrayOfByte(4);
//	for (int i = 0; i < 4; i++)
//		arrayOfByte[3 - i] = (paramInt >> (i * 8));
//	return arrayOfByte;
//}
