#include <atomic>
#include <memory>
#include <iostream>


/*
@Description: A thread safe queue that uses Micheal and Scott method from text book 
*/

template<typename T>
class Queue {
public:
    struct Node {
        T data;
        std::atomic<Node*> next;

        Node(T val) : data(val), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

    //Constrcutor: Always creates a dummy node
    Queue() {
        Node* dummy = new Node(T{});  // Dummy node
        head.store(dummy);
        tail.store(dummy);
    }
     
    //Destructor: Clear the nodes
    ~Queue() {
        while (Node* old_head = head.load()) {  
            head.store(old_head->next.load());
            delete old_head;
        }
    }

    void enqueue(T value) {
        Node* new_node = new Node(value);
        Node* old_tail = nullptr;

        while (true) {
            old_tail = tail.load();
            Node* next = old_tail->next.load();

            if (old_tail == tail.load()) {
                if (next == nullptr) {
                    if (old_tail->next.compare_exchange_weak(next, new_node)) {
                        break;
                    }
                } else {
                    tail.compare_exchange_weak(old_tail, next);
                }
            }
        }

        tail.compare_exchange_weak(old_tail, new_node);
    }

    T dequeue() {
        Node* old_head = nullptr;

        while (true) {
            old_head = head.load();
            Node* old_tail = tail.load();
            Node* next = old_head->next.load();

            if (old_head == head.load()) {
                if (old_head == old_tail) {
                    if (next == nullptr) {
                        return NULL;  // Queue is empty
                    }
                    tail.compare_exchange_weak(old_tail, next);
                } else {
                    T* value = new T(next->data);  // Allocate new memory for the value to be returned
                    if (head.compare_exchange_weak(old_head, next)) {
                        delete old_head;
                        return *value;
                    }
                }
            }
        }
    }

    bool isEmpty() const {
        return head.load()->next.load() == nullptr;
    }

    void print() const {
        Node* current = head.load()->next.load();
        std::cout << "Queue: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next.load();
        }
        
        std::cout << std::endl;
    }
};
