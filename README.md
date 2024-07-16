# Maze_CPP
Maze generator &amp; solve program C++ (for Ubuntu / MacOS)
Maze is a program for generating, solve mazes, read and save mazes from files.

## Requirements:
- Ubuntu or MacOS operating system;
- Qt version 6+ (e.g. qt-6-base-dev for Ubuntu);
- OpenGL libraries;
- Cmake for compiling;

## Basic properties:
- GUI implementation, based on Qt library;
- Maximum size of the maze is 50x50;
- The loaded maze render on the screen in a field of 500 x 500 pixels;
- "Wall" thickness is 2 pixels;
- Ability to automatically generate a perfect maze. A maze is considered perfect if it is possible to get from each point to any other point in exactly one way;
- The program generates the maze according to Eller's algorithm;
- The generated maze does not have isolations and loops;
- The user able to choose only the dimensionality of the maze: the number of rows and columns;
- The generated maze must be saved in the file format described beyond:
  
## Maze description
The maze can be stored in a file as a number of rows and columns, as well as two matrices containing the positions of vertical and horizontal walls respectively.
The first matrix shows the wall to the right of each cell, and the second - the wall at the bottom.
An example of such a file:
```
4 4
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1

1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1
```
The maze described in this file:

![alt-текст](https://github.com/Apsaraconda/Maze_CPP/raw/main/materials/maze4.jpg "Example maze")

## Solving the maze
Program is able to show the solution to any maze currently shown on the screen

## Compilation:

Use "make" command:
```
make install
```
The command installs the program to "Maze_CPP" directory.

(for Ubuntu) If your system does not have qt ver.6+ or OpenGL libraries installed:
```
make libs_install
```
or manually run the command:
```
sudo apt-get install qt6-base-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
```
## Uninstall:
```
make uninstall
```
Or delete app's directory.

## Run:
```
make run
```
Or manually open "Maze_CPP" file.

## Zip compiled program:
```
make dist
```
It makes "Maze_CPP.tar.gz" file.

## Compile and open readme.dvi:
```
make dvi
```
If you have not installed "latex" command:
```
make latex_install
```
