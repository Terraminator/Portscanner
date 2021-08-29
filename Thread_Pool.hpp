#include <iostream>
#include <vector>
#include <thread>

using namespace std;


class Thread_Pool {
public:
    vector<thread> Pool;

    int wait_for_pool() {
        for (thread& t : Pool) {
            t.join();
        }
        return 0;
    }

    int start_pool(int number, int (*target)(int), int arg) {
        for (int i{ 0 }; i < number; i++) {
            loop:
            try {
                Pool.emplace_back(target, arg);
            }
            catch (...) {
                goto loop;
            }
        }
        return 0;
    }

    int start_thread(int (*target)(string, int), string sarg, int arg) {
        start:
        try {
            Pool.emplace_back(target, sarg, arg);
        }
        catch (...){
            goto start;
        }
        return 0;
    }
};