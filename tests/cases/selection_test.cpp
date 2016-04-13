#include "catch.hpp"

#include "selection.hpp"

TEST_CASE("selection", "[selection]") {
    std::vector<int> b = {1, 4, 0, 4, 12, 90, 35, 21, 0, 89, 3};
    
    REQUIRE(atlas::select(b, 0) == 0);
    REQUIRE(atlas::select(b, 1) == 0);
    REQUIRE(atlas::select(b, 2) == 1);
    REQUIRE(atlas::select(b, 3) == 3);
    REQUIRE(atlas::select(b, 4) == 4);
    REQUIRE(atlas::select(b, 5) == 4);
    REQUIRE(atlas::select(b, 6) == 12);
    REQUIRE(atlas::select(b, 7) == 21);
    REQUIRE(atlas::select(b, 8) == 35);
    REQUIRE(atlas::select(b, 9) == 89);
    REQUIRE(atlas::select(b, 10) == 90);
}