cmake_minimum_required(VERSION 2.8)

project(GameIsOn)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${PROJECT_NAME} "main.cpp" "engine.cpp")
find_library(SDL2_LIB libSDL2.so)
target_link_libraries(${PROJECT_NAME}
    -lSDL2)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
