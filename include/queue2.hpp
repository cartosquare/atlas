#ifndef __queue2__hpp__
#define __queue2__hpp__

namespace atlas {
    // array implementation of queue
    template<typename T>
    class Queue2 {
    public:
        Queue2() {
            capicity_ = 1;
            first_ = 0;
            last_ = 0;
            items_ = new T[capicity_];
        }
        
        ~Queue2() {
            if (items_) {
                delete [] items_;
            }
        }
        
        bool isEmpty() {
            return (first_ >= last_);
        }
        
        bool EnQueue(T item) {
            if (last_ == capicity_) {
                resize(capicity_ * 2);
            }
            
            items_[last_++] = item;
            return true;
        }
        
        T DeQueue() {
            T item = items_[first_++];
            if (isEmpty()) {
                return item;
            }
            
            if (last_ > 0 && (last_ - first_) == capicity_ / 4) {
                resize(capicity_ / 2);
            }
            return item;
        }
        
    private:
        bool resize(int N) {
            // TODO: catch memory allocation fail
            T* tmp = new T[N];
            for (int i = first_; i < last_; ++i) {
                tmp[i - first_] = items_[i];
            }
            delete[] items_;
            items_ = tmp;
            
            last_ = (last_ - first_);
            first_ = 0;
            
            capicity_ = N;
            return true;
        }
        
        T* items_;
        int first_;
        int last_;
        int capicity_;
    };
}
#endif