#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main()
{

    pid_t q;
    q = fork();

    cout << "Creating a process : " << endl;

    if (q < 0)
    {
        cout << "some error is 
            detected "<<endl; 
    }
    else if (q == 0)
    {
        cout << "I am the child 
            process "<<endl; 
            cout
             << "My process id is : 
                "<<getpid()<<endl; 
            cout
             << "My parent's process id is : 
                "<<getppid()<<endl; 

            cout
             << "Child process is doing some 
                works...."<<endl; 

                sleep(2);
        cout << "Child process is finished and 
            terminating "<<endl;
            exit(0);
    }

    else if (q > 0)
    {

        cout << "I am the parent process 
                "<<endl; 
            cout
             << "My process id is : 
                "<<getpid()<<endl; 
            cout
             << "My child's process id is : 
                "<<q<<endl; 
            cout
             << "Waiting for the child to 
            terminate "<<endl; 
            wait(NULL);
        cout << "Child has terminated, parents 
            ends now "<<endl; 
    }
}