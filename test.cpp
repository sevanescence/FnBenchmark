#include "fnb.h"

#include <iostream>
#include <chrono>

#include <random>

void foo(int b)
{
    srand(0);

    int a = 0;
    for (int i = 0; i < 10000000; ++i)
    {
        a += rand() % 10;
    }

    std::cout << "a = " << a << '\n';
}

int bar(int a)
{
    return a + 1;
}

int baz()
{
    return 2;
}

class Class
{
public:
    Class() { std::cout << "Constructor called\n"; }
    ~Class() { std::cout << "Destructor called\n"; }
};

Class CreateClass()
{
    return Class();
}

int main()
{
    std::cout << "foo(): " << bench(&foo, 3) << "ms\n";
    std::cout << "bar(): " << bench(&bar, 5) << "ms\n";
    bench(&baz);
    std::cout << "CreateClass() " << bench(CreateClass) << "\n";
    std::cout << "End of test.\n";
}
