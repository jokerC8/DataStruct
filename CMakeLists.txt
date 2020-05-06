cmake_minimum_required(VERSION 3.6)
project(DataStruct C)
# This for mac osx only
set(CMAKE_MACOSX_RPATH ON)

add_subdirectory(avltree)
add_subdirectory(graph)
add_subdirectory(list)
add_subdirectory(priority_queue)
add_subdirectory(queue)
add_subdirectory(rbtree)
add_subdirectory(stack)
add_subdirectory(tree)
