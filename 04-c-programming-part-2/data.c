#include "data.h" // This is this file's related .h file

//  ____________ A note on .h and .c files ____________
//                                                              
//  In the data.h file, you can read an explaination of how .h  
//  and .c files are split up.                                  
//                                                              
//  Here in the data.c file, you can see the implementation of  
//  the functions that we included in data.h.  This is the nitty
//  gritty of the code.                                         
//                                                              
//  If you change the anything in the functions signature (IE   
//  its name, return type, or parameter names/types), then you  
//  will need to update both files.                             
//                                                              



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

double calculateCircumference(double radius) {
    // TODO: Fix this function
    if(radius < 0) return -1;
    double circumference = radius * TWO_PI;
    return circumference;
}

double calculateAverage(int data[5]) {
    // TODO: Fix this function
    double sum = 0;
    for (int i = 0; i <= 5; i++) {
        sum += data[i];
    }
    return sum / 5;
}

uint8_t anyBitIsOne(int32_t input) {
    // TODO: Implement this function
    uint32_t test = 4294967295;
    return input && test;
}

uint8_t anyBitIsZero(int32_t input) {
    // TODO: Implement this function
    return !input;
}

int8_t extractFromWord(uint32_t word, uint8_t bytenum) {
    // TODO: Implement this function
    return ((unsigned)word >> (bytenum << 3)) & 0xFF;}

uint32_t mutliplyByBase2(uint32_t num, uint32_t power) {
    // TODO: Implement this function
    uint32_t answer = num * (2);
    return 0;
}

int8_t checkIfSpace(int val, int maxBytes) {
    // TODO: Fix this function
    if (maxBytes - sizeof(val) >= 0) {
        return 1;
    } else {
        return 0;
    }
}
