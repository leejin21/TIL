#include <iostream>
using namespace std;

void celebrateBirthday(int* age);

int main(){
    int myAge = 25;

    cout << "Before function, age: " << myAge << endl;

    celebrateBirthday(&myAge);

    cout << "After Function, age: " << myAge << endl;

}

void celebrateBirthday(int* age){
    (*age)++;
    cout << "Yeeeey, celebrated " << *age << ". birthday" << endl;
}