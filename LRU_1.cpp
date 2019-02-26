#include <iostream>
#include <list>
#include <unordered_map>
#include <math.h>
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
    void Replace(int, int &, int &); 
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
    int blocks = C/b;
    cout<<"BLOCKS: "<<blocks<<endl;
    int sets = blocks/N;
    cout<<"SETS: "<<sets<<endl;
    int offset = log(block_size)/log(2);
    cout<<"OFFSET: "<<offset<<endl;
    int index = log(sets)/log(2);
    cout<<"INDEX: "<<index<<endl;
 }
//////////////////////////////////////////////////////////////////
void Cache::Replace(int Tag, int &hit, int &miss) 
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
int main() 
{ 
    int Tag;
    int hit=0;          //Number of hits counter
    int miss=0;         //Number of misses counter

    int c_size=5;       //# of blocks(cache size)
    int num_in=7;       //number of total memory inputs
    int C=32768;        //cache size
    int b=64;           //black size
    int N=4;            //assoc

    Cache LRUCache(c_size, C, b, N); 
    for(int i=0; i<num_in; i++)  //iterate for how many inputs were given
    {
        cout<<"Enter memory Address: "<<endl;
        cin>>Tag;
        LRUCache.Replace(Tag, hit, miss);
    }

    cout<<endl<<"Number of hits: "<<hit<<endl;
    cout<<"Hit Rate: "<<(float)hit/num_in*100<<"%"<<endl<<endl;
    cout<<"Number of misses: "<<miss<<endl;
    cout<<"Miss Rate: "<<(float)miss/num_in*100<<"%"<<endl;

    //cout<<12345 / 1000 % 10<<endl; //method to access individual digits, prints 2

    return 0; 
} 
