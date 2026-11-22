cmake_minimum_required(VERSION 3.20)
project(MergeSortP3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Program demonstracyjny.
add_executable(mergesort main.cpp)

target_include_directories(
        mergesort
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
)

include(CTest)

if(BUILD_TESTING)
    # Najpierw szukamy GoogleTest w systemie.
    find_package(GTest CONFIG QUIET)

    # Jesli go nie ma, pobieramy ustalona wersje.
    if(NOT GTest_FOUND)
        include(FetchContent)

        if(POLICY CMP0135)
            cmake_policy(SET CMP0135 NEW)
        endif()

        FetchContent_Declare(
                googletest
                URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
                URL_HASH SHA256=40d4ec942217dcc84a9ebe2a68584ada7d4a33a8ee958755763278ea1c5e18ff
        )

        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
        set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

        FetchContent_MakeAvailable(googletest)
    endif()

    # Osobny program z testami.
    add_executable(
            mergesort_tests
            MergeSortTests.cpp
    )

    target_include_directories(
            mergesort_tests
            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    target_link_libraries(
            mergesort_tests
            PRIVATE GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(mergesort_tests)
endif()