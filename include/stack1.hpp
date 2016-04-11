#ifndef __stack1__hpp__
#define __stack1__hpp__

#include "utility.hpp"

namespace atlas {
    // link list implementation of stack
    // every operation takes constant time in the worse case
    // use extra time and space to deal with the links.
    // 表现更稳定，但是会消耗较多时间和内存。如果需要程序不允许任何操作失误，
    // 选择线性表实现的stack合适，如果想更高的运行效率，选择数组实现的stack合适。
    template<typename T>
    class Stack1 {
    public:
        Stack1() {
            first_ = nullptr;
        }
        
        ~Stack1() {
            while (!isEmpty()) {
                this->Pop();
            }
        }
        
        bool isEmpty() {
            return first_ == nullptr;
        }
        
        bool Push(T item) {
            // create a new node
            Node<T>* new_node = new Node<T>;
            
            new_node->item = item;
            new_node->next = first_;
            
            // update first node
            first_ = new_node;
            
            return true;
        }
        
        T Pop() {
            if (isEmpty()) {
                throw std::runtime_error("pop from empty stack");
            }
            
            // mark first for further delete
            Node<T>* tmp = first_;
            
            first_ = first_->next;
            
            T item = tmp->item;
            delete tmp;
            return item;
        }
        
    private:
        // matain a node to the first element
        Node<T>* first_;
    };
}
#endif