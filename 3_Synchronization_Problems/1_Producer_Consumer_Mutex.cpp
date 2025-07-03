/*
 * Description:
 * Simple producer-consumer program using a custom spinlock mutex.
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

int count = 0;
atomic<bool> available(true);  // Acts like the mutex

void acquire() {
    while (!available.exchange(false)) {
        // Busy-wait (spinlock)
    }
}

void release() {
    available.store(true);
}

void producer() {
    for (int i = 0; i < 20; ++i) {
        acquire();
        int temp = count;
        this_thread::sleep_for(chrono::milliseconds(10));
        count = temp + 1;
        cout << "Produced: count = " << count << endl;
        release();
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

void consumer() {
    for (int i = 0; i < 20; ++i) {
        acquire();
        int temp = count;
        this_thread::sleep_for(chrono::milliseconds(10));
        count = temp - 1;
        cout << "Consumed: count = " << count << endl;
        release();
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

int main() {
    thread prod(producer);
    thread cons(consumer);

    prod.join();
    cons.join();

    cout << "\nFinal count = " << count << endl;
    return 0;
}
