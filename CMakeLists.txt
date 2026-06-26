cmake_minimum_required(VERSION 3.27)

project(sw_battle_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sw_battle_test)
