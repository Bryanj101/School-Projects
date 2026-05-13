cmake_minimum_required(VERSION 3.20)
project(Stack)

set(CMAKE_CXX_STANDARD 14)

add_executable(Stack main.cpp Stack.cpp Stack.h Matrix.cpp Matrix.h Tokenizer.cpp Tokenizer.h Commands.cpp Commands.h)
