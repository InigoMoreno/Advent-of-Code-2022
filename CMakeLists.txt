cmake_minimum_required(VERSION 3.16)
# set(CMAKE_CXX_STANDARD 20) set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE debug) set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
# -std=c++20")

project(Advent-of-code-2022)

find_package(Eigen3 3.4 REQUIRED)
find_package(fmt REQUIRED)

# add_library(utils src/utils.cpp) target_include_directories(utils PUBLIC
# ${PROJECT_SOURCE_DIR}/include)

set(LIBRARIES ${Eigen_LIBRARIES} fmt::fmt)

function(add_day n)
  add_executable(day${n} src/day${n}.cpp)
  target_include_directories(day${n} PUBLIC ${PROJECT_SOURCE_DIR}/include)
  target_link_libraries(day${n} PRIVATE ${LIBRARIES})
endfunction()

add_day(1)
