cmake_minimum_required(VERSION 3.5)
project(ip_filter)

find_package(GTest REQUIRED)
find_package (Threads REQUIRED)

add_executable(ip_filter ip_filter.cpp main.cpp)

add_executable(filter_tests filter_tests.cpp ip_filter.cpp)

set_target_properties(ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;-Werror"
        )

set_target_properties(filter_tests PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
        )

target_link_libraries(filter_tests ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS ip_filter RUNTIME DESTINATION bin)

enable_testing()

add_test(test filter_tests)