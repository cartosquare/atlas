#ifndef __stack2__hpp__
#define __stack2__hpp__
#include "utility.hpp"

namespace atlas {
    // array implementation of stack
    // every operation takes constant amorized time.
    // less wasted space.
    // 比起线性表实现的stack总耗时更少，但是某些操作可能会相对耗时。
    template<typename T>
    class Stack2 {
    public:
        Stack2() {
            capicity_ = 1;
            first_ = 0;
            items_ = new T[capicity_];
        }
        
        ~Stack2() {
            if (items_) {
                delete [] items_;
            }
        }
        
        bool isEmpty() {
            return first_ == 0;
        }
        
        bool Push(T item) {
            if (first_ == capicity_) {
                resize(capicity_ * 2);
            }
            
            items_[first_++] = item;
            return true;
        }
        
        T Pop() {
            if (isEmpty()) {
                throw std::runtime_error("pop from empty stack");
            }
            
            T item = items_[--first_];
            if (first_ > 0 && first_ == capicity_ / 4) {
                resize(capicity_ / 2);
            }
            return item;
        }
        
    private:
        bool resize(int N) {
            // TODO: catch memory allocation fail
            T* tmp = new T[N];
            for (int i = 0; i < first_; ++i) {
                tmp[i] = items_[i];
            }
            delete[] items_;
            items_ = tmp;
            capicity_ = N;
            return true;
        }
        
        T* items_;
        int first_;
        int capicity_;
    };
}
#endif