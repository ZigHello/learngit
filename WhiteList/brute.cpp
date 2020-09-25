//brute.cpp
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

const int w_1m = 1000000;
int w[w_1m];


int Half_Search(int t, int low, int high)
{
    int  mid;
    mid = (high + low) / 2;
    if (w[mid] == t)
    {
        return false;
    }
    else if (low >= high)
    {
        return 1;
    }
    else if (w[mid] > t)
    {
        return Half_Search(t, low, mid - 1);
    }
    else if (w[mid] < t)
    {
        return Half_Search(t, mid + 1, high);
    }
    return true;
}

/*
bool is_match(int t, int w[], int w_length)
{
    for (int i = 0; i < w_length; i++)
    {
        if (t == w[i])
        {
            return false;
        }
    }
    return true;
}

*/

// brute -w whitelist < T
int main(int argc, char* argv[])
{
    if (argc != 3 || strcmp(argv[1], "-w"))
    {
        return 1;
    }

    // init w
    ////    for(int i=0;i<w_1m)
    ////    {
    ////        w[i]=-1; //填充非法数据
    ////    }
    ifstream infile;
    infile.open(argv[2]);
    int i = 0;
    cout << argv[2] << endl;
    while (infile >> w[i++])
    {
    }
    int w_length = i - 1;
    cout << w_length << endl;
    // check t
    int t = 0;
    while (cin >> t)
    {
        if (Half_Search(t, 0, w_length))
        {
            cout << t << endl;
        }
    }
}