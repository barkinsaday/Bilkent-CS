#ifndef MLFQ_MUTEX_H
#define MLFQ_MUTEX_H

#include <atomic>
#include <vector>
#include <queue>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include "park.h"
#include "queue.h"
/*
	@Description: Multi Level FeedBack Queue Mutex for lock/unlock thread critical sections
*/

class MLFQMutex {
private:
    std::atomic_flag lockFlag = ATOMIC_FLAG_INIT; // Spinlock for protecting critical sections
    std::vector<Queue<pthread_t>*> levels; // Vector of queues for each priority level
    std::unordered_map<pthread_t, int> threadPriorities; // Map to track each thread's priority level
    std::mutex queueMutex; // Mutex for queue operations
    int numLevels;
    double quantum; // Quantum in seconds
    std::atomic<pthread_t> owner; // Current owner of the mutex
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime; // Start time of the mutex acquisition
    Garage garage; // Garage object for parking threads

public:
    // Constructor
    MLFQMutex(int levels, double q) : numLevels(levels), quantum(q) {
        for (int i = 0; i < levels; i++) {
            this->levels.push_back(new Queue<pthread_t>());
        }
    }

    // Destructor
    ~MLFQMutex() {
        for (auto& level : levels) {
            delete level;
        }
    }

    // Lock the mutex
    void lock() {
        pthread_t currentThread = pthread_self();
        while (lockFlag.test_and_set(std::memory_order_acquire)) { // Spin and try to acquire the lock
            garage.setPark();
            garage.park();
            //printf("AAAAAAAAAAAAAAAAAAAAA\n");
        }

        std::lock_guard<std::mutex> lg(queueMutex);
        owner.store(currentThread);
        startTime = std::chrono::high_resolution_clock::now();
        // Check and assign thread to proper queue if not already present
        if (threadPriorities.find(currentThread) == threadPriorities.end()) {
            threadPriorities[currentThread] = 0; // Assign to highest priority (level 0)
            levels[0]->enqueue(currentThread);
            std::cout << "Adding thread with ID: " << currentThread << " to level " << threadPriorities[currentThread] << std::endl;
            //std::cout.flush();
        }
    }

    // Unlock the mutex
    void unlock() {
        std::lock_guard<std::mutex> lg(queueMutex);
        pthread_t currentThread = pthread_self();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto execTime = std::chrono::duration<double>(endTime - startTime).count();

        int currentLevel = threadPriorities[currentThread];
        int newLevel = currentLevel + static_cast<int>(execTime / quantum);
        newLevel = std::min(newLevel, numLevels - 1); // Cap to the maximum level
        threadPriorities[currentThread] = newLevel;

        // Move to new level if needed
        if (newLevel != currentLevel) {
            levels[currentLevel]->dequeue();//remove(currentThread)???
            levels[newLevel]->enqueue(currentThread);
        }

        owner.store(0);
        lockFlag.clear(std::memory_order_release);
        pthread_t nextThread = levels[newLevel]->dequeue(); // Ideally, get the next thread from the highest priority queue that is not empty
        if (nextThread != 0) {
            garage.unpark(nextThread);
        }
    }

    // Print the contents of all queues
    void print() {
        std::lock_guard<std::mutex> lg(queueMutex);
        for (int i = 0; i < numLevels; i++) {
            std::cout << "Level " << i << ": ";
            levels[i]->print();
        }
    }
};

#endif  // MLFQ_MUTEX_H
