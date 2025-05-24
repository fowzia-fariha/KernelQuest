/*
 * Safe Multithreaded Counter Increment with Mutex Locking
 * --------------------------------------------------------
 * This program creates two threads that safely increment a shared counter
 * 100 times each. A mutex lock ensures atomic access to the shared resource,
 * preventing race conditions and ensuring the correct final value.
 */

#include <iostream>
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock;

// Function executed by threads to increment counter
void *increment(void *thread_id)
{
    long tid = (long)thread_id;

    for (int i = 0; i < 100; ++i)
    {
        pthread_mutex_lock(&lock);
        ++counter;
        pthread_mutex_unlock(&lock);
    }

    std::cout << "[Thread " << tid << "] Finished incrementing.\n";
    return nullptr;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&lock, nullptr);

    std::cout << "\n=== Starting Safe Counter Increment Simulation ===\n";

    pthread_create(&t1, nullptr, increment, (void *)1);
    pthread_create(&t2, nullptr, increment, (void *)2);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    std::cout << "--------------------------------------------------\n";
    std::cout << ">> Expected Final Counter Value : 200\n";
    std::cout << ">> Actual   Final Counter Value : " << counter << "\n";
    std::cout << ">> Result: " << (counter == 200 ? "Correct " : "Incorrect ") << "\n";
    std::cout << "--------------------------------------------------\n";

    pthread_mutex_destroy(&lock);

    return 0;
}
