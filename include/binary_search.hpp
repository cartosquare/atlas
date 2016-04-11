#ifndef __binary_search__hpp__
#define __binary_search__hpp__

#include <vector>

namespace atlas {
    
    template<typename T>
    T BinarySearch(T* sorted_array, int N, T target) {
        int lo = 0;
        int hi = N;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (target > sorted_array[mid]) {
                lo = mid + 1;
            } else if (target < sorted_array[mid]) {
                hi = mid - 1;
            } else {
                return mid;
            }
        }
        return -1;
    }
}

#endif