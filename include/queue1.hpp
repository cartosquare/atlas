#ifndef __queue1__hpp__
#define __queue1__hpp__

#include "utility.hpp"
namespace atlas {
    // link list implementation of queue
    template<typename T>
    class Queue1 {
    public:
        Queue1() {
            first_ = nullptr;
            last_ = nullptr;
        }
        
        ~Queue1() {
            while (!isEmpty()) {
                this->DeQueue();
            }
        }
        
        bool isEmpty() {
            return (first_ == nullptr);
        }
        
        bool EnQueue(T item) {
            // add item to the last
            Node<T>* old_last = last_;
            
            // create a new node
            last_ = new Node<T>;
            last_->item = item;
            last_->next = nullptr;
            
            if (isEmpty()) {
                first_ = last_;
            } else {
                old_last->next = last_;
            }
            
            return true;
        }
        
        T DeQueue() {
            // mark first for further delete
            Node<T>* tmp = first_;
            
            first_ = first_->next;
            
            T item = tmp->item;
            delete tmp;
            
            if (isEmpty()) {
                last_ = nullptr;
            }
            
            return item;
        }
        
    private:
        // matain pointer to the first and last element of queue
        Node<T>* first_;
        Node<T>* last_;
    };
}
#endif