I use cmake to manage the code.
Here's one way to use it in terminal:
    mkdir build
    cd build
    cmake ..
    make
    ./hw6
After creating the file, you can use "./hw6 < ../sampleinput.txt" to use the sample input I provided.
Tips: In windows, you should use "hw6" instead of "./hw6".
The typical usages and tests for Vector are in main.cpp, you can modify the code to test.
The main program will print 0 if all the test has been passed, otherwise it will print the first error location.
For convenient, I add the function capacity() when I test Vector, You can uncomment it and try it.
In my Vector, the fuction clear actually just set the size of Vector to 0, the data is not actually deleted.

Thank you for your checking.

