#ifndef DATA_H // This is a simple guard to check that the .h file hasn't already been included by the compiler
#define DATA_H

#include <stdint.h>

#define PI       3.14159
#define TWO_PI   (PI + PI) // You may change this value if nessecary


//  ____________ A note on .h and .c files ____________
//                                                               
//  Functions can be split between .c and .h files Typically,    
//  .h files contain function declarations and global constants. 
//  .c files contain the implementation of those functions.      
//                                                               
//  This allows .h files to simply show a user what a            
//  function does needing to show everything going on under      
//  the hood.                                                    
//                                                               
//  If you are familar with other programming languages,         
//  this may be compared to private and public methods.          
//  .h files are for the public; .c files are for the            
//  programmer.                                         


//  ____________ Instructions on this assignment ____________
//
//  You will either need to implement or debug all of the
//  functions in data.c and custom_strings.c.
//
//  As you code, follow the following rules:
//  1.  Unless specified in the function, do not change the
//      data types.
//  2.  If you need to change a data type to a floating-point
//      number, then use `double`, not `float`.  This is for
//      the autograder. 
//  3.  You can use printf() statments for debugging data.c and
//      custom_strings.c, but comment them out or remove them 
//      before you pass off.
//  4.  If there are any specific rules for the fuction, follow
//      them.
//
//  Here's a bit of advice:
//  1.  Look up what a bit mask is.
//  2.  Recall what bitwise operations do.
//  3.  Use plenty of printf() statements when you debug.
//  4.  It's better to have code that is broken up and easy
//      to read than code that is compact.
//
//  Good luck!




/*  A premade function that calculates the circumference of a circle from the radius.
*   The function should be able to handle decimal as well as whole numbers.
*
*   If the radius is negative, return -1.
*   
*   The function is already written, but buggy. You will need to fix it.
*
*   You may change data types of the return address and the radius. NOTE: If you need 
*   use a number with a decimal point, use a double instead of a float for this problem. 
*/
double calculateCircumference(double radius);


/*  Given an array of 5 integers, outputs the average.  
*   Output should be a decimal.
*
*   The function is already written, but buggy. You will need to fix it.
*
*   You may not change the data type of the return address or the input.
*   You may change data types within the function.
*/
double calculateAverage(int data[5]);

/*  If any bit in input is 1, returns 1   
*   Else, returns 0
*
*   You may not use the equality (==) or inequality (!=) operators
*   You also may not use an if statement or the ternary operator (:?)
*   You may not use a for or while loop
*
*   See problem 2.61 in the textbook
*/
uint8_t anyBitIsOne(int32_t input);


/*  If any bit in input is 0, return 1 
*   Else, returns 0
*
*   You may not use the equality (==) or inequality (!=) operators
*   You also may not use an if statement or the ternary operator (:?)
*   You may not use a for or while loop
*
*   See problem 2.61 in the textbook
*/
uint8_t anyBitIsZero(int32_t input);


/*  This function should take a "packed" integer with 32 bytes (AKA a "word") and unpack a 
*   single signed byte. For example, if I had 4 'int8_t's: 0xDE, 0xAD, 0xBE, 0xEF, I could put 
*   them together into one larger uint32_t: 0xDEADBEEF.
*
*   This function extracts one of the small ints based on its position in the larger int.
*   extractFromWord(0xDEADBEEF, 1) would return 0xAD
*
*   Assume positioning is 0x(0, 1, 2, 3)
*
*   You may not use any if/else statements
*   You may not use the ternary operator (?:)
*
*   Based off of problem 2.71 in the textbook
*/
int8_t extractFromWord(uint32_t word, uint8_t bytenum);


/*  Multiplies the num by 2^power.
*   You may not use any loop or recursion
*   You may not use an external library with a power function
*   You may assume that num will not be non-zero and positive
*/
uint32_t mutliplyByBase2(uint32_t num, uint32_t power);

/*  This function checks if there is enough space in memory to copy the value 
*   of val in.  If there is enough space, it returns 1.  Otherwise, it will return 0.
*
*   The idea here is that if the block of memory doesn't have enough space
*   left, trying to copy over the int anyways would cause a memory leak; a
*   bug where your data is erased.  Memory leaks pose a security risk that
*   can be exploited by hackers.  Unfortunately, this function was used in 
*   industry in a popular library for a long time before the bug was 
*   discovered.
*
*   The orignal code (seen in problem 2.72 in the textbook) uses the function "memcpy"
*   to copy the value over into the block of memory.  You'll learn how to use
*   that function later.  For this lab, we have simplified the function.
*
*   The function is already written, but buggy. You will need to fix it.
*
*   The size of the memory is indicated by "maxBytes," and the value is indicated
*   by "val."
*
*   You may change the data type of the parameters if nessecary.
*
*   (Hint: You should look up what the sizeof() function does)
*/
int8_t checkIfSpace(int val, int maxBytes);
#endif // DATA_H
