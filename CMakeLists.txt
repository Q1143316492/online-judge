cmake_minimum_required(VERSION 3.13)
project(Study)

set(CMAKE_CXX_STANDARD 14)

add_executable(Study main.cpp include/util.h include/judgeResult.h include/Problem.h include/OnlineJudge.h)