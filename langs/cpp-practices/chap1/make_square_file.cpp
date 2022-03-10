#include <fstream>

int main(){
    // #1 표준 입력
    std::ofstream square_file;
    square_file.open("squares.txt");
    for (int i=0; i<10; i++)
        square_file << i << "^3 = " << i * i * i << std::endl;
    square_file.close();

    // #2 암시적으로 닫는다
    std::ofstream square_file("squares.txt");
    for (int i=0; i<10; i++)
        square_file << i << "^2 = " << i * i << std::endl;

}