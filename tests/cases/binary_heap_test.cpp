#include "catch.hpp"
#include "binary_heap.hpp"

TEST_CASE("binary heap", "[binary heap]") {
    
    SECTION("binary heap") {
        atlas::MaxPriorityQueue<char> max_pq(100);
        max_pq.insert('T');
        max_pq.insert('P');
        max_pq.insert('R');
        max_pq.insert('N');
        max_pq.insert('H');
        max_pq.insert('O');
        max_pq.insert('A');
        max_pq.insert('E');
        max_pq.insert('I');
        max_pq.insert('G');
        
        max_pq.insert('S');
        
        REQUIRE(max_pq.delMax() == 'T');
        REQUIRE(max_pq.delMax() == 'S');
        
    }
}