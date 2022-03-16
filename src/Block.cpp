//
// Created by andre on 3/11/22.
//

#include "Block.h"

#include <utility>
Block::Block(unsigned short number_bits_tag) : _data(0), _dirty(false), _valid(false){
  _tag = std::vector<bool>(number_bits_tag, false);
}
std::tuple<bool, bool, std::vector<bool>, int> Block::readBlock() const {
  return std::make_tuple(_valid, _dirty, _tag, _data);
}
void Block::writeBlock(bool valid, bool dirty, std::vector<bool> tag, int data) {
  this->_valid = valid;
  this->_dirty = dirty;
  this->_tag = std::move(tag);
  this->_data = data;
}
bool operator==(const Block &block1, const Block &block2) {
  if(block1._valid != block2._valid)
    return false;
  if(block1._dirty != block2._dirty)
    return false;
  if(block1._data != block2._data)
    return false;
  if(block1._tag != block2._tag)
    return false;
  return true;
}

