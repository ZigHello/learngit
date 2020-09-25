//create.cpp
#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;

int main(int argc, char* argv[])
{
    //atoi()将字符串转换为int型，形参是const char*
    int num = atoi(argv[1]);
    
    srand((unsigned)time(NULL));
    for (int i = 0; i < num; i++)
    {
        cout << rand() << "\n";
    }
    cout << endl;
    return 0;
}