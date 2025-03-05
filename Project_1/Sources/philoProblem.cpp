//
// Created by mateu on 04.03.2025.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <semaphore>
#include "philoProblem.h"

using namespace std;

void philosopher_activity(int);
bool take_fork(int, int);
void put_fork(int, int);
void thinking(int);
void eating(int);
void display_philosophers_activity();

mutex display_mutex;

#define N 5

int forks[5];                                         // semaphores {0 - fork is used, 1 - fork is free}
int philosophers_id[5];
string philosophers_state[5];
thread philosophers[5];

void startup() {

    for(int i = 0; i < N; i++) {
        forks[i] = 1;
        philosophers_id[i] = i+1;
        philosophers_state[i] = "thinking";
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

        bool tf_l = take_fork(philosopher_id, left_fork_id);                    // take left fork

        if (tf_l) {
            bool tf_r = take_fork(philosopher_id, right_fork_id);               // take right fork

            if(tf_r) {                                                          // if philosopher took left and right fork
                philosophers_state[philosopher_id-1] = "eating";
                cout << "Tak" << endl;
                // display_mutex.lock();
                system("cls");
                display_philosophers_activity();
                // display_mutex.unlock();
                eating(philosopher_id);

                put_fork(philosopher_id, left_fork_id);
                put_fork(philosopher_id, right_fork_id);
                philosophers_state[philosopher_id-1] = "thinking";

                // display_mutex.lock();
                system("cls");
                display_philosophers_activity();
                // display_mutex.unlock();
                thinking(philosopher_id);
            }

        } else {
            put_fork(philosopher_id, left_fork_id);
        }

    }
}

bool take_fork(int philosopher_id, int fork_id) {
    if(forks[fork_id] == 1) {
        forks[fork_id] = 0;
        // cout << philosopher_id << " philosopher took " << fork_id << " fork" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        return true;
    }
    return false;
}

void put_fork(int philosopher_id, int fork_id) {
    if(forks[fork_id] == 0) {
        forks[fork_id] = 1;
        // cout << philosopher_id << " philosopher put back " << fork_id << " fork" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void thinking(int philosopher_id) {
    // cout << philosopher_id << " philosopher is thinking" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void eating(int philosopher_id) {
    // cout << philosopher_id << " philosopher is eating" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void display_philosophers_activity() {

    for(int i = 0; i < N; i++) {
        cout << philosophers_id[i] << " philosopher is " << philosophers_state[i] << endl;
    }
}