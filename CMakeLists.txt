cmake_minimum_required(VERSION 3.26)
project(KnapsackProblem_NEDP)

set(CMAKE_CXX_STANDARD 17)

add_executable(KnapsackProblem_NEDP main.cpp
        dynamic_programming.h
        dynamic_programming.cpp
        read_problem.cpp
        read_problem.h)
