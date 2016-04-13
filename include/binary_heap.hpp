#ifndef __binary__heap__hpp__
#define __binary__heap__hpp__

#include "utility.hpp"

namespace atlas {
    // Binary tree. Empty or node with links to left and right binary trees.
    // Complete tree. Perfectly balanced, except for bottom level.
    // Height of complete tree with N nodes is ceil(lgN)
    
    // Binary heap. Array representation of a heap-ordered complete binary tree.
    // Heap-ordered binary tree
    // * keys in nodes.
    // * parent's key no smaller than children's keys
    
    // Array representation
    // * indices start at 1
    // * take nodes in level order
    // * no explicit links needed!
    
    // Largest key is a[1], which is root of binary tree.
    // Can use array indices to move through tree
    // * Parent of node at k is at k / 2.
    // * Children of node at k are at 2k and 2k + 1.
    
    // When we insert nodes to Binary heap, it will comes two Scenario:
    
    // Scenario 1: Child's key becomes larger key than its parent's key.
    // To eliminate the violation:
    // * Exchange key in child with key in parent.
    // * Repeat until heap order restored.
    
    // Scenario 2: Parent's key becomes smaller than one (or both) of this children's.
    // To eliminate the violation:
    // * Exchange key in parent with key in larger child.
    // * Repeat until heap order restored.
    
    template<typename T>
    class MaxPriorityQueue {
    public:
        MaxPriorityQueue(int capacity): N_(0) {
            pq_ = new T[capacity];
        }
        
        bool isEmpty() {
            return N_ == 0;
        }
        
        void insert(const T& key) {
            pq_[++N_] = key;
            swim(N_);
        }
        
        void swim(int k) {
            // parent of node at k is k/2
            while (k > 1 && pq_[k / 2] < pq_[k]) {
                // if children's node is larger than parent, exchange
                exch(pq_[k], pq_[k / 2]);
                
                // swim up a level
                k /= 2;
            }
        }
        
        void sink(int k) {
            // make sure k is not the bottom level
            while (2 * k <= N_) {
                // j is the left children
                int j = 2 * k;
                if (j < N_ && pq_[j] < pq_[j + 1]) {
                    // now, j is the bigger children
                    j++;
                }
                
                if (pq_[k] > pq_[j]) {
                    break;
                }
                
                // if parent node is smaller than the bigger children, exchange
                exch(pq_[k], pq_[j]);
                
                // sink down a level
                k = j;
            }
            
        }
        
        T delMax() {
            T max = pq_[1];
            
            // exchange root node with the last node
            // and record last node is not in queue
            exch(pq_[1], pq_[N_--]);
            
            // sink root node
            this->sink(1);
            
            return max;
        }
        
    private:
        int N_;
        T* pq_;
    };
}

#endif /* __binary__heap__hpp__ */
