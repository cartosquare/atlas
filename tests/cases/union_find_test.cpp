#include "catch.hpp"

#include "union_find.hpp"

using namespace atlas;

TEST_CASE("union-find test", "[union-find]") {
    SECTION("") {
        WeightedUnionFind uf(10);
        uf.Union(4, 3);
        uf.Union(3, 8);
        uf.Union(6, 5);
        uf.Union(9, 4);
        uf.Union(2, 1);
        uf.Union(5, 0);
        uf.Union(7, 2);
        
        REQUIRE(uf.Connected(2, 1));
        REQUIRE(uf.Connected(2, 7));
        REQUIRE(uf.Connected(4, 3));
        REQUIRE(uf.Connected(4, 8));
        REQUIRE(uf.Connected(4, 9));
        REQUIRE(uf.Connected(6, 0));
        REQUIRE(uf.Connected(6, 5));
        
        REQUIRE(!uf.Connected(4, 6));
        REQUIRE(!uf.Connected(4, 2));
        REQUIRE(!uf.Connected(2, 6));
        REQUIRE(!uf.Connected(1, 3));
        REQUIRE(!uf.Connected(7, 0));
        REQUIRE(!uf.Connected(5, 8));
    }
}


