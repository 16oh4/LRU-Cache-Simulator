#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;


int main()
{
    ifstream file;
    string line;
    size_t found;
    unsigned int n;
    vector<int> binaryNum;  
    int i=0;
    unsigned long number = 0;
    long long counter=0;
    char x;
    cout<<"Before File Open"<<endl;
    file.open("example1.trc", ios::in);
    cout<<"File Open"<<endl;    
    while (file.get(x))
    {
        getline(file,line);
        found = line.find("x");
        n = stol(line.substr(found+1, line.length()),nullptr,16);
        
        cout<<"TEST: "<<hex<<n<<"    "<<dec<<counter<<endl;
		counter++;

		while (n > 0) 
	    { 
	        binaryNum.push_back(n%2); 
	        n = n / 2; 
	        i++; 
	    } 
	    int offset = 6;
	    int index = 7;
	    int tag = 19;

	for (int i=tag+offset+index-1; i>=(offset+index); --i)
	    {
	    	cout<<binaryNum[i];
	    	if(binaryNum[i])
	    	{
				number = number + pow(2,(i-offset-index));
					//cout<<"i Value: "<<i<<endl;
			}
    	}    

/*	Used to convert binary list to decimal    
	for (int i=tag+offset+index-1; i>=(offset+index); --i)
	    {
	    	cout<<binaryNum[i];
			number *= 10;
    		number += binaryNum[i];
    	}
*/	    cout<<endl;


cout <<dec<<number<<endl;

	if (file.eof())                      // check for EOF
    	{
    	//	cout<<"Count: "<<counter;
    		cout <<endl<< "[EoF reached]\n";
    		break;
    	}
	}
    file.close();
    return 0;
}