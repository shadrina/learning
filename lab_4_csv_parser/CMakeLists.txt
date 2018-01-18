cmake_minimum_required(VERSION 3.9)
project(lab_4_csv_parser)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab_4_csv_parser main.cpp CSVParser.h Keywords.h subtask_1_print_tuple/print_tuple.h Exception.cpp Exception.h)