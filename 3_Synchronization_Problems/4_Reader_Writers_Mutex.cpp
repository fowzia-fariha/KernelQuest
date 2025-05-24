/*
 * Multiple readers can read the shared data concurrently.
 * Writers need exclusive access to write.
 * A simple mutex-based solution using readCount and two pthread_mutex_t locks:
 *  - mutex: guards readCount
 *  - rw_mutex: ensures exclusive writer access
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

int value = 0;
int readCount = 0;

pthread_mutex_t mutex;      // for readCount synchronization
pthread_mutex_t rw_mutex;   // for writer exclusive access

void* reader(void* arg) {
    const char* name = (char*)arg;
    usleep(rand() % 100000); // simulate delay

    pthread_mutex_lock(&mutex);
    readCount++;
    if (readCount == 1) {
        pthread_mutex_lock(&rw_mutex); // first reader locks write access
    }
    pthread_mutex_unlock(&mutex);

    std::cout << name << " read value: " << value << std::endl;

    pthread_mutex_lock(&mutex);
    readCount--;
    if (readCount == 0) {
        pthread_mutex_unlock(&rw_mutex); // last reader unlocks write access
    }
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

void* writer(void* arg) {
    const char* name = (char*)arg;
    usleep(rand() % 100000); // simulate delay

    pthread_mutex_lock(&rw_mutex);

    int newValue = rand() % 1000;
    std::cout << name << " writing value: " << newValue << std::endl;
    value = newValue;

    pthread_mutex_unlock(&rw_mutex);

    return nullptr;
}

int main() {
    srand(time(nullptr)); // seed random

    pthread_t threads[6];
    const char* names[] = {
        "Reader-1", "Writer-1",
        "Reader-2", "Writer-2",
        "Reader-3", "Writer-3"
    };

    pthread_mutex_init(&mutex, nullptr);
    pthread_mutex_init(&rw_mutex, nullptr);

    for (int i = 0; i < 6; ++i) {
        if (i % 2 == 0)
            pthread_create(&threads[i], nullptr, reader, (void*)names[i]);
        else
            pthread_create(&threads[i], nullptr, writer, (void*)names[i]);
    }

    for (int i = 0; i < 6; ++i) {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&rw_mutex);

    std::cout << "\nFinal value: " << value << std::endl;

    return 0;
}
