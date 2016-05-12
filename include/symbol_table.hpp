#ifndef __symbol__table__hpp__
#define __symbol__table__hpp__

#include <vector>
#include <assert.h>

namespace atlas {
    // Symbol tables
    // Key-value pair abstraction
    // * Insert a value with specify key
    // * Given a key, search for the corresponding value
    
    // Examples:
    // DNS lookup: Insert URL with specified IP address; Given URL, find corresponding IP address.
    // Dictionary: word --> definition
    //
    
    
    // Linked list implemation
    // find time: N for worse-cast, N / 2 for average case
    // insert time: N for both worse and average case
    template<typename Key, typename Value>
    class LinkedListSymbolTable {
    public:
        struct Node {
            Key key_;
            Value value_;
            Node* next_;
        };
        
        LinkedListSymbolTable() {
            front_ = nullptr;
        }
        
        ~LinkedListSymbolTable() {
            if (front_ != nullptr) {
                delete_key(front_->key_);
            }
        }
        
        void put(Key key, Value value) {
            // scan through all keys until find a match
            Node* current = this->get(key);
            if (current != nullptr) {
                current->value_ = value;
                return;
            }
            
            // otherwise insert at front
            Node* new_node = new Node;
            new_node->key_ = key;
            new_node->value_ = value;
            
            new_node->next_ = front_;
            front_ = new_node;
        }
        
        Value get_value(Key key) {
            Node* node = get(key);
            if (node == nullptr) {
                // TODO: maybe this return value is not suitable
                return Value();
            } else {
                return node->value_;
            }
        }
        
        Node* get(Key key) {
            // scan through all keys until find a match.
            Node* tmp = front_;
            while(tmp != nullptr) {
                if (tmp->key_ == key) {
                    return tmp;
                } else {
                    tmp = tmp->next_;
                }
            }
            
            return nullptr;
        }
        
        Node* get_pre(Key key) {
            // scan through all keys until find a match.
            Node* tmp = front_;
            Node* pre = nullptr;
            
            while(tmp != nullptr) {
                if (tmp->key_ == key) {
                    return pre;
                } else {
                    pre = tmp;
                    tmp = tmp->next_;
                }
            }
            
            return nullptr;
        }
        
        
        void delete_key(Key key) {
            // key not exist
            Node* key_node = this->get(key);
            if (key_node == nullptr) {
                return;
            }
            
            // get previous node
            Node* pre_node = this->get_pre(key);
            if (pre_node == nullptr) {
               // key_node is front node
                front_ = key_node->next_;
                delete key_node;
            } else {
                pre_node->next_ = key_node->next_;
                delete key_node;
            }
        }
        
        bool contains(Key key) {
            return (get(key) != nullptr);
        }
        
        bool is_empty() {
            return (front_ == nullptr);
        }
        
        int size() {
            int count = 0;
            Node* tmp = front_;
            while(tmp != nullptr) {
                ++count;
                tmp = tmp->next_;
            }
            return count;
        }
        
    private:
        Node* front_;
    };
    
    // Ordered array impletation of linked list
    // Search time: logN for both worst and average case
    // insert time: N for worst case, N / 2 for average case
    template<typename Key, typename Value>
    class OrderedArraySymbolTable {
    private:
        std::vector<Key> keys_;
        std::vector<Value> values_;
        
    public:
        void put(Key key, Value value) {
            // find first
            size_t i = this->rank(key);
            if (i < keys_.size() && keys_[i] == key) {
                keys_[i] = key;
                values_[i] = value;
                return;
            }
            
            // otherwise insert new element...
            size_t pos = keys_.size();
            for (size_t i = 0; i < keys_.size(); ++i) {
                if (keys_[i] > key) {
                    pos = i;
                    break;
                }
            }
            
            std::vector<Key> new_key;
            std::vector<Value> new_value;
            for (size_t i = 0; i < pos; ++i) {
                new_key.push_back(keys_[i]);
                new_value.push_back(values_[i]);
            }
            
            new_key.push_back(key);
            new_value.push_back(value);
            
            for (size_t i = pos; i < keys_.size(); ++i) {
                new_key.push_back(keys_[i]);
                new_value.push_back(values_[i]);
            }
            
            keys_ = std::move(new_key);
            values_ = std::move(new_value);
        }
        
        void delete_key(Key key) {
            size_t pos = keys_.size();
            for (size_t i = 0; i < keys_.size(); ++i) {
                if (keys_[i] == key) {
                    pos = i;
                    break;
                }
            }
            
            if (pos == keys_.size()) {
                return;
            }
            
            std::vector<Key> new_key;
            std::vector<Value> new_value;
            for (size_t i = 0; i < pos; ++i) {
                new_key.push_back(keys_[i]);
                new_value.push_back(values_[i]);
            }
            
            for (size_t i = pos + 1; i < keys_.size(); ++i) {
                new_key.push_back(keys_[i]);
                new_value.push_back(values_[i]);
            }
            
            keys_ = std::move(new_key);
            values_ = std::move(new_value);
        }
        
        Value get(Key key) {
            if (is_empty()) {
                return Value();
            }
            
            size_t i = rank(key);
            if (i < keys_.size() && keys_[i] == key) {
                return values_[i];
            } else {
                return Value();
            }
        }
        
        bool is_empty() {
            return (keys_.size() == 0);
        }
        
        int rank(Key key) {
            // binary search
            int lo = 0;
            int hi = keys_.size() - 1;
            
            while(lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (keys_[mid] > key) {
                    hi = mid - 1;
                } else if (keys_[mid] < key) {
                    lo = mid + 1;
                } else {
                    return mid;
                }
            }
            
            return lo;
        }
        
        int size() {
            return keys_.size();
        }
        
        bool contains(Key key) {
            int i = this->rank(key);
            if (i < keys_.size() && keys_[i] == key) {
                return true;
            } else {
                return false;
            }
        }
    };
    
    
    
    template<typename Key, typename Value>
    class SymbolTable {
        
    public:
        void put(Key key, Value val) {
            
        }
        
        Value get(Key key) {
            
        }
        
        void delete_by_key(Key key) {
            
        }
        
        bool contains(Key key) {
            
        }
        
        bool is_empty() {
            
        }
        
        int size() {
            
        }
        
        Key min() {
            
        }
        
        Key max() {
            
        }
        
        Key floor(Key key) {
            
        }
        
        Key ceiling(Key key) {
            
        }
        
        int rank(Key key) {
            
        }
        
        Key select(int k) {
            
        }
        
        void delete_min() {
            
        }
        
        void delete_max() {
            
        }
        
        int size(Key lo, Key hi) {
            
        }
        
    };
}

#endif