cmake_minimum_required(VERSION 3.16)
# set(CMAKE_CXX_STANDARD 20) set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE debug) set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
# -std=c++20")
set(CMAKE_CXX_FLAGS_DEBUG "-pg")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(Advent-of-code-2022)

find_package(Eigen3 3.4 REQUIRED)
find_package(fmt REQUIRED)

set(ABSL_PROPAGATE_CXX_STD ON)
include(FetchContent)
FetchContent_Declare(
  abseil-cpp
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp
  GIT_TAG lts_2022_06_23)
FetchContent_MakeAvailable(abseil-cpp)

set(LIBRARIES ${Eigen_LIBRARIES} fmt::fmt absl::base absl::synchronization
              absl::strings)

foreach(n RANGE 1 25)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/day${n}.cpp)
    add_executable(day${n} src/day${n}.cpp)
    target_include_directories(day${n} PUBLIC ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(day${n} PRIVATE ${LIBRARIES})
    # set_property(TARGET day${n} PROPERTY CXX_STANDARD 17)
  endif()
endforeach()
