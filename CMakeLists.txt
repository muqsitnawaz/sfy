
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(sfy LANGUAGES CXX VERSION 0.0.1)

# Set CXX standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS_DEBUG "-stdlib=libc++ -Wall -Wextra")
    set(CMAKE_C_FLAGS_RELEASE "-O2")
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
endif ()

# Set default build type.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Set compile time macros.
add_compile_definitions(FMT_HEADER_ONLY)

# Find require packages.
find_package(GTest REQUIRED)

# Set include and link dirs.
set(INCLUDE_DIRS /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Ranges.
add_executable(ranges src/ranges.cpp)
target_include_directories(ranges PRIVATE ${INCLUDE_DIRS})

# Tests.
add_executable(test_ranges tests/ranges.cpp)
target_include_directories(test_ranges PRIVATE ${INCLUDE_DIRS})
target_link_libraries(test_ranges PRIVATE ${GTEST_LIBRARIES})