I use cmake to manage the code.
Here's one way to use it in terminal:
    mkdir build
    cd build
    cmake ..
    make
You will then see that there are four executable files: pdadd, pdlist, pdremove, pdshow.
Temporary data files will be stored in 'temp.diary' in the build folder, 
it will be read when the program runs and will be update when the program ends.

Command list:   (text in '' is the command you should input, the date format is 'xxxx-xx-xx')
pdadd: 'pdadd xxxx-xx-xx', then you are allowed to input the content.(The input will be exactly 16 characters)
    tips: Make sure your input is consistent with the sample I provided, such as 'pdadd 2002-02-02'.
pdlist: 'pdlist' will list all records' date.
        'pdlist xxxx-xx-xx' will list all the record's date after the given date.
        'pdlist xxxx-xx-xx xxxx-xx-xx' will list records' date between the two dates entered.
pdshow: 'pdshow', then you will be able to enter the date and query the corresponding record.
    tips: Press Enter twice to exit.
pdremove: 'pdremove', then you will be able to enter the date and errase the corresponding record.
    tips: Press Enter twice to exit.

Make program work together:
Obviously, the output of pdlist can be given to pdadd and pdremove.

About script:
Under ./testscript are sample scripts that show ways to make these programs work together and redirect.
add_from_file.bat shows how to add entity from file, it will add all the data in ./testdata at once
partly_delete.bat and clean.bat show how to delete records efficiently(by using pdlist and pdremove together).
partly_show.bat and show_all.bat show how to show records efficiently(by using pdlist and pdshow together).

Tips about EOF:
When emulated at the end of a file with a keyboard, 
the emulated EOF is only judged to be EOF if it is in the first place of the input character. 

Thank you for checking.