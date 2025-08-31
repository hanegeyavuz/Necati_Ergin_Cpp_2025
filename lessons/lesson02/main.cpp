#include <iostream>
#include <stdio.h>

#if 1
struct Point{
	double x,y;
};

int main(){

	Point mypoint = {2.,6.}; //ILLEGAL in C Programming, LEGAL in C++
}
#endif
