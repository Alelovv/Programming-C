#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


bool proverka(double x, double y, double z){
	if ((x + y > z ) && (x + z > y) && (z + y > x)){
		return true ;
	}
	else{
		return false;
	}
	
	
}

double P(double x, double y, double z){	
	return x + y + z;
}

double S(double p, double x, double y, double z){
	return sqrt(p * (p - x)*(p - y)*(p - z));
}

