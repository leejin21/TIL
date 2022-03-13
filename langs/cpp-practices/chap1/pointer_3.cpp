#include <iostream>
using namespace std;

void doSomething(int *ptr);

int main()
{
    // 기존 포인터 널값으로 사용하는 방식
    float* ptr {0};
    float* ptr2;

    ptr2 = 0;

    if (ptr || ptr2){
        cout << "ptr is pointing to a double value." << '\n';
    } else {
        cout << "ptr, ptr2 these two are both null pointer" << '\n';
    }


    // cpp11부터 시작한 널 포인터 방식
    doSomething(nullptr);
    return 0;
}

void doSomething(int *ptr){
    if (ptr){
        cout << "You passed in " << *ptr << '\n';
    } else {
        cout << "You passed in null pointer" << '\n';
    }
}