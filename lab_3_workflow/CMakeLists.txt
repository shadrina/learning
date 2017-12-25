cmake_minimum_required(VERSION 3.8)
project(lab_3_workflow)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Command.cpp Command.h TextEditor.cpp TextEditor.h Workflow.cpp Workflow.h Keys.h Parser.cpp Parser.h exceptions/Exception.cpp exceptions/Exception.h)
add_executable(lab_3_workflow ${SOURCE_FILES})