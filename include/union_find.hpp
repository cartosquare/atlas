#ifndef __union__find__hpp__
#define __union__find__hpp__

namespace atlas {
    /* union-find algorithm is used to solve Dynamic connectivity problem */
    
    // What is Dynamic connectivity?
    // Given a set of N objects.
    //  * Union command: connect two objects.
    //  * Find/connected query: is there a path connecting the two objects?
    
    // Implementation
    // * Use integers as array index to name objects 0 to N - 1
    // * Suppress details not relevant to union-find.
    
    // Modeling the connections
    // We assume "is connected to" is an equivalence relation:
    // * Reflexive: p is connected to p.
    // * Symmetric: if p is connected to q, then q is connected to p.
    // * Transitive: if p is connected to q and q is connected to r, then p is connected to r.
    // Connected components: Maximal set of objects that are mutually connected.
    
    // Implementing the operations
    // * Find query: Check if two objects are in the same connected component.
    // * Union command: Replace components containing two objects with their union.
    
    // Data structure
    // * integer array id of size N.
    // * interpretation: id[i] is parent of i.
    // * root of i is id[id[...id[i]...]].
    // Find: check if p and q have the same root.
    // Union: To merge components containing p and q,
    // set the id of p's root to the id of q's root,
    // to make the tree more flat, we need to link root of smaller tree
    // to root of larger tree(to achieve this, we need another array to record
    // the size of each tree(namely, connected components)).
    
    
    class WeightedUnionFind {
    public:
        WeightedUnionFind(int N) {
            id_ = new int[N];
            sz_ = new int[N];
            
            for (int i = 0; i < N; ++i) {
                id_[i] = i;
                sz_[i] = 1;
            }
        }
        
        ~WeightedUnionFind() {
            delete[] id_;
            delete[] sz_;
        }
        
        bool Connected(int p, int q) {
            // check if p and q have the same root.
            return root(p) == root(q);
        }
        
        void Union(int p, int q) {
            int i = root(p);
            int j = root(q);
            if (i == j) {
                return;
            }
            // find the smaller connected component, and append it to larger ,,,
            if (sz_[i] < sz_[j]) {
                id_[i] = j;
                sz_[j] += sz_[i];
            } else {
                id_[j] = i;
                sz_[i] += sz_[j];
            }
        }
        
    private:
        int root(int i) {
            while (i != id_[i]) {
                id_[i] = id_[id_[i]];
                i = id_[i];
            }
            return i;
        }
        
        int* id_;
        int* sz_;
    };
}
#endif