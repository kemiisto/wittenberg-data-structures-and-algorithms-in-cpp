cmake_minimum_required(VERSION 3.23)
project(wittenberg_data_structures_and_algorithms_in_cpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

find_package(Catch2 REQUIRED)

set(TESTS
    test_vector
    test_list)

foreach(TEST IN LISTS TESTS)
    message(STATUS ${TEST})
    add_executable(${TEST} test/${TEST}.cpp)
    target_link_libraries(${TEST} PRIVATE Catch2::Catch2WithMain)
endforeach()
