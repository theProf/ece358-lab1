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
	static float Uniform(void);
	static float Exponential(float lambda);
	static int Poisson(float mean);
	static float Poisson2(float mean);
};


#endif /* RANDOMVAR_H_ */
