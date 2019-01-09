cmake_minimum_required(VERSION 2.8.8)

project(hsg) # TODO: give a real name to your project here

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(SimGrid 3.21 REQUIRED) # This template requires SimGrid v3.21

include_directories(${SimGrid_INCLUDE_DIR})


add_executable(hsg 

messages/Message.cpp
distributions/RandClass.cpp
hdfs/NameNode.cpp
hdfs/Chunk.cpp
hdfs/DirFiles.cpp
hdfs/Client.cpp
hdfs/HdfsClient.cpp
hdfs/HdfsFile.cpp
hdfs/DataNode.cpp
Main.cpp
)
target_link_libraries(hsg ${SimGrid_LIBRARY})

