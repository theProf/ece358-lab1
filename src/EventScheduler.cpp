/*
 * EventScheduler.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: gerg
 */

#include "EventScheduler.h"

#define TIME_MULTIPLIER 	100					// 1 - secs, 1000 - ms, 1000000 - ns
#define TIME 				10000 	// secs

bool comparator(Event one, Event two) {
	return one.time < two.time;
}

EventScheduler::EventScheduler() {
	this->Ro = 0;
	this->lambda = 0;
	this->alpha = this->lambda;
	this->L = 0;
	this->C = 0;
	this->K = -1;
	el	= new std::list<Event>();
	this->Na	= 0;
	this->Nd	= 0;
	this->No	= 0;
	this->Ndr	= 0;
	this->En	= 0;
	this->Et	= 0;
	this->idle	= 0;
}

EventScheduler::EventScheduler(float pRo, int pL, int pC) {
	this->Ro = pRo;
	this->lambda = pRo*pC/pL;
	this->alpha = this->lambda;
	this->L = pL;
	this->C = pC;
	this->K = -1;
	el	= new std::list<Event>();
	this->Na	= 0;
	this->Nd	= 0;
	this->No	= 0;
	this->Ndr	= 0;
	this->En	= 0;
	this->Et	= 0;
	this->idle	= 0;
}

EventScheduler::EventScheduler(float pRo, int pL, int pC, int pK) {
	this->Ro = pRo;
	this->lambda = pRo*pC/pL;
	this->alpha = this->lambda;
	this->L = pL;
	this->C = pC;
	this->K = pK;
	el	= new std::list<Event>();
	this->Na	= 0;
	this->Nd	= 0;
	this->No	= 0;
	this->Ndr	= 0;
	this->En	= 0;
	this->Et	= 0;
	this->idle	= 0;
}

EventScheduler::~EventScheduler() {
	delete el;
}

void EventScheduler::setup() {
	populateArrivals();
	populateObservers();

	sortES();
	return;
}

void EventScheduler::sortES() {
	el.sort(comparator);
}

void EventScheduler::run() {
	float last_departure = 0;
	for(std::list<Event>::iterator cur_event = el.begin(); cur_event != el.end(); ++cur_event) {
//		Event cur_event = *(ce);
		switch (cur_event->type) {
			case ARRIVING:
//				if(K != -1 && Na - Nd >= K) {
//					++Ndr;
//					continue;
//				}

				++Na;
				// take into account buffer delay
				float Td;
				Td = (last_departure > cur_event->time
							? last_departure
							: cur_event->time)
						+ ((float)cur_event->length / (float)C);

				if(Td < TIME) {
					// create departure
//					el.insert(new Event(Td, DEPARTING));
					el.push_front(*(new Event(Td, DEPARTING)));
					last_departure = Td;
					Et += Td - cur_event->time;
				}
				break;
			case DEPARTING:
				++Nd;

				break;
			case OBSERVING:
				++No;

				idle = Na == Nd ? ++idle : idle;

				En += Na - Nd;
				break;
			default:
				break;
		}
		delete &cur_event;
	}

	printf("ro: %f\t| lambda: %f\t| E[N]: %f\t| E[T]: %f\t| Pidle: %f\n", this->Ro, this->lambda, (float)En/(float)No, (float)Et/(float)Nd, (float)idle/(float)No);
}

void EventScheduler::populateArrivals() {
	Event *e = NULL;
	float time = 0;
	time += Exponential(lambda);
	while ( time < TIME ) {
		e = new Event(time, ARRIVING);
		e->length = (int)Exponential(1.0 / (float)L);
		el.push_back(*e);
		time += Exponential(lambda);
	}

}

void EventScheduler::populateObservers() {
	Event *e = NULL;
	float time = 0;
	time += Exponential(alpha);
	while( time < TIME) {
		e = new Event(time, OBSERVING);
		el.push_back(*e);
		time += Exponential(alpha);
	}
}

float EventScheduler::Uniform() {
	return (float)rand()/(float)(RAND_MAX+1);
}

/*
 * Exponential
 */
float EventScheduler::Exponential(float lambda) {
	return (float)log(Uniform())/-lambda;
}

/*
 * Poisson:
 */
int EventScheduler::Poisson(float mean) { //Special technique required: Box-Muller method...
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

float EventScheduler::Poisson2(float mean) {
	float l = exp(-mean);
	int k = 0;
	float p = 1.0;
	do {
		p = p * -Uniform();
		++k;
	} while (p > l);
	return k - 1;
}
