#include "Lab1_3.h"
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <thread>
#include <random>
#include <mutex>
#include <array>
#include <list>
#include <malloc.h>


using namespace std;
using namespace lab1_3;

const int entities_count = 5;
std::array<std::mutex, entities_count> forks;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distribution(500, 3000);





class Philosopher {
private:
	int philosopher_id;

public:
	Philosopher(int p_id)  {
		philosopher_id = p_id;
		cout << "init Philosopher " << p_id << endl;
	}

	void try_to_eat(std::array<std::mutex, entities_count>& forks) {
		std::list<int> my_forks_ids;

		for (int fork_id = 0; fork_id < forks.size(); fork_id++) {

			if (forks[fork_id].try_lock())
			{
				my_forks_ids.push_back(fork_id);
				
				if (my_forks_ids.size() > 1)  // We can eat - sleep rand ms, then realese all forks
				{
					std::stringstream ss;
					for (const int& num : my_forks_ids) {
						ss << num << ", ";
					}
					std::string my_forks_ids_str = ss.str();

					int rand_val = distribution(gen);

					cout << "philosopher " << philosopher_id << " started dinner for " << rand_val << " ms with forks " << my_forks_ids_str << endl;
					this_thread::sleep_for(chrono::milliseconds(rand_val));
					for (int my_hand_id = 0; my_hand_id < 2; my_hand_id++)
					{
						int my_fork_id = my_forks_ids.back();
						my_forks_ids.pop_back();
						//cout << my_fork_id << " ";
						forks[my_fork_id].unlock();
					}
					cout << endl;
					break;
					return;
				}
			//forks[fork_id].unlock();  // If falied (my_forks_ids.size() > 1) during external for loop, we have only one fork locked. So realese it.
			}
		}
	}
	std::thread try_to_eatThread(std::array <std::mutex, entities_count> &forks) {
		return std::thread([&] { try_to_eat(forks); });
	}

};

int Lab1_3::call()
{
	Philosopher* philosophers = (Philosopher*)malloc(sizeof(Philosopher) * entities_count);
	for (int i = 0; i < entities_count; ++i) {
		philosophers[i] = Philosopher(i);
	}
	std::thread philosopher_threads[entities_count];

	while (true) {
		for (int i = 0; i < entities_count; ++i) {
			philosopher_threads[i] = philosophers[i].try_to_eatThread(forks);
			philosopher_threads[i].detach();
		}
		/*
		for (int i = 0; i < entities_count; ++i) {
			philosopher_threads[i].join();
		}
		*/
	}

	return 0;
}
