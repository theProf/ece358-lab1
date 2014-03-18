/*
 * RandomVar.h
 *
 *  Created on: Mar 16, 2014
 *      Author: gerg
 */

#ifndef RANDOMVAR_H_
#define RANDOMVAR_H_

#include <cmath>
#include <cstdlib>

class RandomVar {
public:
	static double Uniform(void);
	static double Exponential(double lambda);
	static int Poisson(double mean);
	static double Poisson2(double mean);
};


#endif /* RANDOMVAR_H_ */
