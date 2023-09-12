#include <iostream>
#include "Lab1_1.h"
#include "Lab1_2.h"
#include "Lab1_3.h"

using namespace std;
using namespace lab1_1;
using namespace lab1_2;
using namespace lab1_3;



int main()
{	
	int task = 1;
	cout << "Please select task: \n1 - thread races,\n2 - random list,\n3 - philosophers;\n";
	cin >> task;
	switch (task)
	{
	case 1:
		Lab1_1 lab1_executor;
		lab1_executor.call();
		break;
	case 2:
		Lab1_2 lab2_executor;
		lab2_executor.call();
		break;
	case 3:
		Lab1_3 lab3_executor;
		lab3_executor.call();
		break;
	}
	return 0;
}
