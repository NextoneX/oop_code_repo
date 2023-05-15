// main.cpp
// header
#include "vector.h"
#include <iostream>
using namespace std;
//main
int main()
{   
    //!todo 
    //some test
    Vector<int> v1(2);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    cout << v1[1] << " " << v1.at(1) << " " << v1.size() << " " << v1.capacity() << " " << v1.empty() << endl;
    v1.clear();
    cout << v1[1] << " " << v1.size() << " " << v1.empty() << endl;
    try
    {
        v1.at(1);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        v1.at(-1);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    Vector<int> v2 = v1;
    for(int i = 0; i<30; ++i) v2.push_back(1);
    cout << v2.size() << " " << v2.capacity() << endl;
}