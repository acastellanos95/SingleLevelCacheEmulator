//
// Created by andre on 3/12/22.
//

#ifndef CACHECPP_SRC_UTILS_H_
#define CACHECPP_SRC_UTILS_H_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

//template<typename T> // should by integral
//std::string HexToDec(std::string hexNumber, T sizeBits){
//  std::vector<bool> res(sizeBits, false);
//
//}


template<typename T> // should by integral, in general it will be unsigned short
std::vector<bool> HexToBits(std::string hexNumber, T sizeBits){
  std::stringstream bin;
  for(auto it = hexNumber.rbegin(); it != hexNumber.rend(); ++it){
    std::stringstream tmp;
    switch (*it) {
      case '0':
        tmp << "0000";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '1':
        tmp << "0001";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '2':
        tmp << "0010";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '3':
        tmp << "0011";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '4':
        tmp << "0100";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '5':
        tmp << "0101";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '6':
        tmp << "0110";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '7':
        tmp << "0111";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '8':
        tmp << "1000";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case '9':
        tmp << "1001";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case 'A':
      case 'a':
        tmp << "1010";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case 'B':
      case 'b':
        tmp << "1011";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case 'C':
      case 'c':
        tmp << "1100";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case 'D':
      case 'd':
        tmp << "1101";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case 'E':
      case 'e':
        tmp << "1110";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      case 'F':
      case 'f':
        tmp << "1111";
        tmp << bin.rdbuf();
        bin = std::move(tmp);
        break;
      default:
        throw std::runtime_error("El número no es hexadecimal\n");
    }
  }

  std::vector<bool> bits(sizeBits, false);
  std::string binaryNumber = bin.str();
  auto itBits = bits.rbegin();
  for(auto itBinaryNumber = binaryNumber.rbegin(); itBinaryNumber != binaryNumber.rend() && itBits != bits.rend(); ++itBinaryNumber, ++itBits){
    if(*itBinaryNumber == '0'){
      *itBits = false;
    } else {
      *itBits = true;
    }
  }
  return bits;
}

template<typename T> //return type, in general it will be unsigned short
T BitsToIntegral(std::vector<bool> numberBits){
  T number = 0;
  T powerOfTwo = 1;
  for(auto itNumberBits = numberBits.rbegin(); itNumberBits != numberBits.rend(); ++itNumberBits){
    if(*itNumberBits){
      number += powerOfTwo*1;
    }
    powerOfTwo *= 2;
  }
  return number;
}

template<typename T> // return type, in general it will be unsigned short
T NumberAddresableByBitSize(T sizeBits){
  T number = 1;
  T count = 0;
  while(count++ < sizeBits){
    number *= 2;
  }
  return number;
}

template<typename T>
T log2(T number){
  double res = log2((double )number);
  return std::round(res);
}

#endif //CACHECPP_SRC_UTILS_H_
