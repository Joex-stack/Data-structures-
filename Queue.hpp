#ifndef QUEUE_DEQUEUE_CLASSES_HPP
#define QUEUE_DEQUEUE_CLASSES_HPP

#include "Linked__List.hpp"
#include "Vector.hpp"
#include <stdexcept>

// ---------------- Queue with Linked List ----------------
template<class t>
class QueueLI {
private:
    LinkedList<t> data;
    int size = 0;
    bool dynamic = false;

public:
    QueueLI() : QueueLI(10) {}
    QueueLI(int x, bool b = false) : size(x), dynamic(b) {}

    QueueLI(const QueueLI& other) : size(other.size), dynamic(other.dynamic) {
        auto* curr = other.data.gethead();
        while (curr) {
            this->enqueue(curr->data);
            curr = curr->next;
        }
    }

    void enqueue(t x) {
        if (this->isav() || dynamic) {
            data.insert_end(x);
            if (dynamic && data.getlen() == size) size *= 2;
        } else {
            throw std::runtime_error("Queue is full!");
        }
    }

    t dequeue() {
        auto* x = data.gethead();
        if (!x) throw std::runtime_error("Queue is empty");
        t val = x->data;
        data.fdel();
        return val;
    }

    bool isfull() const {
        return !dynamic && data.getlen() == size;
    }

    bool isav() const {
        return dynamic || !isfull();
    }

    bool isemt() const {
        return data.getlen() == 0;
    }

    int getsize() const { return this->size; }

    t front() const {
        if (this->isemt()) throw std::runtime_error("Queue is empty");
        return data.gethead()->data;
    }
};

// ---------------- Queue with Array ----------------
template<class t>
class QueueArr {
private:
    int size{0}, front{0}, rear{0}, len{0};
    t* data{};

    int next(int x) {
        ++x;
        if (x == size) x = 0;
        return x;
    }

public:
    QueueArr(int x) : size(x) {
        data = new t[size];
    }

    QueueArr() : QueueArr(10) {}

    QueueArr(const QueueArr& other) : size(other.size), front(other.front), rear(other.rear), len(other.len) {
        data = new t[size];
        for (int i = 0, idx = front; i < len; ++i, idx = (idx + 1) % size) {
            data[idx] = other.data[idx];
        }
    }

    ~QueueArr() {
        delete[] data;
    }

    void enqueue(t x) {
        if (isav()) {
            data[rear] = x;
            rear = next(rear);
            len++;
        } else {
            throw std::runtime_error("Queue is full!");
        }
    }

    t dequeue() {
        if (!isemt()) {
            t x = data[front];
            front = next(front);
            len--;
            return x;
        } else {
            throw std::runtime_error("Queue is empty!");
        }
    }

    bool isfull() const { return len == size; }
    bool isemt() const { return len == 0; }
    bool isav() const { return !isfull(); }
};

// ---------------- Dequeue with Array ----------------
template<class t>
class DequeueArr {
private:
    int size{0}, len{0}, front{0}, rear{0};
    t* data{};

    int next(int x) {
        ++x;
        if (x >= size) x = 0;
        return x;
    }

    int prev(int x) {
        --x;
        if (x < 0) x = size - 1;
        return x;
    }

public:
    DequeueArr() : DequeueArr(10) {}
    DequeueArr(int x) : size(x) {
        data = new t[size];
    }

    ~DequeueArr() {
        delete[] data;
    }

    void enqueue_rear(t x) {
        if (isav()) {
            data[rear] = x;
            rear = next(rear);
            len++;
        } else {
            throw std::runtime_error("Dequeue is full!");
        }
    }

    void enqueue_front(t x) {
        if (isav()) {
            front = prev(front);
            data[front] = x;
            len++;
        } else {
            throw std::runtime_error("Dequeue is full!");
        }
    }

    t dequeue_front() {
        if (!isemt()) {
            t x = data[front];
            front = next(front);
            len--;
            return x;
        } else {
            throw std::runtime_error("Dequeue is empty!");
        }
    }

    t dequeue_end() {
        if (!isemt()) {
            rear = prev(rear);
            t x = data[rear];
            len--;
            return x;
        } else {
            throw std::runtime_error("Dequeue is empty!");
        }
    }

    bool isemt() const { return len == 0; }
    bool isfull() const { return len == size; }
    bool isav() const { return !isfull(); }
};

// ---------------- Dequeue with Linked List ----------------
template<class t>
class DequeueLI {
private:
    LinkedList<t> data;
    int size{0};
    bool dynamic = false;

public:
    DequeueLI() : DequeueLI(10) {}
    DequeueLI(int x, bool b = false) : size(x), dynamic(b) {}

    void enqueue_back(t x) {
        if (isav() || dynamic) {
            data.insert_end(x);
            if (dynamic && data.getlen() == size) size *= 2;
        } else {
            throw std::runtime_error("Dequeue is full!");
        }
    }

    void enqueue_front(t x) {
        if (isav() || dynamic) {
            data.insert_front(x);
            if (dynamic && data.getlen() == size) size *= 2;
        } else {
            throw std::runtime_error("Dequeue is full!");
        }
    }

    t dequeue_front() {
        if (!isemt()) {
            t x = data.gethead()->data;
            data.fdel();
            return x;
        } else {
            throw std::runtime_error("Dequeue is empty!");
        }
    }

    t dequeue_back() {
        if (!isemt()) {
            t x = data.getfrb(0);
            data.del(data.getlen() - 1);
            return x;
        } else {
            throw std::runtime_error("Dequeue is empty!");
        }
    }

    t front() const { return data.gethead()->data; }
    t back() const { return data.getfrb(0); }
    int getlen() const { return data.getlen(); }
    int capacity() const { return size; }

    bool isemt() const { return data.getlen() == 0; }
    bool isfull() const { return !dynamic && data.getlen() == size; }
    bool isav() const { return dynamic || !isfull(); }
};

#endif // QUEUE_DEQUEUE_CLASSES_HPP