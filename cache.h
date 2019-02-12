#ifndef CACHE
#define CACHE

#include "set.h"
#include "block.h"

namespace G
{
class cache 
{
  unsigned long total_access_counter, hit_count;
  int cache_size;
  int block_size;
  int set_associativity;
  int num_sets;
  set *sets;
  char replacement_policy;
  int access(addr);			//{locate and access a set, return "hit" or "miss"}
  cache(cache_size, block_size, set_assoc, replacement_policy);	//{constructor of the cache class}
};
}

#endif
