#ifndef MLFQ_MUTEX_H
#define MLFQ_MUTEX_H

#include <vector>
#include <chrono>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <unordered_map>
#include <mutex>
#include <iostream>
#include "queue.h"
#include <pthread.h>
#include "park.h"
#include <atomic>

using namespace std;

class MLFQMutex {
private:
    double qval;
    atomic_flag lock_F = ATOMIC_FLAG_INIT;
    int number_of_Levels;
    atomic<pthread_t> producer;
    unordered_map<pthread_t, int> prios;
    vector<Queue<pthread_t>*> queues;
    chrono::time_point<chrono::high_resolution_clock> start_Time;
    mutex mutex_Q;
    mutex mutex_Q_guardian;
    Garage my_gar;
    int active_thread_count;

    public: MLFQMutex(int queues, double q) : number_of_Levels(queues), qval(q) {
    	active_thread_count = 0;
        for (int i = 0; i < queues; i++) 
            this->queues.push_back(new Queue<pthread_t>());
    }

    public: ~MLFQMutex() {
        for (auto& q : queues) 
            delete q;
    }

    public: void print() {
        lock_guard<mutex> lg(mutex_Q);
        cout << "Printing Levels" << endl; 
        for (int i = 0; i < number_of_Levels; i++) {
            cout << "Level number " << i << ": ";
            queues[i]->print();
        }
    }

    public: void lock() {
        pthread_t curr = pthread_self();
        while (lock_F.test_and_set(memory_order_acquire)) { 
            my_gar.setPark();
            my_gar.park();
        }
        lock_guard<mutex> lg(mutex_Q);
        producer.store(curr);
        start_Time = std::chrono::high_resolution_clock::now();
        if (prios.find(curr) == prios.end()) {
            prios[curr] = 0; 
            queues[0]->enqueue(curr);
        }
    }

    public: void unlock() {
        lock_guard<mutex> lg(mutex_Q);
        pthread_t curr = pthread_self();
        auto end_Time = std::chrono::high_resolution_clock::now();
        auto total_duration = std::chrono::duration<double>(end_Time - start_Time).count();

        int current_Queue = prios[curr];
        int downgrade = current_Queue + static_cast<int>(total_duration / qval);
        downgrade = min(downgrade, number_of_Levels - 1); 
        prios[curr] = downgrade;

        if (downgrade != current_Queue) {
            queues[current_Queue]->dequeue();
            queues[downgrade]->enqueue(curr);
        }
        producer.store(0);
        lock_F.clear(memory_order_release);
        pthread_t next = queues[downgrade]->dequeue();
        if (next != 0) {
            my_gar.unpark(next);
        }
    }
};

#endif  // MLFQ_MUTEX_H

