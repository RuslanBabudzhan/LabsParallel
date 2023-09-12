#include "Lab1_1.h"
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>

using namespace std;
using namespace lab1_1;

int x = 10;
int step = 10;
int loop_limit = 1000;

bool is_limit_reached(int val)
{
	if ((val >= loop_limit) || (val <= -loop_limit))
	{
		cout << "Stop iteration! Reached value: " << val << endl;
		return true;
	}
	return false;
}

void th_1(void)
{
	while (true)
	{
		if (is_limit_reached(x))
		{
			return;
		}
		x = x - step;
		cout << "th1: " << x << endl;
	}
	return;
}

void th_2(void)
{
	while (true)
	{
		if (is_limit_reached(x))
		{
			return;
		}
		x = x + step;
		cout << "th2: " << x << endl;
	}
	return;
}


int Lab1_1::call()
{
	thread th1(th_1);
	thread th2(th_2);
	th1.join();
	th2.join();
	return 0;
}
