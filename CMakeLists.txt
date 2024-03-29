cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Build code coverage" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

# TODO: rename project and delete this comment
project(algorithms_and_data_structs VERSION 0.1.0)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(${PROJECT_NAME} STATIC
        #         enum your files and delete this comment
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/my_stack.cpp
        )

add_executable(demo
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )

target_link_libraries(demo ${PROJECT_NAME})

if (BUILD_TESTS)
    add_executable(tests
            #             TODO: enum your files and delete this comment
            ${CMAKE_CURRENT_SOURCE_DIR}
            tests/my_stack_test.cpp
            tests/red_black_tree_test.cpp
            tests/avl_tree_test.cpp
            tests/splay_tree_test.cpp
            tests/two_three_tree_test.cpp
            tests/b_tree_test.cpp
            )

    target_link_libraries(tests ${PROJECT_NAME} GTest::gtest_main)
    enable_testing()
    add_test(NAME unit_tests COMMAND tests)
endif ()
#
#if (BUILD_COVERAGE)
#    set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
#    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/coverage/cmake")
#    find_package(codecov)
#    string(APPEND CMAKE_CXX_FLAGS " --coverage")
#    add_coverage(tests)
#    coverage_evaluate()
#endif ()
