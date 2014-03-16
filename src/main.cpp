//
//  main.cpp
//  lab1
//
//  Created by Gerg on 2013-01-29.
//
//

#include "main.h"

#define Q1_TIME 100000

void Question1(void);
void Question3(void);
//void Question4(void);
//void Question6(void);
//void Question6_2(void);

int main(int argc, const char * argv[])
{
	int seed = time(NULL);

	srand(seed);

	Question1();
    Question3();
//    Question4();
//    Question6();
//    Question6_2();
}

void Question1() {
	printf("Question 1\n");
//	float lambda = 75;
//	float expo[Q1_TIME];
//	float mean = 0;
//	float variance = 0;
//
//	EventScheduler *es = new EventScheduler();
//
//	for(int i = 0; i < Q1_TIME; i++) {
//		expo[i] = es->Exponential(1/lambda);
//		mean += expo[i];
//	}
//
//	mean /= (float)Q1_TIME;
//	variance = pow(expo[0], 2);
//
//	for(int i = 1; i < Q1_TIME; i++) {
//		variance 		+= pow( expo[i], 2);
//	}
//
//	variance = (variance / Q1_TIME) - pow(mean, 2);
//
//	printf("Lambda: %f\t|  Mean: %f\t|  Variance: %f\n", lambda, (float)1/lambda,  (float)1/pow(lambda, 2));
//	printf("Lambda: %f\t| EMean: %f\t| EVariance: %f\n", lambda, mean,  variance);

	return;
}

void Question3() {
	int L = 12000; // bits
	int C = 1048576; // bits / second

	for(float Ro = .25; Ro < 0.95; Ro += 0.1) {
		EventScheduler *es = new EventScheduler(Ro, L, C);
		es->setup();
		es->run();
		delete es;
	}
}

