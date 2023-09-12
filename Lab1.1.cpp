#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>

using namespace std;

int x = 10;
//int y = 20;

bool is_limit_reached(int val)
{
	if ((val >= 1000) || (val <= -1000))
	{
		cout << "Stop iteration! Reached value: " << val << endl;
		return true;
	}
	return false;
}

void th_1(void)
{
	while(true)
	{
		if (is_limit_reached(x))
		{
			return;
		}
		x = x - 10;
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
		x = x + 10;
		cout << "th2: " << x << endl;
	}
	return;
}
void th_3(void)
{	
	int y = 1;
	x = y + 50;
	cout << "th2: " << y << endl;
	return;
}

int call()
{
	std::thread th1(th_1);
	std::thread th2(th_2);
	th1.join();
	th2.join();
	return 0;
}
