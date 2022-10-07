#include "list.h"
#include <catch2/catch_test_macros.hpp>

const int expected[] = {1, 2, 3, 4, 5};

TEST_CASE( "Creating an empty list", "[list ctor]" ) {
    auto numbers = wittenberg::list<int>{};
    REQUIRE(numbers.empty());
}

TEST_CASE( "Creating a list from initializer list", "[list ctor]" ) {
    auto numbers = wittenberg::list{1, 2, 3, 4, 5};
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Creating a list from another list", "[list copy ctor]" ) {
    auto numbers = wittenberg::list{1, 2, 3, 4, 5};
    auto numbers_copy = wittenberg::list{numbers};
    REQUIRE(numbers_copy.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Copy assigning a list", "[list copy assignment]" ) {
    auto numbers = wittenberg::list{3, 2, 1};
    auto other = wittenberg::list{1, 2, 3, 4, 5};
    numbers = other;
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}
