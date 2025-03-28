cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(my_solution)

option(SOLVER_ENABLE_UTIL "Builds solver utility" ON)
option(SOLVER_ENABLE_TESTS "Tests for the solver library" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Shared libs also go into bin folder

add_subdirectory(libsolver)
if(SOLVER_ENABLE_UTIL)
    add_subdirectory(solveutil)
endif()
if(SOLVER_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(solvertests)
endif()