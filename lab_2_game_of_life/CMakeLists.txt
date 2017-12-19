cmake_minimum_required(VERSION 3.8)
project(lab_2_game_of_life)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Entity.cpp Entity.h GameInterface.cpp GameInterface.h Cell.cpp Cell.h ConsoleColor.h exceptions/GOL_Exceptions.cpp exceptions/GOL_Exceptions.h Command.cpp Command.h)
add_executable(lab_2_game_of_life ${SOURCE_FILES})