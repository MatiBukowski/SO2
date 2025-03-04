//
// Created by mateu on 04.03.2025.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "philoProblem.h"

using namespace std;

void philosopher_activity(int);
void take_fork(int, int);
void thinking(int);

#define N 5

int forks[5];                                         // semaphores {0 - fork is used, 1 - fork is free}
int philosophers_id[5];
string philosophers_state[5];
thread philosophers[5];

void startup() {
    for(int& fork : forks) {
        fork = 1;
    }

    for(int i = 0; i < N; i++) {
        philosophers_id[i] = i+1;
    }

    for(string& philosopher_state : philosophers_state) {
        philosopher_state = "thinking";
    }

    for(int i = 0; i < N; i++) {
        philosophers[i] = thread(philosopher_activity, i+1);
    }

    // for(int i = 0; i < N; i++) {
    //     philosophers[i].join();
    // }

}

void philosopher_activity(int philosopher_id) {
    int left_fork_id = philosopher_id;
    int right_fork_id = (philosopher_id + 1)%N;

    while(true) {
        thinking(philosopher_id);

        take_fork(philosopher_id, left_fork_id);                // take left fork
        take_fork(philosopher_id, right_fork_id);               // take right fork


    }
}

void take_fork(int philosopher_id, int fork_id) {
    if(forks[fork_id] == 1) {
        forks[fork_id] = 0;
        cout << philosopher_id << " philosopher took " << fork_id << " fork" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

}

void thinking(int philosopher_id) {
    cout << philosopher_id << " philosopher is thinking" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
}