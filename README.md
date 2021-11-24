# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
  * SDL TTF -> sudo apt install libsdl2-ttf-dev
  * I also ran sudo apt-get install libsdl-ttf2.0-dev
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Rubric points
* The project demonstrates an understanding of C++ functions and control structures.
    * [A function to parse the file is defined on line 16 of game.cpp](src/game.cpp)
    * [A while loop/if and switch statements are used throughout game.cpp (line 75 for instance)](src/game.cpp)
* The project reads data from a file and process the data, or the program writes data to a file.
    * [Reads and saves game data on line 58 of game.cpp](src/game.cpp)
* The project accepts user input and processes the input.
    * [Capturing user input on line 77 of game.cpp](src/game.cpp)
* The project makes use of references in function declarations.
    * [parse\_game\_file on line 16 of game.cpp uses pass by reference](src/game.cpp)
    * [RenderText on line 155 of renderer.cpp uses pass by reference](src/renderer.cpp)
* The project uses Object Oriented Programming techniques.
    * [BonusFood class is created from abstract class GameObject](src/bonus_food.h)
* Classes use appropriate access specifiers for class members.
    * [BonusFood members/methods are specified as either private or public](src/bonus_food.h)
* Class constructors utilize member initialization lists.
    * [BonusFood constructor utilizes list initialization on line 4](src/bonus_food.cpp)
* Classes abstract implementation details from their interfaces.
    * [Class member functions document their effects at the header file](src/bonus_food.h)
* Classes follow an appropriate inheritance hierarchy.
    * [Composition is used to create BonusFood class from abstract class game\_object](src/game_object.h)
* Derived class functions override virtual base class functions.
    * [Member functions (Render line 62 and Update line 105) of BonusFood override virtual base class methods](src/bonus_food.h)

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
