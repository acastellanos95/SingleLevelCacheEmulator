#include <iostream>
#include <fstream>
#include <algorithm>
#include "Block.h"
#include "Set.h"
#include "utils.h"
#include "MainMemory.h"
#include "CacheMemory.h"
#include "SingleLevelCache.h"

int main(int argc, char *argv[]) {
  // test block
//  Block block = Block(7);
//  auto res = block.readBlock();
//  block.writeBlock(true, true, std::vector<bool>{false, true, false, true, true, false, true}, 45);
//  res = block.readBlock();
  //test set
//  Set set = Set(4, 7);
//  for (int i = 0; i < 4; ++i) {
//    set.writeBlockFromSet(i, true, false, std::vector<bool>{false, true, false, true, true, false, true}, 2 * i + 1);
//  }
  // test hex to bits
//  std::vector<bool> bits = HexToBits<unsigned short>("AD", 6);
  // test bits to integral
//  unsigned short number = BitsToIntegral<unsigned short>(bits);
//  number = NumberAddresableByBitSize<unsigned short>(4);
  // Test memory
//  MainMemory main_memory = MainMemory(2048);
//  main_memory.readFromMemoryWithAddress(HexToBits("80", 11), "80");
//  main_memory.writeToMemoryWithAddress(HexToBits("80", 11), "80", 5264);
  // Test Cache Memory
//  CacheMemory cache_memory = CacheMemory(3,11,4);
//  auto blocks = cache_memory.getBlocksFromAddress(HexToBits("35", 11));
//  blocks[1].writeBlock(true, false, HexToBits("6", 8), 54687);
//  cache_memory.setBlocksWithAddress(HexToBits("35", 11), blocks);
//  auto numberLog = log2<unsigned short >(8);
  // Test single level cache
//  auto cache = SingleLevelCache(1024, 4, 2);
//  cache.read("15");
//  cache.load("1E", 32);

  std::ifstream greeting("../begin.txt", std::ifstream::in);
  std::cout << greeting.rdbuf();
  unsigned short size_of_memory;
  unsigned short number_of_sets;
  unsigned short number_of_ways;
  std::cout << "Introduce el tamaño de memoria (potencias de 2): ";
  std::cin >> size_of_memory;
  std::cout << "Introduce el número de conjuntos (potencias de 2): ";
  std::cin >> number_of_sets;
  std::cout << "Introduce el número de ways (formas) (en potencias de 2): ";
  std::cin >> number_of_ways;
  SingleLevelCache cache = SingleLevelCache(size_of_memory, number_of_sets, number_of_ways);
  bool exit = false;
  while(!exit){
    std::cout << "Instrucción: ";

    std::string command;
    std::string address;
    int data;
    std::cin >> command;
    if(command == "load"){
      std::cin >> address;
      std::cin >> data;
       cache.load(address, data);
    } else if (command == "read"){
      std::cin >> address;
       cache.read(address);
    } else {
      throw std::runtime_error("Comando no correcto\n");
    }

    char exitResponse;
    std::cout << "Quiere salir? (y/n): ";
    std::cin >> exitResponse;
    if(exitResponse == 'y')
      exit = true;
  }
  return 0;
}
