#include "fnb.h"

#include <iostream>
#include <chrono>

#include <random>

void foo()
{
	srand(0);

	int a = 0;
	for (int i = 0; i < 10000000; ++i)
	{
		a += rand() % 10;
	}

	std::cout << "a = " << a << '\n';
}

int main()
{
	std::cout << "foo(): " << bench(&foo) << "ms\n";
}
