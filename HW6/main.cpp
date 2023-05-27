// main.cpp
// header
#include "vector.h"
#include <iostream>
#include <string>
using namespace std;

// the test program
int test(); // If all the tests pass, it will return 0, otherwise it will return the first error test location.

// main
int main()
{   
    // Test program description
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl << "This program is responsible for testing the Vector.h file." << endl;
    cout << "If all the tests pass, it will print 0," << endl;
    cout << "otherwise it will print the first error test location." << endl << endl;
    cout << "The output is:";
    // Output the result
    cout << test();
}

int test(){
    int output = 1;
    // Test 1
    // Test Vector();
    {
        Vector<int> v;
        if(v.size() != 0) return output;
        // if(v.capacity() != 10) return output;
        ++output;
    }
    // Test 2
    // Test Vector(int size);
    {
        int vector_size = 3;
        Vector<int> v(vector_size);
        if(v.size() != 0) return output;
        // if(v.capacity() != 3) return output;
        ++output;
    }
    // Test 3
    // Test Vector(const Vector& r);
    {
        int vector_size = 3;
        Vector<int> v0(vector_size);
        v0.push_back(1);
        Vector<int> v(v0);
        if(v.size() != 1 || v.at(0) != v0.at(0)) return output;
        ++output;
    }
    // Test 4
    // Test ~Vector();
    {
        // This has been tested in debug mode and the program has no memory leaks.
        ++output;
    }
    // Test 5
    // Test T& operator[](int index);
    // Test void push_back(const T& x);
    {
        int vector_size = 10;
        Vector<int> v(vector_size);
        for(int i = 0; i < vector_size; ++i)
        {
            v.push_back(i);
        }
        for(int i = 0; i < v.size(); ++i)
        {
            if(v.at(i) != i) return output;
        }
        ++output;
    }
    // Test 6
    // Test T& operator[](int index);
    {
        int vector_size = 10;
        Vector<int> v(vector_size);
        // it shouldn't throw exception
        try
        {
            int temp = v[-1];
            temp = v[11];
        }
        catch(const std::exception& e)
        {
            return output;
        }
        ++output;
    }
    // Test 7
    // Test T& at(int index);
    // Test void push_back(const T& x);
    {
        int vector_size = 10;
        Vector<int> v(vector_size);
        for(int i = 0; i < vector_size; ++i)
        {
            v.push_back(i);
        }
        for(int i = 0; i < v.size(); ++i)
        {
            if(v[i] != i) return output;
        }
        ++output;
    }
    // Test 8
    // Test T& at(int index);
    {
        int vector_size = 10;
        Vector<int> v(vector_size);
        bool judge = false;
        // it should throw exception
        try
        {
            int temp = v.at(-1);
        }
        catch(const std::out_of_range& e)
        {
            judge = true;
        }
        if(!judge) return output;
        ++output;
    }
    // Test 9
    // Test T& at(int index);
    {
        int vector_size = 10;
        Vector<int> v(vector_size);
        bool judge = false;
        // it should throw exception
        try
        {
            int temp = v.at(11);
        }
        catch(const std::out_of_range& e)
        {
            judge = true;
        }
        if(!judge) return output;
        ++output;
    }
    // Test 10
    // Test int size() const;
    // Test void push_back(const T& x);
    {
        int vector_size = 30;
        Vector<int> v;
        for(int i = 0; i < vector_size; ++i)
        {
            if(v.size() != i) return output;
            v.push_back(i);
        }
        ++output;
    }
    // Test 11
    // Test void clear();
    {
        int vector_size = 30;
        Vector<int> v(vector_size);
        for(int i = 0; i < vector_size; ++i)
        {
            v.push_back(i);
        }
        v.clear();
        if(v.size() != 0) return output;
        // In my Vector, the next line judgment actually will be correct, because the data is not actually deleted.
        // for(int i = 0; i < vector_size; ++i) v[i] == i;
        ++output;
    }
    // Test 12
    // Test void empty();
    {
        int vector_size = 30;
        Vector<int> v(vector_size);
        if(!v.empty()) return output;
        for(int i = 0; i < vector_size; ++i)
        {
            v.push_back(i);
        }
        v.clear();
        if(!v.empty()) return output;
        ++output;
    }
    // Test 13
    // Test void inflate();
    {
        int vector_size = 2;
        Vector<int> v(vector_size);
        if(!v.empty()) return output;
        for(int i = 0; i < 30; ++i)
        {
            v.push_back(i);
        }
        if(v.size() != 30) return output;
        // if(v.capacity() != 32) return output;
        ++output;
    }
    // Test 14
    // Test other type of Vector
    {
        Vector<double> d;
        d.push_back(1.1);
        if(d.size() != 1) return output;
        Vector<string> v(2);
        v.push_back("0");
        v.push_back("1");
        v.push_back("2");
        v.push_back(v[1]+v[2]);
        if(v.at(3) != "12") return output;
    }
    return 0;
}