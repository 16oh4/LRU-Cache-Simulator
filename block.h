#ifndef BLOCK
#define BLOCK

#include "set.h"
#include "cache.h"

namespace G
{
class block {
  unsigned long tag;
  unsigned long timestamp;
  
  char valid;
  
  /*Function Prototypes*/
  update_ts(unsigned long newts); 		//{update timestamp}
  update_tag(unsigned long newtag); 	//{update tag}
  int compare_tag(unsigned long tag);	// {compare tag with my tag, return block id or "miss")
};
}

#endif
