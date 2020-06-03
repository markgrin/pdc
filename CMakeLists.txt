cmake_minimum_required(VERSION 2.8)
project(voip)
find_package(Boost REQUIRED )

set (ANALYZER_SRC src/main.cpp
                  src/core.cpp
                  src/simulate.cpp
                  src/math/emp_dist.cpp
                  src/math/berlang.cpp
                  src/math/bern_stat.cpp
                  src/math/bin_poi.cpp
                  src/commands/commands.cpp
                  src/commands/generate.cpp
                  src/commands/dataset_io.cpp)
set(TESTER_SRC tests/main.c)

add_executable(analyzer ${ANALYZER_SRC})
target_compile_features(analyzer PRIVATE cxx_std_17)

add_executable(tester ${TESTER_SRC})
target_link_libraries(tester uv)

