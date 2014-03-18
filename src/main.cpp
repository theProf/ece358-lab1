//
//  main.cpp
//  lab1
//
//  Created by Gerg on 2013-01-29.
//
//

#include "main.h"

#define Q1_TIME 1000

void Question1(void);
void Question3(void);
void Question4(void);
void Question6(void);
//void Question6_2(void);

void roLoop(double start, double stop, double step, int L, int C, int K);




int main(int argc, const char * argv[])
{
	int seed = time(NULL);
	srand(seed);

//	Question1();
//    Question3();
    Question6();
//    Question6();
//    Question6_2();
}


void Question1() {
	printf("Question 1\n");
	double lambda = 75;
	double expo[Q1_TIME];
	double mean = 0;
	double variance = 0;

	for(int i = 0; i < Q1_TIME; i++) {
		expo[i] = RandomVar::Exponential(lambda);
		mean += expo[i];
	}

	mean /= (double)Q1_TIME;
	variance = pow(expo[0], 2);

	for(int i = 1; i < Q1_TIME; i++) {
		variance 		+= pow( expo[i], 2);
	}

	variance = (variance / Q1_TIME) - pow(mean, 2);

	printf("Lambda: %f\t|  Mean: %f\t|  Variance: %f\n", lambda, (double)1/lambda,  (double)1/pow(lambda, 2));
	printf("Lambda: %f\t| EMean: %f\t| EVariance: %f\n", lambda, mean,  variance);

	return;
}

void Question3() {
	int L = 120000;
	int C = pow(1024, 2);

	roLoop(0.25, 0.95, 0.1, L, C, 0);
//	EventScheduler *es = NULL;
//	for(double ro = 0.25; ro <= 0.95; ro += 0.1) {
//		es = new EventScheduler(ro, L, C);
//		es->setup();
//		es->run();
//		delete es;
//	}
}

void Question4() {
	int L = 120000;
	int C = pow(1024, 2);
	double ro = 1.2;

	EventScheduler *es = new EventScheduler(ro, L, C);
	es->setup();
	es->run();
	delete es;
}

void Question6() {
	int L = 120000;
	int C = pow(1024, 2);

//	roLoop(0.5, 1.5, 0.1, L, C, 5);
//	roLoop(0.5, 1.5, 0.1, L, C, 10);
//	roLoop(0.5, 1.5, 0.1, L, C, 40);
	roLoop(0.4, 2, 0.1, L, C, 5);
//	roLoop(2.2, 5, 0.2, L, C, 5);
//	roLoop(5.4, 10, 0.4, L, C, 5);
//	roLoop(0.4, 2, 0.1, L, C, 10);
//	roLoop(2.2, 5, 0.2, L, C, 10);
//	roLoop(5.4, 10, 0.4, L, C, 10);
//	roLoop(0.4, 2, 0.1, L, C, 40);
//	roLoop(2.2, 5, 0.2, L, C, 40);
//	roLoop(5.4, 10, 0.4, L, C, 40);

}

void roLoop(double start, double stop, double step, int L, int C, int K) {
	EventScheduler *es = NULL;
	for(double ro = start; ro <= stop; ro += step) {
		es = new EventScheduler(ro, L, C, K);
		es->setup();
		es->run();
		delete es;
	}
}
