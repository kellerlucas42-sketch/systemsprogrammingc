#ifndef CUSTOM_STRINGS_H
#define CUSTOM_STRINGS_H

#include <stdint.h>

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


#define STR_LEN 100 // The maximum length of any string used in this lab

/*  Finds the length of the string (the number of characters preceeding the null terminator)
*   
*   You may not use the strlen() function from the string.h library
*   You may assume that the string length <= STR_LEN (defined above)
*/
uint32_t getStringLength(char string[]);


/*  Copies the input string into the output string, with all lowercase letters (a-z) replaced with
*   their uppercase equivalent (A-Z)
*
*   You may not use any function in the ctype.h library
*   You may use 1 (and only 1) if/else pair 
*       OR 1 (and only 1) ternary operator (?:)
*   You may not include any "else if" statements
*   You may not use a switch/case statement
*   You may assume that the string length <= STR_LEN (defined above)
*
*   Commment: The restrictions above are to stop you from doing 26 if/else statements to accomplish this
*             There is a more efficent way to implement this function!
*/
void toUpper(char output[], char input[]);


/*  Scans the string and returns the index of the last occurance of the given character
*   If the given character is not found, return -1
*
*   You may not use the strchr() function from the string.h library
*   You may assume that the string length <= STR_LEN (defined above)
*/
int64_t findLastChar(char charToFind, char string[]);


/*  Scans the string, assuming it's a file name.  Populates the extension string
*   with the found extension
*
*   You may assume that the string length <= STR_LEN (defined above)
*   You may assume that the string passed into the function will have one and only one extension (seperated from the file name with a period).
*
*   Comment: There aren't any restrictions on this function, but make sure you write it well
*            You may want to copy this code into a future lab.
*/
void getFileExtension(char extension[], char fileName[]);


/*  Combines a folder and file name to create a path.
*
*   You may assume that the combined string length of the folder and the path <= STR_LEN (defined above)
*   
*   Comment: There aren't any restrictions on this function, but make sure you write it well
*            You may want to copy this code into a future lab.
*/
void combinePath(char path[], char folderName[], char fileName[]);

#endif // CUSTOM_STRINGS_H