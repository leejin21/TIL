#include <iostream>
using namespace std;

int main()
{
    int x = 5;
    cout << x << '\n';
    cout << &x << '\n';
    cout << *&x << '\n';

    return 0;
}