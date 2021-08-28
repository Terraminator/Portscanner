#include <iostream>
#include <vector>
#include <thread>

using namespace std;


class Thread_Pool {
public:
    vector<thread> Pool;

    int start_pool() {
        for (thread& t : Pool) {
            t.join();
        }
        return 0;
    }

    int create_pool(int number, int (*target)(int), int arg) {
        for (int i{ 0 }; i < number; i++) {
            Pool.emplace_back(target, arg);
        }
        return 0;
    }

    int add_thread_to_pool(int (*target)(string, int), string sarg, int arg) {
        Pool.emplace_back(target, sarg, arg);
        return 0;
    }
};