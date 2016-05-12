#include "catch.hpp"

#include "symbol_table.hpp"

using namespace atlas;

TEST_CASE("Symbol Table test", "[symbol table]") {
    SECTION("Linked List Implematation") {
        LinkedListSymbolTable<char, int> st;
        st.put('S', 0);
        st.put('E', 1);
        st.put('A', 2);
        st.put('R', 3);
        st.put('C', 4);
        st.put('H', 5);
        st.put('E', 6);
        st.put('X', 7);
        st.put('A', 8);
        st.put('M', 9);
        st.put('P', 10);
        st.put('L', 11);
        st.put('E', 12);
        
        REQUIRE(st.size() == 10);
        REQUIRE(st.get_value('E') == 12);
        REQUIRE(st.get_value('S') == 0);
        REQUIRE(st.get_value('H') == 5);
        REQUIRE(st.get_value('A') == 8);
        st.delete_key('A');
        REQUIRE(st.get('A') == nullptr);
        REQUIRE(st.size() == 9);
    }
    
    SECTION("Ordered Array Implematation") {
        OrderedArraySymbolTable<char, int> st;
        st.put('S', 0);
        st.put('E', 1);
        st.put('A', 2);
        st.put('R', 3);
        st.put('C', 4);
        st.put('H', 5);
        st.put('E', 6);
        st.put('X', 7);
        st.put('A', 8);
        st.put('M', 9);
        st.put('P', 10);
        st.put('L', 11);
        st.put('E', 12);
        
        REQUIRE(st.size() == 10);
        REQUIRE(st.get('E') == 12);
        REQUIRE(st.get('S') == 0);
        REQUIRE(st.get('H') == 5);
        REQUIRE(st.get('A') == 8);
        
        st.delete_key('A');
        
        REQUIRE(st.size() == 9);
    }
}


