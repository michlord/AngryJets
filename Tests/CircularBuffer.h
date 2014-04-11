#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdexcept>

template <typename T>
class CircularBuffer {
public:

    CircularBuffer(int size_) :
    front(0), back(0), size(size_) {
        //one element is unused so we need extra space
        //to accommodate size requirements
        buffer = new T [size + 1];
    }

    virtual ~CircularBuffer() {
        if (buffer != nullptr) {
            delete [] buffer;
        }
    }

    bool pushBack(T val_) {
        if (full() == true) {
            return false;
        } else {
            buffer[back] = val_;
            back = (back + 1) % size;
            return true;
        }
    }

    bool pushBackOverride(T val_) {
        bool did_not_override = true;
        if (full() == true) {
            popFront();
            did_not_override = false;
        }
        buffer[back] = val_;
        back = (back + 1) % size;
        return did_not_override;
    }

    T popFront() {
        if (empty() == true) {
            throw std::runtime_error("Buffer is empty");
        } else {
            T* val = &buffer[front];
            front = (front + 1) % size;
            return *val;
        }
    }

    bool empty() {
        return front == back;
    }

    bool full() {
        return ((back + 1) % size) == front;
    }

    void clear() {
        front = 0;
        back = 0;

    }
protected:
private:
    T* buffer;
    int front;
    int back;
    int size;

};

#endif // CIRCULARBUFFER_H
