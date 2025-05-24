#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void *thread_func1(void *arg)
{
    pthread_mutex_lock(&lock1);
    cout << "Thread 1: locked lock1" << endl;
    sleep(1); // Give Thread 2 time to
    lock lock2

            cout
        << "Thread 1: trying to lock 
        lock2... " << endl; 
        pthread_mutex_lock(&lock2);
    cout << "Thread 1: locked lock2" << endl;

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return NULL;
}

void *thread_func2(void *arg)
{
    pthread_mutex_lock(&lock2);
    cout << "Thread 2: locked lock2" << endl;
    sleep(1); // Give Thread 1 time to
    lock lock1

            cout
        << "Thread 2: trying to lock 
        lock1... " << endl; 
        pthread_mutex_lock(&lock1);
    cout << "Thread 2: locked lock1" << endl;

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL,
                   thread_func1, NULL);
    pthread_create(&t2, NULL,
                   thread_func2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    cout << "Main ends (this may never 
be printed if deadlock occurs!)" << 
endl;
    return 0;
}