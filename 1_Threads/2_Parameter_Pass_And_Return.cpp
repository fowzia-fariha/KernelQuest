#include <iostream> 
#include <pthread.h> 
 
using namespace std; 
 
// Thread function to calculate sum 
void* calculate_sum(void* arg) { 
  int* arr = (int*)arg; 
    int sum = 0; 
 
    for (int i = 0; i < 5; i++) { 
        sum += arr[i]; 
    } 
 
    
    int* result = new int; 
    *result = sum; 
 
    pthread_exit((void*)result);  // 
Return sum as void* 
} 
 
int main() { 
    pthread_t thread; 
    int arr[5] = {10, 20, 30, 40, 50}; 
    void* sum_ptr; 
 
     
    if (pthread_create(&thread, NULL, 
calculate_sum, (void*)arr)) { 
        cerr << "Thread creation failed!" 
<< endl; 
        return 1; 
    } 
 
     
    if (pthread_join(thread, &sum_ptr)) 
{ 
        cerr << "Thread join failed!" << 
endl; 
        return 2; 
    } 
 
    // Retrieve sum from thread 
    int* final_sum = (int*)sum_ptr; 
    cout << "Sum calculated by thread 
= " << *final_sum << endl; 
 
    delete final_sum;   
    return 0; 
} 
 
 