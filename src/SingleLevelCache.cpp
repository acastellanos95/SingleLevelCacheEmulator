//
// Created by andre on 3/12/22.
//

#include "SingleLevelCache.h"
#include "utils.h"
#include "../lib/VariadicTable.h"
SingleLevelCache::SingleLevelCache(unsigned short size_of_memory,
                                   unsigned short number_of_sets,
                                   unsigned short number_of_ways)
    : _size_of_memory(size_of_memory), _number_of_sets(number_of_sets), _number_of_ways(number_of_ways) {
  this->_cache = CacheMemory(log2<unsigned short>(_number_of_sets), log2<unsigned short>(_size_of_memory), _number_of_ways);
  this->_mem = MainMemory(_size_of_memory);
  this->_replacement_queue = std::vector<std::queue<unsigned short>>(_number_of_sets, std::queue<unsigned short>());
}

void SingleLevelCache::load(const std::string &hexAddress, const int data) {
  auto addressBits = HexToBits(hexAddress, log2<unsigned short>(_size_of_memory));
  auto numberOfSetBits = log2<unsigned short>(_number_of_sets);
  // Write into memory
  std::cout << "Write into memory: " << hexAddress + " " << data << '\n';
  this->_mem.writeToMemoryWithAddress(addressBits, hexAddress, data);
  // Fill cache mem if not valid yet
  std::vector<bool> setBits(addressBits.end()-numberOfSetBits, addressBits.end());
  auto indexSet = BitsToIntegral<unsigned short >(setBits);
  auto blocks = this->_cache.getBlocksFromAddress(addressBits);
  auto tag = std::vector<bool>(addressBits.begin(), addressBits.end()-numberOfSetBits);
  for(auto indexBlock = 0; indexBlock < _number_of_ways; ++indexBlock){
    auto blockInfo = blocks[indexBlock].readBlock();
    bool validBit = std::get<0>(blockInfo);
    if(!validBit){
      blocks[indexBlock].writeBlock(true, false, tag, data);
      this->_replacement_queue[indexSet].push(indexBlock);
      this->_cache.setBlocksWithAddress(addressBits, blocks);
      // Print what we did
      std::cout << "Filling\n";
      VariadicTable<std::string, unsigned short, unsigned short, int, int> vt({"Memory Address", "Set Index", "Block Index", "Data Before", "Data After"});
      vt.addRow(hexAddress, indexSet, indexBlock, std::get<3>(blockInfo), data);
      vt.print(std::cout);
      return;
    }
  }
  // When filled, then pop block_index of FIFO
  auto blockIndex = this->_replacement_queue[indexSet].front();
  auto blockInfo = blocks[blockIndex].readBlock();
  this->_replacement_queue[indexSet].pop();
  this->_replacement_queue[indexSet].push(blockIndex);
  blocks[blockIndex].writeBlock(true, false, tag, data);
  this->_cache.setBlocksWithAddress(addressBits, blocks);
  // Print what we did
  std::cout << "Replacing\n";
  VariadicTable<std::string, unsigned short, unsigned short, int, int> vt({"Memory Address", "Set Index", "Block Index", "Data Before", "Data After"});
  vt.addRow(hexAddress, indexSet, blockIndex, std::get<3>(blockInfo), data);
  vt.print(std::cout);
}

void SingleLevelCache::read(const std::string &hexAddress) {
  auto addressBits = HexToBits(hexAddress, log2<unsigned short>(_size_of_memory));
  auto numberOfSetBits = log2<unsigned short>(_number_of_sets);
  // Search tag in cache
  std::vector<bool> setBits(addressBits.end()-numberOfSetBits, addressBits.end());
  auto indexSet = BitsToIntegral<unsigned short >(setBits);
  auto blocks = this->_cache.getBlocksFromAddress(addressBits);
  auto tagOfAddress = std::vector<bool>(addressBits.begin(), addressBits.end()-numberOfSetBits);
  for(auto indexBlock = 0; indexBlock < _number_of_ways; ++indexBlock){
    auto blockInfo = blocks[indexBlock].readBlock();
    bool validBit = std::get<0>(blockInfo);
    auto tagOfBlock = std::get<2>(blockInfo);
    if(validBit & tagOfAddress == tagOfBlock){ // TODO: test same size
      // Convert tag to binary string
      int tag = BitsToIntegral<int>(tagOfBlock);
      std::stringstream HexTag;
      HexTag << std::hex << tag;
      // Print what we did
      std::cout << "Hit\n";
      VariadicTable<std::string, unsigned short, unsigned short, std::string, int> vt({"Memory Address", "Set Index", "Block Index", "Tag", "Data"});
      vt.addRow(hexAddress, indexSet, indexBlock, HexTag.str(), std::get<3>(blockInfo));
      vt.print(std::cout);
      return;
    }
  }
  // Miss
  std::cout << "Miss\n";
  std::cout << "take from main memory to cache\n";
  auto data = this->_mem.readFromMemoryWithAddress(addressBits, hexAddress);
  std::cout << "Writing to cache memory\n";
  if(this->_replacement_queue[indexSet].size() < 4){ //if FIFO isn't full
    for(auto indexBlock = 0; indexBlock < _number_of_ways; ++indexBlock){
      auto blockInfo = blocks[indexBlock].readBlock();
      bool validBit = std::get<0>(blockInfo);
      if(!validBit){
        blocks[indexBlock].writeBlock(true, false, tagOfAddress, data);
        this->_replacement_queue[indexSet].push(indexBlock);
        this->_cache.setBlocksWithAddress(addressBits, blocks);
        // Print what we did
        int tag = BitsToIntegral<int>(tagOfAddress);
        std::stringstream HexTag;
        HexTag << std::hex << tag;
        VariadicTable<std::string, unsigned short, unsigned short, std::string, int, int> vt({"Memory Address", "Set Index", "Block Index", "New Tag", "Data Before", "Data After"});
        vt.addRow(hexAddress, indexSet, indexBlock, HexTag.str(),std::get<3>(blockInfo), data);
        vt.print(std::cout);
        return;
      }
    }
  } else { // if FIFO is full
    auto blockIndex = this->_replacement_queue[indexSet].front();
    auto blockInfo = blocks[blockIndex].readBlock();
    this->_replacement_queue[indexSet].pop();
    this->_replacement_queue[indexSet].push(blockIndex);
    blocks[blockIndex].writeBlock(true, false, tagOfAddress, data);
    int tag = BitsToIntegral<int>(tagOfAddress);
    std::stringstream HexTag;
    HexTag << std::hex << tag;
    VariadicTable<std::string, unsigned short, unsigned short, std::string, int, int> vt({"Memory Address", "Set Index", "Block Index", "New Tag", "Data Before", "Data After"});
    vt.addRow(hexAddress, indexSet, blockIndex, HexTag.str(),std::get<3>(blockInfo), data);
    vt.print(std::cout);
  }
}
