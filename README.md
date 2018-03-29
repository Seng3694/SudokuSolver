# Sudoku Solver #

C++ sudoku solver with backtracking algorithm inspired by [Code My Road][4].

## Backtracking Algorithm ##
![algorithm][1]


## How to use ##

Write a sudoku riddle in a text file:

```
0 0 3   0 2 0   6 0 0
9 0 0   3 0 5   0 0 1
0 0 1   8 0 6   4 0 0
    	    	    
0 0 8   1 0 2   9 0 0
7 0 0   0 0 0   0 0 8
0 0 6   7 0 8   2 0 0
    	    	    
0 0 2   6 0 9   5 0 0
8 0 0   2 0 3   0 0 9
0 0 5   0 1 0   3 0 0
```

The formatting is purely aesthetic (but it works). You can just write a 81 characters long string if that's your kind of thing.

You can either run the program with the command line or just drag&drop the file onto the executable:
```
>SudokuSolver.exe "path/to/sudoku/sudoku.txt"
```

First it prints the riddle:

![not_solved][2]

Then it solves it:

![solved][3]

## Build ##

Project uses [CMake][5] to generate platform and compiler-specific build files.

### Dependencies ###

Note that this project uses `C++14` features such as `auto` and `lambdas`, and therefore requires a `C++14` compliant compiler in order to build successfully.

### Building on Windows (Visual Studio) ###
1. Clone the repository
    ```
    git clone https://github.com/Seng3694/SudokuSolver
    ```

2. Generate the build files
    ```
    mkdir build
    cd build
    cmake -G "Visual Studio 15" ../SudokuSolver
    cmake --build . --config Release
    ```

### Building on Linux
1. Clone the repository
    ```
    git clone https://github.com/Seng3694/SudokuSolver
    ```

2. Generate the build files
    ```
    mkdir build
    cd build
    cmake -G "Unix Makefiles" ../SudokuSolver
    cmake --build . --config Release
    ```

[1]: https://codemyroad.files.wordpress.com/2014/04/output_hqxeh9.gif
[2]: https://cdn.discordapp.com/attachments/425728769236664350/428988250414383104/unknown.png
[3]: https://cdn.discordapp.com/attachments/425728769236664350/428989437557342208/unknown.png
[4]: https://codemyroad.wordpress.com/2014/05/01/solving-sudoku-by-backtracking/
[5]: http://www.cmake.org/