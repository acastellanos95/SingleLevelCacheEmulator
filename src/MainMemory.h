//
// Created by andre on 3/12/22.
//

#ifndef CACHECPP_SRC_MAINMEMORY_H_
#define CACHECPP_SRC_MAINMEMORY_H_

#include <vector>
class MainMemory {
 private:
  std::vector<int> _memory;
 public:
  MainMemory();
  MainMemory(unsigned int size_of_memory);
  int readFromMemoryWithAddress(std::vector<bool> address, const std::string& hexAddress);
  void writeToMemoryWithAddress(std::vector<bool> address, const std::string& hexAddress, int data);
};

#endif //CACHECPP_SRC_MAINMEMORY_H_
