//
// Created by andre on 3/11/22.
//

#ifndef CACHECPP_SRC_CACHEMEMORY_H_
#define CACHECPP_SRC_CACHEMEMORY_H_

#include <vector>
#include <map>
#include <queue>
#include "Set.h"
#include "MainMemory.h"

class CacheMemory {
  unsigned short _size_of_address_bits;
  unsigned short _size_of_set_bits;
  unsigned short _size_of_tag_bits;
  unsigned short _size_of_blocks;
  std::vector<Set> _cache_memory;
 public:
  CacheMemory();
  CacheMemory(unsigned short size_of_set_bits, unsigned size_memory_address_bits, unsigned short size_of_blocks);
  std::vector<Block> getBlocksFromAddress(const std::vector<bool>& address);
  void setBlocksWithAddress(const std::vector<bool> &address, const std::vector<Block> &blocks);
};

#endif //CACHECPP_SRC_CACHEMEMORY_H_
