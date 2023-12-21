cmake_minimum_required(VERSION 3.26)
project(KnapsackProblem_NEDP)

set(CMAKE_CXX_STANDARD 17)


AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} DIR_CUR)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(GMP REQUIRED)
add_executable(KnapsackProblem_NEDP ${DIR_SRCS} ${DIR_CUR})

target_link_libraries(KnapsackProblem_NEDP gmp gmpxx)
