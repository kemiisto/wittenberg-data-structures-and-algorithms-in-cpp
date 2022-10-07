#include "vector.h"
#include <vector>
#include <catch2/catch_test_macros.hpp>

const int expected[] = {1, 2, 3, 4, 5};

TEST_CASE( "Creating an empty vector", "[vector default ctor]" ) {
    auto numbers = wittenberg::vector<int>{};
    REQUIRE(numbers.empty());
}

TEST_CASE( "Creating a vector of 5 default-initialized integers", "[vector ctor]" ) {
    auto numbers = wittenberg::vector<int>(5);
    REQUIRE(numbers.size() == 5);
    REQUIRE(numbers.front() == int{});
    REQUIRE(numbers.back() == int{});
}

TEST_CASE( "Creating a vector of 5 ones", "[vector ctor]" ) {
    auto numbers = wittenberg::vector<int>(5, 1);
    REQUIRE(numbers.size() == 5);
    REQUIRE(numbers.front() == 1);
    REQUIRE(numbers.back() == 1);
}

TEST_CASE( "Creating a vector from initializer list", "[vector initializer list ctor]" ) {
    auto numbers = wittenberg::vector{1, 2, 3, 4, 5};
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Creating a vector from another vector", "[vector copy ctor]" ) {
    auto numbers = wittenberg::vector{1, 2, 3, 4, 5};
    auto numbers_copy = wittenberg::vector{numbers};
    REQUIRE(numbers_copy.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Copy assigning a vector", "[vector copy assignment]" ) {
    auto numbers = wittenberg::vector{3, 2, 1};
    auto other = wittenberg::vector{1, 2, 3, 4, 5};
    numbers = other;
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Using operator square brackets", "[vector operator square brackets]" ) {
    auto numbers = wittenberg::vector{1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        numbers[i] = expected[i];
    }
}

TEST_CASE( "Using at method", "[vector at method]" ) {
    auto numbers = wittenberg::vector{1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        numbers.at(i) = expected[i];
    }
    REQUIRE_THROWS_AS(numbers.at(-1), std::out_of_range);
}

TEST_CASE( "Using push_back method", "[vector push_back method]" ) {
    auto numbers = wittenberg::vector{1, 2, 3};
    numbers.push_back(4);
    numbers.push_back(5);
    REQUIRE(numbers.size() == 5);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Using pop_back method", "[vector pop_back method]" ) {
    auto numbers = wittenberg::vector{1, 2, 3, 4, 5};
    numbers.pop_back();
    REQUIRE(numbers.size() == 4);
    auto i = 0;
    for (auto actual : numbers) {
        REQUIRE(actual == expected[i]);
        ++i;
    }
}

TEST_CASE( "Resizing a vector", "[vector resize]" ) {
    auto numbers = wittenberg::vector{1, 2, 3};
    numbers.resize(4, 5);
    REQUIRE(numbers.size() == 4);
    REQUIRE(numbers.back() == 5);
}
