I use cmake to manage the code.
Here's one way to use it in terminal:
    mkdir build
    cd build
    cmake ..
    make
    ./hw7
Tips: In windows, you should use "hw7" instead of "./hw7".

In my memory pool, I divide each memory slice in the smallest unit of slot.
For better use the memory, we use union to store the next pointer and the element itself in the same memory.
So Pointers don't introduce extra memory, but this is unfriendly for smaller types, such as char.
(This means that it performs well for those larger types)
Thus, if time permits, I should override the memory pool for char. However, the final test is coming,
so just let it go.
The blocksize for each small memory slice is 4096.(You can change it manually in the header file)
Everything is wonderful, you can use my memory pool as same as std::allocator.
(notise MemoryPool& operator=(const MemoryPool& memoryPool) is banned)
In test.cpp, I put together some test cases. You will see the result if you run hw7.

Thank you for your checking.

