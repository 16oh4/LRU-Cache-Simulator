# cachesimulator
A C++ simulation of an LRU cache with a ~650000 memory address dump. Combination of lists and vectors were used to implement LRU Cache. Vectors were used to store the entire memory from the file with the memory addresses. The cache was created as a vector of lists, which simulated the sets. 

Compile main.cpp, cache.h, and cache.cpp. INCLUDE configuration file example.cfg, and example.trc (32 bit memory address trace) in your source folder

Change working directory to folder containing files. 
Compile with g++ using c++11 with the following command:
g++ -std=c++11 Cache.cpp main.cpp  -o hw
./hw 

Cache Size=32768
Block Size=64
Associativity=4
HIT RATE: 0.85424

Cache Size=32768
Block Size=64
Associativity=4
HIT RATE: 0.853662

Cache Size=16384
Block Size=64
Associativity=4
HIT RATE: 0.027724
