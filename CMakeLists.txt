cmake_minimum_required(VERSION 3.16)
# set(CMAKE_CXX_STANDARD 20) set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE debug) set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
# -std=c++20")

project(Advent-of-code-2022)

find_package(Eigen3 3.3 REQUIRED)
link_directories(${Eigen_INCLUDE_DIRS})

# add_library(utils src/utils.cpp)
# target_include_directories(utils PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(LIBRARIES ${Eigen_LIBRARIES})

add_executable(day1 src/day1.cpp)
target_include_directories(day1 PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(day1 PRIVATE ${LIBRARIES})
