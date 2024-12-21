#include <iostream>
#include <memory>
#include <atomic>

using namespace std;

template<typename T>
class Queue {
public: struct Q_Node {
        T item;
        atomic<Q_Node*> next;

        Q_Node(T val) : item(val), next(nullptr) {}
    };

    atomic<Q_Node*> first;
    atomic<Q_Node*> last;

    public: Queue() {
        Q_Node* dummy_node = new Q_Node(T{});  
        first.store(dummy_node);
        last.store(dummy_node);
    }
     
    public: ~Queue() {
        while (Q_Node* prev = first.load()) {  
            first.store(prev->next.load());
            delete prev;
        }
    }

    public: void enqueue(T item_to_add) {
        Q_Node* new_node = new Q_Node(item_to_add);
        Q_Node* last_old = nullptr;

        while (true) {
            last_old = last.load();
            Q_Node* next = last_old->next.load();

            if (last_old == last.load()) {
                if (next == nullptr) {
                    if (last_old->next.compare_exchange_weak(next, new_node)) {
                        break;
                    }
                } else {
                    last.compare_exchange_weak(last_old, next);
                }
            }
        }
        last.compare_exchange_weak(last_old, new_node);
    }

    public: T dequeue() {
        Q_Node* prev = nullptr;

        while (true) {
            prev = first.load();
            Q_Node* last_old = last.load();
            Q_Node* next = prev->next.load();

            if (prev == first.load()) {
                if (prev == last_old) {
                    if (next == nullptr) {
                        return NULL; 
                    }
                    last.compare_exchange_weak(last_old, next);
                }
                else {
                    T* item_to_remove = new T(next->item);  
                    if (first.compare_exchange_weak(prev, next)) {
                        delete prev;
                        return *item_to_remove;
                    }
               }
            }
        }
    }

    public: void print() const {
        Q_Node* current = first.load()->next.load();
        while (current != nullptr) {
            cout << current->item << " ";
            current = current->next.load();
        }
        cout << endl;
    }
    
    public: bool isEmpty() const {
        return first.load()->next.load() == nullptr;
    }
};
