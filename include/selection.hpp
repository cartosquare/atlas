#ifndef __selection__hpp__
#define __selection__hpp__

#include "sort.hpp"

namespace atlas {
    // Selection
    // Goal. Given an array of N items, find the kth largest.
    
    // Quick-select
    // Partition array so that:
    // * Entry a[j] is in place.
    //  - No larger entry to the left of j.
    //  - No smaller entry to the right of j.
    // Repeat in one subarray, depending on j;
    // finished when j equals k.
    template<typename T>
    T select(std::vector<T>& a, int k) {
        shuffle(a);
        
        int lo = 0;
        int hi = a.size() - 1;
        while (hi > lo) {
            int j = partition(a, lo, hi);
            if (j < k) {
                lo = j + 1;
            } else if ( j > k) {
                hi = j - 1;
            } else {
                return a[k];
            }
        }
        return a[k];
    }
}


#endif