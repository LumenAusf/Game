cmake_minimum_required(VERSION 3.9)
project(GameIsOn)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -pedantic")

set(SOURCEPATH "../Game(Source)/Source/")
file(GLOB files "${SOURCEPATH}*.cpp")
file(GLOB filesexecut "../Game(Source)/*.cpp")
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_library(engine SHARED ${files} "${SOURCEPATH}engine.h")
target_compile_features(engine PUBLIC cxx_std_17)
find_library(SDL2_LIB NAMES SDL2)
target_link_libraries(engine -lSDL2 ${OPENGL_LIBRARIES} -lGLEW)
add_executable(game ${filesexecut} "../Game(Source)/src/audio.c")
target_compile_features(game PUBLIC cxx_std_17)
target_link_libraries(game engine)

#**********************************************************************



#find_library(SDL2_LIB NAMES SDL2)

#add_executable(game ${filesexecut} "../Game(Source)/src/audio.c" ${files} "${SOURCEPATH}engine.h")
#target_link_libraries(game -lSDL2 -lGL)
#target_compile_features(game PUBLIC cxx_std_17)
