cmake_minimum_required(VERSION 3.0.0)
project(autograder_test VERSION 0.1.0)

set(GCC_COMPILER_FLAGS "-fsanitize=address -fsanitize=undefined -Werror -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILER_FLAGS}")

add_subdirectory(lib/project3-main)

add_library(dlist src/dlist.cpp)

add_executable(dlist tests/dlist.cpp)
target_link_libraries(search_tests PRIVATE Catch2::Catch2WithMain search)

add_executable(word_analysis_tests tests/word_analysis_tests.cpp)
target_link_libraries(word_analysis_tests PRIVATE Catch2::Catch2WithMain word_analysis)

add_executable(reverse_array_tests tests/reverse_array_tests.cpp)
target_link_libraries(reverse_array_tests PRIVATE Catch2::Catch2WithMain reverse_array)

add_executable(main main.cpp)
target_link_libraries(main reverse_array word_analysis search)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
