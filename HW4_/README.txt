I use cmake to manage the code.
Here's one way to use it in terminal:
    mkdir build
    cd build
    cmake ..
    make
    ./hw4
Tips: In windows, you should use "hw4" instead of "./hw4".
Tips: In program, you can input "help" to get help.

EOF:
When emulated at the end of a file with a keyboard, 
the emulated EOF is only judged to be EOF if it is in the first place of the input character. 
if it is not in the first place, it will be read as a character with the value 26. 
So the program is doing both of these things.

Command list:   (text in '' is the command you should input, the date format is 'xxxx-xx-xx')
pdadd: 'pdadd xxxx-xx-xx', then you are allowed to input the content.(The input will be exactly 16 characters)
    tips: Make sure your input is consistent with the sample I provided, such as 'pdadd 2002-02-02'.
pdlist: 'pdlist []' will list all records.
        'pdlist xxxx-xx-xx xxxx-xx-xx' will list records between the two dates entered.
pdshow: 'pdshow xxxx-xx-xx', as same as pdadd.(The input will be exactly 17 characters)
pdremove: 'pdremove xxxx-xx-xx', as same as pdadd.(The input will be exactly 19 characters)
load: 'load', then you are allowed to input the load_path to load data from existing file.
    tips: The program can only read files with the ".diary" suffix.
store_to: 'store_to', then you are allowed to change the store_path to save data to file.
    tips: When not specified, the default output path is "temp.diary".
    tips: Please make sure the store_path ends with ".diary", otherwise it will not be able to be loaded by this program.
store: 'store' or 'save', to save data immediately.
exit: 'q' or 'Q' or 'exit', to exit progrem.

Thank you for checking.