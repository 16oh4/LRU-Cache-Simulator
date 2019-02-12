#ifndef SET
#define SET

#include "cache.h"
#include "block.h"

namespace G
{
class set {
      int num_blks;
      block *blk;
      char replacement_policy;
      
      /*Function Prototypes*/
      int access(tag);			//{compare tag with blocks in this set, return block id or "miss"}
      int find_victim(policy);	//	{find a victim block to replace with "policy"}
};	
}

#endif
