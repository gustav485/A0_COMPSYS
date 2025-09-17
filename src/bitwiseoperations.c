#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//1. Given an integer value int x, give a C expression that returns the value multiplied by 8.
int x;
int func1(){
    return x * 8;
}

//2. Given an integer value int x, give a C expression that returns true if the value is equal to 6.
int x;
int func2(){
    if(x == 6){
        return EXIT_SUCCESS; //Or true
    }
    return EXIT_FAILURE; //Or false
}

//3. Given an integer value int x, give a C expression that returns true if the value is less than or equal to 0.
int x;
int func3(){
    if(x <= 0){
        return EXIT_SUCCESS; //Or true
    }
    return EXIT_FAILURE; //Or false
}

//4. Given integer values int x and int y, give a C expression that returns true if the value of x and y are different.
int x,y;
int func4(){
    if(x != y){
        return EXIT_SUCCESS; //Or true
    }
    return EXIT_FAILURE; //Or false
}

//5. 
