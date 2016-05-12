#ifndef __binary_search_tree__hpp__
#define __binary_search_tree__hpp__

#include <vector>

namespace atlas {
    /*         Definition                */
    // A binary search tree is a binary tree in symmetric order
    // What's symmetric order mean?
    // Each node has a key, and every node's key is:
    // * Larger than all keys in its left subtree.
    // * Smaller than all keys in its right subtree.
    
    // search time: N for worse case, 1.39lgN for the average case
    // insert time: N for worse case, 1.39lgN for the average case
    
    // quick both in search and insert in average case!
    template<typename Key, typename Value>
    class BinarySearchTree {
    private:
        struct Node {
            // a node has four basic field
            Key key_;
            Value value_;
            
            // left and right subtree
            Node* left_;   // smaller keys
            Node* right_;  // larger keys
            
            // to facilitates efficient implementation of rand() and select(),
            // in each node, we store the number of nodes in the subtree rooted at that node;
            // to implement size(), just return the count at the root.
            int count_;
            
            Node(Key key, Value value, int count): key_(key), value_(value), count_(count) {
            }
        };
        
        // A BST is a reference to a root Node.
        Node* root_;
        
        
        
    public:
        BinarySearchTree() {
            root_ = nullptr;
        }
        
        ~BinarySearchTree() {
        }
        
        // return value corresponding to given key,
        // or null if no such key
        Value get(Key key) {
            Node x = root;
            while (x != nullptr) {
                // Search. If less, go left; if greater, go right; if equal, search hit.
                if (x.key_ > key) {
                    x = x.left_;
                } else if (x.key_ < key) {
                    x = x.right_;
                } else {
                    return x.value_;
                }
            }
            
            // unsuccessful search
            return Value();
        }
        
        
        // search for key, then two cases:
        // key in tree -> reset value
        // key not in tree -> add new node
        void put(Key key, Value value) {
            // recursive code!!!
            root_ = put(root_, key, value);
        }
        
        // Insert. If less, go left; if greater go right; if null, insert
        Node put(Node x, Key key, Value val) {
            if (x == null) {
                return new Node(key, value, 1);
            }
            
            if (key < x.key) {
                x.left_ = put(x.left_, key, val);
            } else if (key > x.key) {
                x.right_ = put(x.right_, key, val);
            } else {
                x.val = val;
            }
            
            // update node count
            x.count_ = size(x->left_) + size(x->right_) + 1;
            
            // return the node that is the parent of the inserted node
            return x;
        }
        
        // Smallest key in table
        Key min() {
            if (root_ == nullptr) {
                return Key();
            }
            
            // go to the most left node
            Node* tmp = root_;
            while (tmp != nullptr) {
                tmp = tmp->left_;
            }
            return tmp->key_;
        }
        
        // Largest key in table
        Key max() {
            if (root_ == nullptr) {
                return Key();
            }
            
            // go to the most right node
            Node* tmp = root_;
            while(tmp != nullptr) {
                tmp = tmp->right_;
            }
            return tmp->key_;
        }
        
        // Largest key <= to a given key
        Key floor(Key key) {
            Node* x = floor(root_, key);
            if (x == nullptr) {
                return Key();
            } else {
                return x->key_;
            }
        }
        
        Node floor(Node* x, Key key) {
            if (x == nullptr) {
                return nullptr;
            }
            
            // case 1. k equals to the key at root, The floor of k is k
            if (key == x->key) {
                return x;
            }
            
            // case 2: k is less than the key at root
            // the floor of k is in the left subtree.
            if (key < x->key) {
                return floor(x->left_, key);
            }
            
            // case 3. k is greater than the key at root
            // the floor of k is in the right subtree(if there is any key <= k in right subtree);
            // otherwise it is the key in the root.
            Node* t = floor(x->right_, key);
            if (t != nullptr) {
                return t;
            } else {
                return x;
            }
        }
        
        // Smallest key >= to a given key
        Key ceiling(Key key) {
            Node* x = ceiling(root_, key);
            if (x == nullptr) {
                return Key();
            } else {
                return x->key_;
            }
        }
        
        Node ceiling(Node* x, Key key) {
            if (x == nullptr) {
                return nullptr;
            }
            
            // case 1. k equals to the key at root, the ceiling of k is k.
            if (key == x->key) {
                return x;
            }
            
            // case 2. k is bigger than the key at root
            // the ceiling of k is in the right subtree.
            if (key > x->key_) {
                return ceiling(x->right_, key);
            }
            
            // case 3. k is less than the key at root
            // the ceiling of k is in the left subtree(if there is any key >= k in left subtree).
            // otherwise it is the key in the root
            Node* t = ceiling(x->left_, key);
            if (t != nullptr) {
                return t;
            } else {
                return x;
            }
        }
        
        int size() {
            return size(root_);
        }
        
        int size(Node* x) {
            if (x == nullptr) {
                return 0;
            } else {
                return x->count_;
            }
        }
        
        // How many keys < k?
        int rank(Key key) {
            return rank(root_, key);
        }
        
        int rank(Node* x, Key key) {
            if (x == nullptr) {
                return 0;
            }
            
            if (key < x->key_) {
                return rank(x->left_, key);
            } else if (key > x->key_) {
                return (1 + size(x->left_) + rank(x->right_, key));
            } else {
                // key == x->key_
                return size(x.left_);
            }
        }
        
        int size(Key lo, Key hi) {
            return (rank(hi) - rank(lo));
        }
        
        // delete the minimum key
        void delete_min() {
            root_ = delete_min(root_);
        }
        
        // Go left until finding a node with a null left link.
        // Replace that node by its right link.
        // Update subtree counts.
        Node* delete_min(Node* x) {
            if (x.left_ == nullptr) {
                Node* tmp = x.right_;
                delete x;
                return tmp;
            }
            
            x->left_ = delete_min(x->left_);
            
            x->count_ = 1 + size(x->left_) + size(x->right_);
            
            return x;
        }
        
        // Go right until finding a node with a null right link.
        // Replace that node by its left link.
        // Update subtree counts
        void delete_max() {
            root_ = delete_max(root_);
        }
        
        Node* delete_max(Node* x) {
            if (x->right_ == nullptr) {
                Node* tmp = x->left_;
                delete x;
                return tmp;
            }
            
            x->right_ = delete_max(x->right_);
            x->count_ = 1 + size(x->left_) + size(x->right_);
            
            return x;
        }
        
        // To delete a node with key k: search for node t containing key k.
        // case 0. [0 children] delete t by setting parent link to null.
        // case 1. [1 children] delete t by replacing parent link.
        // case 2. [2 children]
        // * find successor x of t (that x has no left child -- x is the minimal key of the subtree rooted at x)
        // * delete the minimum in t's right subtree
        // * put x in t's spot
        void hibard_delete(Key key) {
            root_ = hibard_delete(root_);
        }
        
        // simple implemation, but unfortunitly, the tree after lots of random inserts and delete is NOT Symmetric!!!
        Node* hibard_delete(Node* x, Key key) {
            if (x == nullptr) {
                return nullptr;
            }
            
            // search for key
            if (key < x->key_) {
                x->left_ = hibard_delete(x->left_, key);
            } else if (key > x->key_) {
                x->right_ = hibard_delete(x->right_, key);
            } else {
                if (x.right_ == nullptr) {
                    Node* tmp = x.left_;
                    delete x;
                    return tmp;
                }
                
                if (x.left_ == nullptr) {
                    Node* tmp = x->right_;
                    delete x;
                    return tmp;
                }
                
                // replace with successor
                Node* t = x;
                x = min(t.right_);
                
                // backup minimum node
                Node* new_node(x->key_, x->value_, x->count_);
                // delete minimum node
                new_node->right_ = delete_min(t->right_);
                new_node->left_ = t.left_;
                
                x = new_node;
            }
            x->count_ = size(x->left_) + size(x->right_) + 1;
            return x;
        }
        
        Key select(int k) {
            
        }
        
    };
    
}

#endif