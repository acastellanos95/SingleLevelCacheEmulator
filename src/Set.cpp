//
// Created by andre on 3/11/22.
//

#include "Set.h"

#include <utility>
Set::Set(unsigned short number_of_blocks, unsigned short number_bits_tag) {
  this->_blocks = std::vector<Block>(number_of_blocks, Block(number_bits_tag));
}
Block Set::readBlockFromSet(unsigned short index_block) {
  return this->_blocks[index_block];
}
void Set::writeBlockFromSet(unsigned short index_block, bool valid, bool dirty, std::vector<bool> tag, int data) {
  this->_blocks[index_block].writeBlock(valid, dirty, std::move(tag), data);
}
