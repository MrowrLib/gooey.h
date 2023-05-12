cmake_minimum_required(VERSION 3.21)

project(gooey-project LANGUAGES CXX)

# add_executable("TESTING" Examples/Cpp/Test.cpp)

add_subdirectory(gooey)
add_subdirectory(gooey-base)
add_subdirectory(gooey-qt)
add_subdirectory(Examples)

# add_executable("Test123" foo.cpp)