cmake_minimum_required(VERSION 3.21)

project(gooey-project LANGUAGES CXX)

file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/android-build)

add_subdirectory(gooey)
add_subdirectory(gooey-base)
add_subdirectory(gooey-qt)
add_subdirectory(Examples)
