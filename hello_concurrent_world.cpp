// A simple exmaple demonstrating thread usage in modern C++
// Environment: MinGW64 (Windows 11)
// Build with: g++ -std=c++17 hello_concurrent_world.cpp -o hello_concurrent_world.exe

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>           

std::mutex cout_mutex;

void hello()                       
{
    for (int i=0; i<100; i++)
    {
        std::lock_guard<std::mutex> lock(cout_mutex); // std::cout is not re-entrant
        std::cout << i << " : Hello Concurrent World!\n"; 

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void worker(int id)
{
    for (int i=0; i<100; i++)
    {
        std::lock_guard<std::mutex> lock(cout_mutex); // std::cout is not re-entrant
        std::cout << i << " : I'm Worker " << id << " employed for your concurrent work.\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main()
{
    std::thread t1(hello);
    std::thread t2(worker, 1);
    std::thread t3(worker, 2);

    t1.join();
    t2.join();
    t3.join();
}
