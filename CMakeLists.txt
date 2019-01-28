cmake_minimum_required(VERSION 2.8)

project(TestChain)

set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")


set(TESTCHAIN_SOURCES
			Blockchain.cpp
			Block.cpp
			main.cpp
			sha256.cpp)

include_directories(./)

add_executable(TestChain ${TESTCHAIN_SOURCES})

