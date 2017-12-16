cmake_minimum_required(VERSION 3.9)
project(GameIsOn)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

set(SOURCEPATH "../Game(Source)/Source/")

add_library(engine SHARED "${SOURCEPATH}engine.cpp" "${SOURCEPATH}engine.h" "${SOURCEPATH}EventBase.cpp")
target_compile_features(engine PUBLIC cxx_std_17)


find_library(SDL2_LIB NAMES SDL2)


target_link_libraries(engine
               -lSDL2
                -lGL
               )


add_executable(game "../Game(Source)/main.cpp" "../Game(Source)/src/audio.c")
target_compile_features(game PUBLIC cxx_std_17)

target_link_libraries(game engine)

#**********************************************************************



#find_library(SDL2_LIB NAMES SDL2)

#add_executable(game "../Game(Source)/main.cpp" "${SOURCEPATH}engine.cpp" "${SOURCEPATH}engine.h" "${SOURCEPATH}EventBase.cpp")

#target_link_libraries(game -lSDL2 -lGL)

#target_compile_features(game PUBLIC cxx_std_17)
