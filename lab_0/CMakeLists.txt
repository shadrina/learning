cmake_minimum_required(VERSION 3.8)
project(lab_0)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp module1.h module2.h module1.cpp module2.cpp module3.h module3.cpp)
add_executable(lab_0 ${SOURCE_FILES})