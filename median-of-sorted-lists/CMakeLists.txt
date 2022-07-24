cmake_minimum_required(VERSION 3.22)
project(MedianOfSortedLists)

set(CMAKE_CXX_STANDARD 17)

add_library(
        solution
        solution.cc
)
target_include_directories(solution PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# https://github.com/emil-e/rapidcheck/issues/242
set(RC_ENABLE_GTEST ON CACHE BOOL "Rapidcheck GTest Support" FORCE)
FetchContent_Declare(
        rapidcheck
        GIT_REPOSITORY https://github.com/emil-e/rapidcheck.git
        GIT_TAG 8fafda42e732164db58003e542196e94a28481f9
)
FetchContent_MakeAvailable(rapidcheck)

enable_testing()

add_executable(
        solution_test
        solution_test.cc
)

# https://github.com/emil-e/rapidcheck/issues/242
#message("rapidcheck source: ${rapidcheck_SOURCE_DIR}")
target_include_directories(solution_test PUBLIC ${rapidcheck_SOURCE_DIR}/extras/gtest/include)

target_link_libraries(
        solution_test
        solution
        rapidcheck
        rapidcheck_gtest
        gtest_main
)

add_executable(
        solution_rapidcheck
        solution_rapidcheck.cc
)

target_link_libraries(
        solution_rapidcheck
        solution
        rapidcheck
)

include(GoogleTest)
gtest_discover_tests(solution_test)