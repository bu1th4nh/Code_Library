# Test Generating Template and Supporting Library 

It's **Visual Studio** and **GCC** - compatible for generating test for programming contests. Up to now it can only generate fundamental data type such as integers, strings,floating-point number and Big Integers. And there will have more option in the future such as graphs, maze, etc... I use Mersenne MT19937 pseudo-random generator for producing more "random" output. You can find more information [here](https://en.wikipedia.org/wiki/Mersenne_Twister)

## The Test Library File - `test_lib.h`
This file contains all of the necessary function to generate data with many option available.

   * `rand_int` - Integer generator: This function generates positive integer from `start` (default is 0) to `limit`
   * `rand_str` - String generator: This function generates strings, with upper/lowercase Latin letter and numbers, which can chage in `NUMBER_SETTINGS` and `CASE_SETTINGS` parameter, and, of couurse - length of the string!
   * `rand_BigInt` - Big Integers Generator - *to infinity and beyond!* - This function generates Big Integers, of course it also generates Small Int :P. The only limit is *length*
   * `rand_double` - This function generates positive floating-point numbers, and you can change the FP rounding limit and natural part limit.

## Main File - `main.cpp`
This file is the main skeleton of the generator. It provides input and answer generating, along with test-checking and judging feature with time indicator. You can see the code to understand more.


**If you want to generate negative number, simply add this line after `rand_int(...)`: ` * ((rand_int(1, 0) == 1) ? -1 : 1);`**


This template is created by [`bu1th4nh`](https://github.com/bu1th4nh) under GNU GPL v3.0 license.
