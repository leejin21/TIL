#include <iostream>
using namespace std;

int main()
{
    int value = 5;
    int *ptr = &value;

    cout << value << '\n';
    cout << ptr << '\n';
    cout << *ptr << '\n';
}