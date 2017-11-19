cmake_minimum_required(VERSION 3.9)
project(GameIsOn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

add_executable(${PROJECT_NAME} main.cpp engine.cpp DelegateAndEvent/EventBase.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_library(SDL2_LIB libSDL2.so)

target_link_libraries(${PROJECT_NAME} -lSDL2)

