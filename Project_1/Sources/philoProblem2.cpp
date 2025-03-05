//
// Created by mateu on 05.03.2025.
//
//
// Created by mateu on 04.03.2025.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <semaphore>
#include "philoProblem2.h"

using namespace std;

void philosopher_activity2(int);
void take_fork2(int, int);
void put_fork2(int, int);
void thinking2(int);
void eating2(int);
void display_philosophers_activity2();

mutex display_mutex2;

#define N 5

// binary_semaphore forks[N];
// vector<binary_semaphore> forks;
// vector<binary_semaphore> forks2(N, binary_semaphore(1));
binary_semaphore forks2[N] { binary_semaphore(1), binary_semaphore(1),
                                binary_semaphore(1), binary_semaphore(1), binary_semaphore(1) };
int philosophers_id2[5];
string philosophers_state2[5];
thread philosophers2[5];

void startup2() {

    for(int i = 0; i < N; i++) {
        // new (&forks[i]) binary_semaphore(1);
        // forks.emplace_back(1);                                      // emplace_back - automatic constructor of vector's type object
        philosophers_id2[i] = i+1;
        philosophers_state2[i] = "thinking";
        philosophers2[i] = thread(philosopher_activity2, i+1);
    }

    // for(int i = 0; i < N; i++) {
    //     philosophers[i].join();
    // }

}

void philosopher_activity2(int philosopher_id) {
    int left_fork_id = philosopher_id - 1;
    int right_fork_id = (philosopher_id-1 + 1)%N;

    while(true) {
        thinking2(philosopher_id);
        take_fork2(philosopher_id, left_fork_id);

        if (forks2[right_fork_id].try_acquire()) {
            philosophers_state2[philosopher_id-1] = "eating";
            display_mutex2.lock();
            system("cls");
            display_philosophers_activity2();
            display_mutex2.unlock();
            eating2(philosopher_id);

            put_fork2(philosopher_id, left_fork_id);
            put_fork2(philosopher_id, right_fork_id);

            philosophers_state2[philosopher_id-1] = "thinking";
            display_mutex2.lock();
            system("cls");
            display_philosophers_activity2();
            display_mutex2.unlock();
            thinking2(philosopher_id);
        } else {
            put_fork2(philosopher_id, left_fork_id);
        }
    }
}

void take_fork2(int philosopher_id, int fork_id) {
    forks2[fork_id].acquire();
    // cout << philosopher_id << " philosopher took " << fork_id << " fork" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
}

void put_fork2(int philosopher_id, int fork_id) {
    forks2[fork_id].release();
    // cout << philosopher_id << " philosopher put back " << fork_id << " fork" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));

}

void thinking2(int philosopher_id) {
    // cout << philosopher_id << " philosopher is thinking" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void eating2(int philosopher_id) {
    // cout << philosopher_id << " philosopher is eating" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void display_philosophers_activity2() {

    for(int i = 0; i < N; i++) {
        cout << philosophers_id2[i] << " philosopher is " << philosophers_state2[i] << endl;
    }
}