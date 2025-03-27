cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(solver)

add_library(${PROJECT_NAME} SHARED
    src/Matrix.cpp
    src/Fractional.cpp
    src/Solver.cpp
    src/Util.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC inc)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)