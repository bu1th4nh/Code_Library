# Test Generating Template and Supporting Library 

This is **Visual Studio** and **GCC** - compatible for generating test for programming contests. Up to now it can only generate fundamental data type such as integers, strings,floating-point number and Big Integers. And there will have more option in the future such as graphs, maze, etc... I use Mersenne MT19937 pseudo-random generator for producing more "random" output. You can find more information [here](https://en.wikipedia.org/wiki/Mersenne_Twister)

## What's new on Version 1.1?
* I've modified `rand_int` function, which enable it to generate bigger integer and support negative integers.
* Added scoring feature in `main.cpp` file
* And some fixes and improvements.
    

## The Test Library File - `test_lib.h`
This file contains all necessary functions to generate data with many options available. If you want to use the library, simply drop this file into the same directory with your `main.cpp` file and add this line into your code:

          #include "test_lib.h"

   * `rand_int` - Integer generator: This function generates ~~positive integer~~ - Well, now it can generate integers, both positive and negative, which have ABSOLUTE VALUE from `start` ~~(default is 0)~~ - _I've removed that default value_ -  to `limit`. And now, it supports _long long int_! You can change number type (positive, negative or both) in `SIGN_SETTING` parameter.
   * `rand_str` - String generator: This function generates strings, with upper/lowercase Latin letter and numbers, which can chage in `NUMBER_SETTINGS` and `CASE_SETTINGS` parameter, and, of course - length of the string!
   * `rand_BigInt` - Big Integers Generator - *to infinity and beyond!* - This function generates Big Integers, of course it also generates Small Int :P. The only limit is *length*
   * `rand_double` - This function generates positive floating-point numbers, and you can change the FP rounding limit and natural part limit.

## Main File - `main.cpp`
This file is the main skeleton of the generator. It provides input and answer generating, along with test-checking and judging feature with time and scoring indicator. You can see the code to understand more.

## Examples:
This is an example of using data-generating functions

       std::cout << rand_str(10, 0, 0) << std::endl;      //Generate a string with maximum length 10, use lowercase Latin letters only. 
       std::cout << rand_BigInt(1000) << std::endl;       //Generate a Big Integer <= 1e1000
       std::cout << rand_double(200, 30) << std::endl;    //Generate a FP number <= 1e200 and FP rounding limit is 1e-30.

~~**If you want to generate negative number, simply add this line after `rand_int(...)`: ` * ((rand_int(1, 0) == 1) ? -1 : 1);`**~~ - Now you don't need to do that anymore.


This template is created by [`bu1th4nh`](https://github.com/bu1th4nh) under GNU GPL v3.0 license.
