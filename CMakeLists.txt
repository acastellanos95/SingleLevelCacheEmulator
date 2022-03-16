cmake_minimum_required(VERSION 3.21)
project(CacheCPP)

set(CMAKE_CXX_STANDARD 17)
add_executable(CacheCPP src/main.cpp src/CacheMemory.cpp src/CacheMemory.h src/Block.cpp src/Block.h src/Set.cpp src/Set.h src/utils.h src/MainMemory.cpp src/MainMemory.h lib/VariadicTable.h src/SingleLevelCache.cpp src/SingleLevelCache.h)