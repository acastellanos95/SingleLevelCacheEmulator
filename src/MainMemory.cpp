//
// Created by andre on 3/12/22.
//

#include <random>
#include <algorithm>
#include <utility>
#include "MainMemory.h"
#include "utils.h"
#include "../lib/VariadicTable.h"
MainMemory::MainMemory(unsigned int size_of_memory) {
  // randomize content of memory
  std::uniform_int_distribution<int> dst(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
  std::default_random_engine gen;
  this->_memory = std::vector<int>(size_of_memory, 0);
  std::generate(this->_memory.begin(), this->_memory.end(), [&dst, &gen](){ return dst(gen); });
}
int MainMemory::readFromMemoryWithAddress(std::vector<bool> address, const std::string& hexAddress) {
  auto indexMemory = BitsToIntegral<size_t>(std::move(address));

  // Print neighbours
  std::cout << "Load Memory Address: " << hexAddress + "\n";
  VariadicTable<std::string, int> vt({"Memory Address", "Data"});
  if(indexMemory !=0)
    vt.addRow(hexAddress+"-1", this->_memory[indexMemory-1]);
  vt.addRow(hexAddress, this->_memory[indexMemory]);
  vt.addRow(hexAddress+"+1", this->_memory[indexMemory+1]);
  vt.print(std::cout);
  return this->_memory[indexMemory];
}

void MainMemory::writeToMemoryWithAddress(std::vector<bool> address, const std::string &hexAddress, int data) {
  auto indexMemory = BitsToIntegral<size_t>(std::move(address));
  auto dataBefore = this->_memory[indexMemory];
  this->_memory[indexMemory] = data;
  // Print neighbours
  std::cout << "Edit Memory Address: " << hexAddress + "\n";
  VariadicTable<std::string, int, int> vt({"Memory Address", "Data Before", "Data After"});
  if(indexMemory !=0)
    vt.addRow(hexAddress+"-1", this->_memory[indexMemory-1], this->_memory[indexMemory-1]);
  vt.addRow(hexAddress, dataBefore, this->_memory[indexMemory]);
  vt.addRow(hexAddress+"+1", this->_memory[indexMemory+1], this->_memory[indexMemory+1]);
  vt.print(std::cout);
}
MainMemory::MainMemory() {

}


