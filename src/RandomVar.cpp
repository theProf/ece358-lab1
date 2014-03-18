/*
 * RandomVar.cpp
 *
 *  Created on: Mar 16, 2014
 *      Author: gerg
 */

#include "RandomVar.h"

float RandomVar::Uniform() {
	return (float)rand()/(float)(RAND_MAX);
}

/*
 * Exponential
 */
float RandomVar::Exponential(float lambda) {
	return -(float)log(Uniform())/lambda;
}

/*
 * Poisson:
 */
int RandomVar::Poisson(float mean) { //Special technique required: Box-Muller method...
	float R;
	float sum = 0;
	int i;
	i=-1;
	float z;

	while(sum <=mean)
	{

				R = Uniform();
				z = log(R);
				sum+= z;
				i++;
	}
	return i;
}

float RandomVar::Poisson2(float mean) {
	float l = exp(-mean);
	int k = 0;
	float p = 1.0;
	do {
		p = p * Uniform();
		++k;
	} while (p > l);
	return k - 1;
}
