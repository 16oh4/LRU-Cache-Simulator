# Fast LRU Cache Simulator, 695,000 memory addresses analyzed in 2.5 seconds
https://github.com/brunogracia/cachesimulator/blob/master/README.md

A C++ simulation of an LRU cache with a ~695000 memory address dump. Combination of lists and vectors were used to implement LRU Cache. Vectors were used to store the entire memory from the file with the memory addresses. The cache was created as a vector of lists, which simulated the sets. 

--------------------------------------------------------------------------------------------------------------------------------------------

HOW IT WORKS:

The memory address trace is read in from the specified file and stored in a dynamically allocated array of mem_address structs called "bank". This struct holds information about the memory address: (the memory address itself, the tag bits, the index bits, and the offset bits). So there is a mem_address struct generated for every memory address read in from the file.

Next, beginning with the first read memory address, in this case bank[0], the memory address is passed in checkEntry() for checking if it is in the cache. The algorithm checks the index bits of the incoming mem_address struct, and selects the appropriate set (list<entry>) from the cache vector (which stores all sets in the cache). 
  
The tag bits are compared against what is stored in the list, and if it is a match, the hits are incremented. If it is a miss, the tag is put in the set on the LRU position.

Here is a brief showcase of how the LRU algorithm works (with arbitrary tags), with a cache of associativity = 4

0x0040|-0x007C|-0x008D|-0x009C-|

LRU---|

If an incoming tag= 0x748A is a miss in the cache, then it will be updated in this spot:

0x007C|-0x008D|-0x009C|-0x748A-|

LRU---|

The remaining tags in the set will be shifted to towards the n=0 slot as they increase in their LRU'ness.

--------------------------------------------------------------------------------------------------------------------------------------------

Compile main.cpp, cache.h, and cache.cpp. INCLUDE configuration file example.cfg, and example.trc (32 bit memory address trace) in your source folder

Change working directory to folder containing files. 
Compile with g++ using c++11 with the following command:
g++ -std=c++11 Cache.cpp main.cpp  -o hw
./hw 

Sample Runs: (Memory sizes are in bytes)

Cache Size=32768
Block Size=64
Associativity=4
HIT RATE: 0.85424

Cache Size=32768
Block Size=64
Associativity=2
HIT RATE: 0.853662

Cache Size=16384
Block Size=64
Associativity=2
HIT RATE: 0.852278

Cache Size=16384
Block Size=64
Associativity=8
HIT RATE: 0.853008



![alt text](https://github.com/brunogracia/cachesimulator/blob/master/Capture.PNG)
