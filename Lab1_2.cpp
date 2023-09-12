#include "Lab1_2.h"
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>
#include <mutex> 
#include <list>
#include <random>
#include <chrono>
#include <sstream>

using namespace std;
using namespace lab1_2;


std::list<int> x;
std::mutex m;
int list_size_limit = 10;


void thread_func1()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	while(true) {
		m.lock();

		if (x.size() > list_size_limit)
		{
			m.unlock();
			std::cout << "thread_func1 ended\n";
			return;
		}

		std::uniform_int_distribution<int> distribution(1, 100);

		int rand_val = distribution(gen);

		x.push_back(rand_val);
		m.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

void thread_func2()
{
	while (true) {
		m.lock();

		if (x.size() > list_size_limit)
		{
			m.unlock();
			std::cout << "thread_func2 ended\n";
			return;
		}
		std::cout << "our array: ";
		for (int v : x)
		{
			std::cout <<  v << ", ";
		}
		std::cout << "\n";
		m.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}


int Lab1_2::call()
{
	std::thread th1(thread_func1);
	std::thread th2(thread_func2);

	th1.join();
	th2.join();

	return 0;
}
