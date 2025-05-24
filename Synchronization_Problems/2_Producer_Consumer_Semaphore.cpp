/*
 * Description:
 * A basic producer-consumer program using a custom semaphore for synchronization.
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

int count = 0;
atomic<int> sem_value(1); // Custom semaphore with initial value 1

// Wait (P operation)
void waitSem()
{
    while (true)
    {
        int expected = sem_value.load();
        if (expected > 0 && sem_value.compare_exchange_strong(expected, expected - 1))
        {
            break;
        }
        // Spin-wait
    }
}

// Signal (V operation)
void signalSem()
{
    sem_value.fetch_add(1);
}

void producer()
{
    for (int i = 0; i < 20; ++i)
    {
        waitSem();

        int temp = count;
        this_thread::sleep_for(chrono::milliseconds(10));
        count = temp + 1;
        cout << "Produced: count = " << count << endl;

        signalSem();
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

void consumer()
{
    for (int i = 0; i < 20; ++i)
    {
        waitSem();

        int temp = count;
        this_thread::sleep_for(chrono::milliseconds(10));
        count = temp - 1;
        cout << "Consumed: count = " << count << endl;

        signalSem();
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

int main()
{
    thread prod(producer);
    thread cons(consumer);

    prod.join();
    cons.join();

    cout << "\nFinal count = " << count << endl;
    return 0;
}
