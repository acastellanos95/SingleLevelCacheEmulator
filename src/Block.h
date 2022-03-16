//
// Created by andre on 3/11/22.
//

#ifndef CACHECPP_SRC_BLOCK_H_
#define CACHECPP_SRC_BLOCK_H_

#include <tuple>
#include <vector>

class Block {
 private:
  bool _valid;
  bool _dirty;
  std::vector<bool> _tag;
  int _data;
 public:
  Block(unsigned short number_bits_tag);
  std::tuple<bool, bool, std::vector<bool>, int> readBlock() const;
  void writeBlock(bool valid, bool dirty, std::vector<bool> tag, int data);
  friend bool operator==(const Block &block1, const Block &block2);
};

#endif //CACHECPP_SRC_BLOCK_H_
