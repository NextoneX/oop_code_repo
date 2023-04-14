I use cmake to manage the code.
Here's one way to use it in terminal:
    mkdir build
    cd build
    cmake ..
    make
    ./hw3
Tips: In windows, you should use "hw3" instead of "./hw3".
In this homework, you need to select level, input name.
In each room, input "go $(exit)" to exit.
For example, "go east" is vaild when the room allows you to leave on the east, but "east" is invalid.
Thank you for checking.