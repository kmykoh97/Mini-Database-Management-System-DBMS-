/*
program to test char and int size of your computer
*/

#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main()
{
    cout << "size of int: " << sizeof(int) << endl;
    cout << "size of char: " << sizeof(char) << endl;
    cout << "size of long int: " << sizeof(long int) << endl;

    int imin = std::numeric_limits<int>::min(); // minimum value
    int imax = std::numeric_limits<int>::max();

    cout << imin << endl;
    cout << imax << endl;

    system("pause");
    return 0;
}