//
// Created by andre on 3/12/22.
//

#ifndef CACHECPP_SRC_SINGLELEVELCACHE_H_
#define CACHECPP_SRC_SINGLELEVELCACHE_H_

#include "CacheMemory.h"
#include "MainMemory.h"
class SingleLevelCache {
  CacheMemory _cache;
  MainMemory _mem;
  unsigned short _size_of_memory;
  unsigned short _number_of_sets;
  unsigned short _number_of_ways;
  std::vector<std::queue<unsigned short>> _replacement_queue;
 public:
  SingleLevelCache(unsigned short size_of_memory, unsigned short number_of_sets, unsigned short number_of_ways);
  void load(const std::string &hexAddress, const int data);
  void read(const std::string &hexAddress);
};

#endif //CACHECPP_SRC_SINGLELEVELCACHE_H_
