/*
 * RandomVar.cpp
 *
 *  Created on: Mar 16, 2014
 *      Author: gerg
 */

#include "RandomVar.h"

double RandomVar::Uniform() {
	return (double)rand()/(double)(RAND_MAX);
}

/*
 * Exponential
 */
double RandomVar::Exponential(double lambda) {
	return -(double)log(Uniform())/lambda;
}

/*
 * Poisson:
 */
int RandomVar::Poisson(double mean) { //Special technique required: Box-Muller method...
	double R;
	double sum = 0;
	int i;
	i=-1;
	double z;

	while(sum <=mean)
	{

				R = Uniform();
				z = log(R);
				sum+= z;
				i++;
	}
	return i;
}

double RandomVar::Poisson2(double mean) {
	double l = exp(-mean);
	int k = 0;
	double p = 1.0;
	do {
		p = p * Uniform();
		++k;
	} while (p > l);
	return k - 1;
}
