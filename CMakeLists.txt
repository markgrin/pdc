cmake_minimum_required(VERSION 2.8)
project(voip)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set (ANALYZER_SRC src/main.cpp
                  src/core.cpp
                  src/simulate.cpp
                  src/commands/commands.cpp
                  src/commands/generate.cpp)

add_executable(analyzer ${ANALYZER_SRC})
