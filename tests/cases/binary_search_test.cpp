#include "catch.hpp"

#include "binary_search.hpp"

#include <iostream>

TEST_CASE("binary search", "[BinarySearch]") {
    
    SECTION("simple test") {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        double b[6] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };
        
        REQUIRE(atlas::BinarySearch(a, 10, 1) == 0);
        REQUIRE(atlas::BinarySearch(a, 10, 5) == 4);
        REQUIRE(atlas::BinarySearch(a, 10, 10) == 9);
        REQUIRE(atlas::BinarySearch(a, 10, 11) == -1);
        REQUIRE(atlas::BinarySearch(a, 10, 0) == -1);
        
        REQUIRE(atlas::BinarySearch(b, 6, 1.1) == 0);
        REQUIRE(atlas::BinarySearch(b, 6, 3.3) == 2);
        REQUIRE(atlas::BinarySearch(b, 6, 6.6) == 5);
        REQUIRE(atlas::BinarySearch(b, 6, 0.0) == -1);
        REQUIRE(atlas::BinarySearch(b, 6, 6.5) == -1);
        REQUIRE(atlas::BinarySearch(b, 6, 2.5) == -1);
    }
}


