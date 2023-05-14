I use cmake to manage the code.
Here's one way to use it in terminal:
    mkdir build
    cd build
    cmake ..
    make
    ./hw5
After creating the file, you can use "./hw5 < ../sampleinput.txt" to use the sample input I provided.
Tips: In windows, you should use "hw5" instead of "./hw5".
The typical usages for fraction are in main.cpp, you can modify the code to test.

Necessary statement:
If you use the default ctor, the dividend will be initialized as 0 while the divisor will be 1.

When use the ctor takes two integers as parameters(dividend and divisor), the dividend and divisor will be automatically divided(by using GCD). This ctor won't allow you input 0 as the divisor(which will incur the div 0 error)

In the ctor about conversion from a finite decimal string, I use stoi() in <string>, if the input don't have '.', the divisor will be 1. Otherwise, the decimal will be converted to an integer and assigned to the dividend. The divisor will be the number multiplied by the decimal of the transformation.

The `to_string` function will transfer this fraction to string. It has a parameter `decimal_digits` to control the number of digits after the decimal point(the default value is 2), the result will be round down. If you set decimal_digits as 0 or a negetive number, the output of 1.1(11/10) will be "1." for example. But if the dividend is 0, it will output "0" no matter what decimal_digits is.

Thank you for your checking.