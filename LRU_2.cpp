#include <iostream>
#include <list>
#include <unordered_map>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std; 
  
class Cache 
{ 
    list<int> List;                                     //List to store keys
    unordered_map<int, list<int>::iterator> cache;      //create cache 
    int cache_size;                                     //maximum capacity of cache 
    int capacity;
    int block_size;
    int assoc;
  
public: 
    Cache(int, int&, int&, int&); 
    void createCache(int& , int&, int&);
    void Replace(unsigned long, int &, int &); 
    void display(); 
}; 
//////////////////////////////////////////////////////////////////  
Cache::Cache(int c_size,int& C, int&b, int&N) 
{ 
    cache_size = c_size; 
    capacity    = C;
    block_size  = b;
    assoc       = N;
       
    createCache(C, b, N);
} 
//////////////////////////////////////////////////////////////////
void Cache::createCache(int& C, int&b, int&N) 
{    
    int B;
    int S;
    int offset;
    int index;
    int tag;

    B = C/b;                    //# of Blocks
    S = B/N;                    //# of Sets
    offset = log(b)/log(2);     //# of Offset bits
    index = log(S)/log(2);      //# of Index
    tag = 32 - offset - index;  //#tag bits

    cout << "Capacity: " << C << endl;
    cout << "Block Size: " << b << endl;
    cout << "Associativity: " << N << endl;
    cout << "Total blocks: " << B << endl;
    cout << "Total sets: " << S << endl;
    cout << "Offset bits: " <<dec<< offset << endl;
    cout << "Index bits: " << index << endl;
    cout << "Tag bits: " << tag << endl;
 }
//////////////////////////////////////////////////////////////////
void Cache::Replace(unsigned long Tag, int &hit, int &miss) 
{ 
    if (cache.find(Tag) == cache.end()) //Miss, iterator has reached end of cache 
    { 
        //cout<<"Miss"<<endl;
        miss++;                         //update miss counter
        if (List.size() == cache_size)       //Cache is full
        { 
            cout<<"Cache Full"<<endl;    
            int last = List.back();     //update key to be deleted
            List.pop_back();            //delete last element from list
            cache.erase(last);          //delete last element from cache
        } 
    } 
    else    //Hit, tag found in cache
    {
        List.erase(cache[Tag]);         //remove from list, will be added back later
        //cout<<"Hit"<<endl;
        hit++;                          //update hit counter
    }
    List.push_front(Tag);               //move element to top of list
    cache[Tag] = List.begin();          //add to cache
} 
//////////////////////////////////////////////////////////////////
// display contents of cache 
void Cache::display() 
{ 
    for (auto it = List.begin(); it != List.end(); it++) //it=iterator. Prints entire List
        cout << (*it) << " "; 
  
    cout << endl; 
} 
//////////////////////////////////////////////////////////////////
void getParameters(int &C, int &b, int &N)
{
    ifstream file;
    string line;
    size_t found;

    cout<<"Before File Open"<<endl;
    file.open("example.cfg", ios::in);
    cout<<"File Open"<<endl;    
    if (file.is_open())
    {
        getline(file,line);
        found = line.find("=");
        C = stoi(line.substr(found+1, line.length()),nullptr,0);

        getline(file, line);
        found = line.find("=");
        b = stoi(line.substr(found+1, line.length()),nullptr,0);
        
        getline(file, line);
        found = line.find("=");
        N = stoi(line.substr(found+1, line.length()),nullptr,0);
    }

    file.close();
}
//////////////////////////////////////////////////////////////////
int main() 
{ 
    
    int hit=0;          //Number of hits counter
    int miss=0;         //Number of misses counter

    int c_size=500;       //# of blocks(cache size)
    int num_in=94;       //number of total memory inputs
    unsigned long Tag;
    int C=0;        //cache size
    int b=0;           //black size
    int N=0;            //assoc

ifstream file;
    string line;
    size_t found;
    unsigned int n;
    vector<int> binaryNum;
    vector<int> Offset;
    vector<int> Index;

    int i=0;
    long long counter=0;
    char x;
    cout<<"Before File Open"<<endl;
    file.open("example1.trc", ios::in);
    cout<<"File Open"<<endl; 


    getParameters(C,b,N);
    Cache LRUCache(c_size, C, b, N); 
    //for(int i=0; i<num_in; i++)  //iterate for how many inputs were given
    //{
    //    cout<<"Enter memory Address: "<<endl;
        



        //cin>>Tag[i];
        //LRUCache.Replace(Tag[i], hit, miss);
    //}

    while (file.get(x))
    {
        getline(file,line);
        found = line.find("x");
        n = stol(line.substr(found+1, line.length()),nullptr,16);
        
        //cout<<"TEST: "<<hex<<n<<"    "<<dec<<counter<<endl;
        counter++;

        while (n > 0) 
        { 
            binaryNum.push_back(n%2); 
            n = n / 2; 
            i++; 
        } 
        //for (int j = i - 1; j >= 0; j--) 
            //cout << binaryNum[j]; 
        //cout<<endl;
        int offset = 6;
        int index = 7;  
        int tag = 19;
        //for (int i=offset-1; i>=0; --i)
            //cout<<binaryNum[i];
        //cout<<endl;
        //for (int i=offset+index-1; i>=offset; --i)
            //cout<<binaryNum[i];
        //cout<<endl;
        for (int i=tag+offset+index-1; i>=(offset+index); --i)
        {
            //cout<<binaryNum[i];
            Tag *= 10;
            Tag += binaryNum[i];
            //cout<<dec<<Tag<<"TAG VALUE"<<endl;
        }
        //cout<<dec<<Tag<<"TAG VALUE"<<endl;    
        //cout<<endl;

        LRUCache.Replace(Tag, hit, miss);

        if (file.eof())                      // check for EOF
        {
        //  cout<<"Count: "<<counter;
            cout <<endl<< "[EoF reached]\n";
            break;
        }
    }
    file.close();




    cout<<endl<<"Number of hits: "<<hit<<endl;
    cout<<"Hit Rate: "<<(float)hit/num_in*100<<"%"<<endl<<endl;
    cout<<"Number of misses: "<<miss<<endl;
    cout<<"Miss Rate: "<<(float)miss/num_in*100<<"%"<<endl;

    //cout<<12345 / 1000 % 10<<endl; //method to access individual digits, prints 2

    return 0; 
} 
