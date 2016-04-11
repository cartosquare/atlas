#ifndef __utility__hpp__
#define __utility__hpp__

#include <cstdlib>
#include <ctime>

namespace atlas {
    // link list Node
    template <typename T>
    struct Node {
        T item;
        Node<T>* next;
    };

    template<typename T>
    void exch(T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
    
    template<typename T>
    void shuffle(std::vector<T>& a) {
        std::srand(std::time(0));
        
        for (size_t i = 1; i < a.size(); ++i) {
            int idx = std::rand() % i;
            
            exch(a[idx], a[i]);
        }
    }
    
    template<typename T>
    int median_of_three(std::vector<T>& a, int t1, int t2, int t3) {
        // find max
        T a1 = a[t1];
        T a2 = a[t2];
        T a3 = a[t3];
        
        if ((a1 - a2) * (a1 - a3) <= 0) {
            return t1;
        } else if ((a2 - a1) * (a2 - a3) <= 0) {
            return t2;
        } else {
            return t3;
        }
        
    }
}
#endif