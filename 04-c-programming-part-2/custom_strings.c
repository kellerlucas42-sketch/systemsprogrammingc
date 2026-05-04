#include "custom_strings.h"
#include <stdio.h>

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

uint32_t getStringLength(char string[]) {
    // TODO: Implement this function
    int j = 0;
    int length = 0;
    while(string[j]){
        length++;
        j++;
    }
    return length;
}

void toUpper(char output[], char input[]) {
    char letter;
    printf("Please Enter a Lower Case Letter:");
    letter = getchar();

    if (letter >= 'a' && letter <= 'z')
        letter = letter - 'a' + 'A';
    printf("%c\n", letter);

}

int64_t findLastChar(char charToFind, char string[]) {
    // TODO: Implement this function
    return -1;
}

void getFileExtension(char extension[], char fileName[]) {
    // TODO: Implement this function
}

void combinePath(char path[], char folderName[], char fileName[]) {
    // TODO: Implement this function
}