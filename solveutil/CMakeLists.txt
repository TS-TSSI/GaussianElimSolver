cmake_minimum_required(VERSION 3.26)
project(solveutil VERSION 1.0.0)

add_executable(${PROJECT_NAME} 
    main.cpp
)

configure_file(config.input headers/config.h)
target_include_directories(${PROJECT_NAME} 
    PRIVATE ${PROJECT_BINARY_DIR}/headers
)

target_link_libraries(${PROJECT_NAME} solver)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)