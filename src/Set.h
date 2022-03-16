//
// Created by andre on 3/11/22.
//

#ifndef CACHECPP_SRC_SET_H_
#define CACHECPP_SRC_SET_H_

#include <vector>
#include "Block.h"
class Set {
  std::vector<Block> _blocks;
 public:
  Set(unsigned short number_of_blocks, unsigned short number_bits_tag);
  Block readBlockFromSet(unsigned short index_block);
  void writeBlockFromSet(unsigned short index_block, bool valid, bool dirty, std::vector<bool> tag, int data);
};

#endif //CACHECPP_SRC_SET_H_
