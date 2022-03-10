#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void write_something(ostream& os){
    os << "Hi stream, " << 3*3 << '\n';
}

int main(int argc, char* argv[]){
    ofstream myfile("example.txt");
    stringstream mysstream;

    write_something(cout);
    write_something(myfile);
    write_something(mysstream);

    cout << "mysstream is " << mysstream.str(); // 개행 포함
    // stringstream의 메소드 str()은 스트림의 내부 문자열을 반환

    cout << "pi <3 is " << (3.14<3) << '\n';
    cout << "pi <3 is " << boolalpha << (3.14<3) << endl;
}