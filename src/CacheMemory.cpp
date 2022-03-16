//
// Created by andre on 3/11/22.
//

#include "CacheMemory.h"
#include "utils.h"

CacheMemory::CacheMemory(unsigned short size_of_set_bits, unsigned size_memory_address_bits, unsigned short size_of_blocks)
    : _size_of_set_bits(size_of_set_bits),
      _size_of_blocks(size_of_blocks),
      _size_of_address_bits(size_memory_address_bits){
  this->_size_of_tag_bits = this->_size_of_address_bits - this->_size_of_set_bits;
  auto numberOfSets = NumberAddresableByBitSize<unsigned short>(this->_size_of_set_bits);
  this->_cache_memory = std::vector<Set>(numberOfSets, Set(_size_of_blocks, _size_of_tag_bits));
}

std::vector<Block> CacheMemory::getBlocksFromAddress(const std::vector<bool>& address) {
  // get set bit part
  std::vector<bool> setBits(address.end()-this->_size_of_set_bits, address.end());
  auto indexSet = BitsToIntegral<unsigned short >(setBits);
  // Create blocks vector
  std::vector<Block> blocks;
  for (unsigned short indexBlock = 0; indexBlock < this->_size_of_blocks; ++indexBlock) {
    blocks.push_back(this->_cache_memory[indexSet].readBlockFromSet(indexBlock));
  }
  return blocks;
}

void CacheMemory::setBlocksWithAddress(const std::vector<bool> &address, const std::vector<Block> &blocks) {
  // Get set index
  std::vector<bool> setBits(address.end()-this->_size_of_set_bits, address.end());
  auto indexSet = BitsToIntegral<unsigned short >(setBits);
  // check that only one block changed
  unsigned short countChanges = 0;
  for (unsigned short indexBlock = 0; indexBlock < this->_size_of_blocks; ++indexBlock) {
    auto blockWrited = blocks[indexBlock].readBlock();
    auto blockInCache = this->_cache_memory[indexSet].readBlockFromSet(indexBlock).readBlock();
    if(!(blockWrited == blockInCache))
      countChanges++;
  }
  if(countChanges > 1)
    throw std::runtime_error("array of block was changed more than once");
  // Change now blocks
  for (unsigned short indexBlock = 0; indexBlock < this->_size_of_blocks; ++indexBlock) {
    auto block = blocks[indexBlock].readBlock();
    this->_cache_memory[indexSet].writeBlockFromSet(indexBlock, std::get<0>(block), std::get<1>(block), std::get<2>(block), std::get<3>(block));
  }
}
CacheMemory::CacheMemory() {

}
