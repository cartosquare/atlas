#ifndef __sort__hpp__
#define __sort__hpp__

#include "utility.hpp"
#include <vector>
#include <iostream>

// Sorting algorithms: summary
/*
                   inplace?    stable?      worst     average     best        remarks
 selection    |      yes   |    no     |   N*N/2  |   N*N/2   |  N*N/2   | N exchanges
 insertion    |      yes   |    yes    |   N*N/2  |   N*N/4   |    N     | use for small N or partially ordered
   shell      |      yes   |    no     |     ?    |     ?     |    N     | tight code, subquadratic
   quick      |      yes   |    no     |   N*N/2  |   2*N*lgN |  N*lgN   | NlogN probalilistic guarantee fastest in practice
 3-way quick  |      yes   |    no     |   N*N/2  |   2*N*lgN |    N     | improve quicksort in presence of dumplicate keys
   merge      |      no    |    yes    |   N*lgN  |    N*lgN  |  N*lgN   | NlogN guarantee, stable
   heap       |      yes   |    no     |  2*N*lgN |   2*N*lgN |  N*lgN   | NlogN guarantee, in-place
   ???        |      yes   |    yes    |   N*lgN  |    N*logN |  N*lgN   | holy sorting grail
 */

namespace atlas {
    // Selection sort
    
    // implemation:
    // sort an array of N, loop from 0 to N - 1,
    // in iteration i, find index min of smallest remaining entry
    // swap a[i] and a[min]
    
    // proterties:
    // Running time insensitive to input. Quadratic time, even if input is sorted.
    // Data movement is minimal. Linear number of exchanges.
    template<typename T>
    void selection_sort(std::vector<T>& a, int lo, int hi) {
        for (int i = lo; i <= hi; ++i) {
            int min_index = i;
            
            for (int j = i + 1; j <= hi; ++j) {
                if (a[min_index] > a[j]) {
                    min_index = j;
                }
            }
            
            // swap a[i] and a[min_index]
            exch(a[i], a[min_index]);
        }
    }
    
    
    // Insertion sort
    
    // implemation:
    // sort an array of N, loop from 0 to N - 1,
    // in iteration i, swap a[i] with each larger entry to its left
    
    // for partially-sorted arrays, insertion sort runs in linear time
    template<typename T>
    void insertion_sort(std::vector<T>& a, int lo, int hi) {
        for (int i = lo; i <= hi; ++i) {
            for (int j = i; j > lo; --j) {
                if (a[j] < a[j - 1]) {
                    exch(a[j], a[j - 1]);
                } else {
                    break;
                }
            }
        }
    }
    
    
    // Shell sort
    // Idea: move entries more than one position at a time by h-sorted array
    // an h-sorted array is h interleaved sorted subsequences
    
    // shellsort: h-sort array for decreasing sequence of values of h
    // wich sequence to use? 3x + 1 -> 1, 4, 13, 40, 121, 364, ...
    
    //  time complex of this sequence: O(N^(3/2))
    
    // this sort method is useful in practice for following reasons:
    // * Fast unless array size is huge
    // * Tiny, fixed footprint for code(used in embedded systems)
    // * Hardware sort prototype
    template<typename T>
    void shell_sort(std::vector<T>& a, int lo, int hi) {
        int N = hi - lo + 1;
        
        // decide decrease sequence
        int h = 1;
        while (h < N / 3) {
            h = 3 * h + 1;
        }
        
        while (h >= 1) {
            // h-sort the array
            for (int i = h + lo; i <= hi; ++i) {
                for (int j = i; j >= h + lo && a[j] < a[j - h]; j -= h) {
                    exch(a[j], a[j - h]);
                }
            }
            h = h / 3;
        }
    }
    
    
    // merge sort
    // N * log(N) !!!
    
    // merge tow subarray
    template<typename T>
    void merge(std::vector<T>& a, std::vector<T>& aux, int lo, int mid, int hi) {
        for (int i = lo; i <= hi; ++i) {
            aux[i] = a[i];
        }
        
        int m = lo;
        int n = mid + 1;
        for (int i = lo; i <= hi; ++i) {
            if (m > mid) {
                a[i] = aux[n++];
            } else if (n > hi) {
                a[i] = aux[m++];
            } else if (aux[n] < aux[m]) {
                a[i] = aux[n++];
            } else {
                a[i] = aux[m++];
            }
        }
    }
    
    // resuive sort
    const int CUTOFF = 7;
    template<typename T>
    void merge_sort(std::vector<T>& a, std::vector<T>& aux, int lo, int hi) {
        if (hi <= lo) {
            return;
        }

        // use insertion sort for small subarrays
        if (hi <= lo + CUTOFF - 1) {
            insertion_sort(a, lo, hi);
            return;
        }

        int mid = lo + (hi - lo) / 2;
        merge_sort(a, aux, lo, mid);
        merge_sort(a, aux, mid + 1, hi);
        
        // do not merge if already sorted
        if (a[mid] < a[mid + 1]) {
            return;
        }
        
        merge(a, aux, lo, mid, hi);
    }
    
    
    // Bottom Up merge sort
    
    // No recursion needed!
    // basic plan:
    // * Pass through array, merging subarrays of size 1.
    // * Repeat for subarrays of size 2, 3, 4, 16 ...
    
    // concise industrial-strength code, if you have enough space
    template<typename T>
    void bottom_up_merge_sort(std::vector<T>& a, std::vector<T>& aux, int lo, int hi) {
        int N = hi - lo + 1;
        for (int sz = 1; sz < N; sz += sz) {
            for (int k = lo; k < lo + N - sz; k += (sz + sz)) {
                merge(a, aux, k, k + sz - 1, std::min(k + sz + sz - 1, N - 1));
            }
        }
    }
    
    
    // Quick sort
    
    // * Shuffle the array
    // * Partition so that, for some j
    //  - entry a[j] is in place
    //  - no larger entry to the left of j
    //  - no smaller entry to the right of j
    // * Sort each piece recursively
    template<typename T>
    int partition(std::vector<T>& a, int lo, int hi) {
        int i = lo;
        int j = hi + 1;
        
        while(true) {
            // process i pointer
            // find item on left to swap
            while(a[++i] < a[lo]) {
                if (i == hi) {
                    break;
                }
            }
            
            // process j pointer
            // find item on right to swap
            while(a[--j] > a[lo]) {
                if (j == lo) {
                    break;
                }
            }
            
            // find if pointers cross
            if (i >= j) {
                break;
            }
            
            // swap
            exch(a[i], a[j]);
        }
        
        // swap with partition item
        exch(a[lo], a[j]);
        
        // return index of item now known to be in place
        return j;
    }
    
    
    template<typename T>
    void quick_sort_sub(std::vector<T>& a, int lo, int hi) {
        if (hi <= lo + CUTOFF) {
            // improvement 1:  use insertion fort for small subarray
            insertion_sort(a, lo, hi);
            return;
        }
        
        // improvement 2: estimate partition item with median of three samples
        int m = median_of_three(a, lo, lo + (hi - lo)/ 2, hi);
        exch(a[lo], a[m]);
        
        int j = partition(a, lo, hi);
        quick_sort_sub(a, lo, j - 1);
        quick_sort_sub(a, j + 1, hi);
    }
    
    template<typename T>
    void quick_sort(std::vector<T>& a) {
        // shuffle is needed for performance guarantee
        shuffle(a);
        
        quick_sort_sub<T>(a, 0, static_cast<int>(a.size()) - 1);
    }
    
    
    // 3-way quik-sort, useful for arrays contain large number of dumplicates
    // Randomized quicksort with 3-way partitioning reduces running time
    // from linearithmic to linear in broad class of applications
    
    // Goal. Partition array into 3 parts so that:
    // * Entries between lt and gt equal to partition item
    // * No larger entries to left of lt
    // * No smaller entries to right of gt
    
    // Implementation:
    // * Let v be partitioning item a[lo].
    // * Scan i from left to right.
    //  - (a[i] < v): exchange a[lt] with a[i]; increment both lt and i
    //  - (a[i] > v): exchange a[gt] with a[i]; decrement gt;
    //  - (a[i] == v): increment i
    template<typename T>
    void quick_sort_3way_sub(std::vector<T>& a, int lo, int hi) {
        if (hi <= lo + CUTOFF) {
            // improvement 1:  use insertion fort for small subarray
            insertion_sort(a, lo, hi);
            return;
        }
        
        int lt = lo;
        int i = lo;
        int gt = hi;
        
        // improvement 2: estimate partition item with median of three samples
        int m = median_of_three(a, lo, lo + (hi - lo)/ 2, hi);
        exch(a[lo], a[m]);
        
        // partition item
        T v = a[lo];
        
        while(i <= gt) {
            if (a[i] < v) {
                exch(a[lt++], a[i++]);
            } else if (a[i] > v) {
                exch(a[i], a[gt--]);
            } else {
                i++;
            }
        }
        
        quick_sort_3way_sub(a, lo, lt - 1);
        quick_sort_3way_sub(a, gt + 1, hi);
    }
    
    template<typename T>
    void quick_sort_3way(std::vector<T>& a) {
        // shuffle is needed for performance guarantee
        shuffle(a);
        
        quick_sort_3way_sub<T>(a, 0, static_cast<int>(a.size()) - 1);
    }
    
    
    
    // Heap Sort
    // Basic plan for in-place sort
    // * Create max-heap with all N keys.
    // * Repeatedly remove the maximum key.
    
    // Heap construction. Build max heap using bottom-up method.
    // Heap construction uses <= 2N compares and exchanges.

    // Sort Down. <= 2NlgN compares and exchanges
    
    // Heap Sort is doing best in in-place sorting with NlogN worst-case.
    // Mergesort: no, linear extra space.
    // Quicksort: no, quadratic time in worst case.
    // Heapsort: yes!
    
    // Heapsort is optimal for both time and space, but:
    // * Inner loop longer than quicksort's
    // * Makes poor use of cache memory
    // * Not stable
    
    template<typename T>
    void sink(std::vector<T>& a, int k, int N) {
        // NOTE: the value of node k is a[k - 1]
        
        // make sure k is not the bottom level
        while (2 * k < N) {
            // j is the left children
            int j = 2 * k;
            if (j < N && a[j - 1] < a[j]) {
                // now, j is the bigger children
                j++;
            }
            
            if (a[k - 1] > a[j - 1]) {
                break;
            }
            
            // if parent node is smaller than the bigger children, exchange
            exch(a[k - 1], a[j - 1]);
            
            // sink down a level
            k = j;
        }
    }
    
    template<typename T>
    void heap_sort(std::vector<T>& pq) {
        int N = pq.size();
        
        // Heap construction
        for (int k = N / 2; k >= 1; --k) {
            // loop for every non leaf node
            sink(pq, k, N);
        }
        
        // Sort down
        while(N > 1) {
            exch(pq[0], pq[N - 1]);
            sink(pq, 1, --N);
        }
    }
    
}

#endif