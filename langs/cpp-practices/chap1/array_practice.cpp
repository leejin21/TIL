#include <iostream>
using namespace std;

unique_ptr<double> f(){
    return unique_ptr<double>{new double};
}

int main(){
    int* y = new int[10];
    unique_ptr<double> dp2;
    unique_ptr<double> dp3 = f();
}