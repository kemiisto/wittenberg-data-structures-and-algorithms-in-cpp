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

TEST_CASE( "Inserting into a list at the beginning", "[list insert]" ) {
    auto numbers = wittenberg::list{2, 3, 4, 5};
    numbers.insert(numbers.begin(), 1);
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Inserting into a list at the end", "[list insert]" ) {
    auto numbers = wittenberg::list{1, 2, 3, 4};
    numbers.insert(numbers.end(), 5);
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Inserting into a list in the middle", "[list insert]" ) {
    auto numbers = wittenberg::list{1, 2, 4, 5};
    auto it = numbers.begin();
    it++;
    numbers.insert(++it, 3);
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Erasing at the beginning", "[list erase]" ) {
    auto numbers = wittenberg::list{0, 1, 2, 3, 4, 5};
    numbers.erase(numbers.begin());
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Erasing at the end", "[list erase]" ) {
    auto numbers = wittenberg::list{1, 2, 3, 4, 5, 6};
    auto it = numbers.begin();
    it++; it++; it++; it++; it++;
    numbers.erase(it);
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Erasing in the middle", "[list erase]" ) {
    auto numbers = wittenberg::list{1, 2, 3, 3, 4, 5};
    auto it = numbers.begin();
    it++; it++;
    numbers.erase(it);
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}
