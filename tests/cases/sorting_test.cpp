#include "catch.hpp"

#include "sort.hpp"

TEST_CASE("sorting", "[sorting]") {
    std::vector<char> a = {'S', 'O', 'R', 'T', 'E', 'X',
        'A', 'M', 'P', 'L', 'E' };
    
    std::vector<int> b = {1, 4, 0, 4, 12, 90, 35, 21, 0, 89, 3};
    
    SECTION("selection sort") {
        atlas::selection_sort<char>(a, 0, a.size() - 1);
        REQUIRE(a[0] == 'A');
        REQUIRE(a[1] == 'E');
        REQUIRE(a[2] == 'E');
        REQUIRE(a[3] == 'L');
        REQUIRE(a[4] == 'M');
        REQUIRE(a[5] == 'O');
        REQUIRE(a[6] == 'P');
        REQUIRE(a[7] == 'R');
        REQUIRE(a[8] == 'S');
        REQUIRE(a[9] == 'T');
        REQUIRE(a[10] == 'X');
        
    }
    SECTION("insertion sort") {
        atlas::insertion_sort<char>(a, 0, a.size() - 1);
        REQUIRE(a[0] == 'A');
        REQUIRE(a[1] == 'E');
        REQUIRE(a[2] == 'E');
        REQUIRE(a[3] == 'L');
        REQUIRE(a[4] == 'M');
        REQUIRE(a[5] == 'O');
        REQUIRE(a[6] == 'P');
        REQUIRE(a[7] == 'R');
        REQUIRE(a[8] == 'S');
        REQUIRE(a[9] == 'T');
        REQUIRE(a[10] == 'X');
        
    }
    
    SECTION("shell sort") {
        atlas::shell_sort<char>(a, 0, a.size() - 1);
        REQUIRE(a[0] == 'A');
        REQUIRE(a[1] == 'E');
        REQUIRE(a[2] == 'E');
        REQUIRE(a[3] == 'L');
        REQUIRE(a[4] == 'M');
        REQUIRE(a[5] == 'O');
        REQUIRE(a[6] == 'P');
        REQUIRE(a[7] == 'R');
        REQUIRE(a[8] == 'S');
        REQUIRE(a[9] == 'T');
        REQUIRE(a[10] == 'X');
    }
    
    SECTION("merge sort") {
        std::vector<char> aux;
        aux.resize(a.size());
        
        atlas::merge_sort(a, aux, 0, a.size() - 1);

        REQUIRE(a[0] == 'A');
        REQUIRE(a[1] == 'E');
        REQUIRE(a[2] == 'E');
        REQUIRE(a[3] == 'L');
        REQUIRE(a[4] == 'M');
        REQUIRE(a[5] == 'O');
        REQUIRE(a[6] == 'P');
        REQUIRE(a[7] == 'R');
        REQUIRE(a[8] == 'S');
        REQUIRE(a[9] == 'T');
        REQUIRE(a[10] == 'X');
        
        std::vector<int> aux2;
        aux2.resize(b.size());
        //std::vector<int> b = { 1, 4, 0, 4, 12, 90, 35, 21, 0, 89, 3 };
        atlas::merge_sort(b, aux2, 0, b.size() - 1);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 0);
        REQUIRE(b[2] == 1);
        REQUIRE(b[3] == 3);
        REQUIRE(b[4] == 4);
        REQUIRE(b[5] == 4);
        REQUIRE(b[6] == 12);
        REQUIRE(b[7] == 21);
        REQUIRE(b[8] == 35);
        REQUIRE(b[9] == 89);
        REQUIRE(b[10] == 90);
        
    }
    
    SECTION("bottom-up merge sort") {
        std::vector<char> aux;
        aux.resize(a.size());
        
        atlas::bottom_up_merge_sort(a, aux, 0, a.size() - 1);
        
        REQUIRE(a[0] == 'A');
        REQUIRE(a[1] == 'E');
        REQUIRE(a[2] == 'E');
        REQUIRE(a[3] == 'L');
        REQUIRE(a[4] == 'M');
        REQUIRE(a[5] == 'O');
        REQUIRE(a[6] == 'P');
        REQUIRE(a[7] == 'R');
        REQUIRE(a[8] == 'S');
        REQUIRE(a[9] == 'T');
        REQUIRE(a[10] == 'X');
        
        std::vector<int> aux2;
        aux2.resize(b.size());
        //std::vector<int> b = { 1, 4, 0, 4, 12, 90, 35, 21, 0, 89, 3 };
        atlas::bottom_up_merge_sort(b, aux2, 0, b.size() - 1);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 0);
        REQUIRE(b[2] == 1);
        REQUIRE(b[3] == 3);
        REQUIRE(b[4] == 4);
        REQUIRE(b[5] == 4);
        REQUIRE(b[6] == 12);
        REQUIRE(b[7] == 21);
        REQUIRE(b[8] == 35);
        REQUIRE(b[9] == 89);
        REQUIRE(b[10] == 90);
        
    }
    
    SECTION("media of three") {
        std::vector<int> a = { 1, 2, 3 };
        REQUIRE(atlas::median_of_three(a, 0, 1, 2) == 1);
        REQUIRE(atlas::median_of_three(a, 1, 0, 2) == 1);
        REQUIRE(atlas::median_of_three(a, 2, 0, 1) == 1);
    }
    
    SECTION("quick sort") {
        atlas::quick_sort(a);
        
        REQUIRE(a[0] == 'A');
        REQUIRE(a[1] == 'E');
        REQUIRE(a[2] == 'E');
        REQUIRE(a[3] == 'L');
        REQUIRE(a[4] == 'M');
        REQUIRE(a[5] == 'O');
        REQUIRE(a[6] == 'P');
        REQUIRE(a[7] == 'R');
        REQUIRE(a[8] == 'S');
        REQUIRE(a[9] == 'T');
        REQUIRE(a[10] == 'X');
        
        
        //std::vector<int> b = { 1, 4, 0, 4, 12, 90, 35, 21, 0, 89, 3 };
        atlas::quick_sort(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 0);
        REQUIRE(b[2] == 1);
        REQUIRE(b[3] == 3);
        REQUIRE(b[4] == 4);
        REQUIRE(b[5] == 4);
        REQUIRE(b[6] == 12);
        REQUIRE(b[7] == 21);
        REQUIRE(b[8] == 35);
        REQUIRE(b[9] == 89);
        REQUIRE(b[10] == 90);
        
    }
    
    SECTION("3 way quick sort") {
        atlas::quick_sort_3way(a);
        
        REQUIRE(a[0] == 'A');
        REQUIRE(a[1] == 'E');
        REQUIRE(a[2] == 'E');
        REQUIRE(a[3] == 'L');
        REQUIRE(a[4] == 'M');
        REQUIRE(a[5] == 'O');
        REQUIRE(a[6] == 'P');
        REQUIRE(a[7] == 'R');
        REQUIRE(a[8] == 'S');
        REQUIRE(a[9] == 'T');
        REQUIRE(a[10] == 'X');
        
        atlas::quick_sort_3way(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 0);
        REQUIRE(b[2] == 1);
        REQUIRE(b[3] == 3);
        REQUIRE(b[4] == 4);
        REQUIRE(b[5] == 4);
        REQUIRE(b[6] == 12);
        REQUIRE(b[7] == 21);
        REQUIRE(b[8] == 35);
        REQUIRE(b[9] == 89);
        REQUIRE(b[10] == 90);
        
    }
    
    SECTION("heap sort") {
        atlas::heap_sort(a);
        
        REQUIRE(a[0] == 'A');
        REQUIRE(a[1] == 'E');
        REQUIRE(a[2] == 'E');
        REQUIRE(a[3] == 'L');
        REQUIRE(a[4] == 'M');
        REQUIRE(a[5] == 'O');
        REQUIRE(a[6] == 'P');
        REQUIRE(a[7] == 'R');
        REQUIRE(a[8] == 'S');
        REQUIRE(a[9] == 'T');
        REQUIRE(a[10] == 'X');
        
        atlas::heap_sort(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 0);
        REQUIRE(b[2] == 1);
        REQUIRE(b[3] == 3);
        REQUIRE(b[4] == 4);
        REQUIRE(b[5] == 4);
        REQUIRE(b[6] == 12);
        REQUIRE(b[7] == 21);
        REQUIRE(b[8] == 35);
        REQUIRE(b[9] == 89);
        REQUIRE(b[10] == 90);
        
    }
}
