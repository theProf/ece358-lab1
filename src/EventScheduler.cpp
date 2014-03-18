/*
 * EventScheduler.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: gerg
 */

#include "EventScheduler.h"

#define TIME 				10000 	// secs

bool comparator(Event *one, Event *two) {
//	if(one->time == two->time && (one->type == DEPARTING && two->type == ARRIVING) || (two->type == DEPARTING && one->type == ARRIVING) ) {
//		int x = 0; // breakpoint
//	}
	return one->time <= two->time;
}

EventScheduler::EventScheduler() {
	this->Ro 	= 0;
	this->lambda = 0;
	this->alpha = this->lambda;
	this->L 	= 0;
	this->C 	= 0;
	this->K 	= -1;
	this->el	= new std::list<Event *>();
	this->Na	= 0;
	this->Nd	= 0;
	this->No	= 0;
	this->Ndr	= 0;
	this->En	= 0;
	this->Et	= 0;
	this->idle	= 0;
}

EventScheduler::EventScheduler(double pRo, int pL, int pC) {
	this->Ro 	= pRo;
	this->lambda = pRo*pC/pL;
	this->alpha = this->lambda;
	this->L 	= pL;
	this->C 	= pC;
	this->K 	= -1;
	this->el	= new std::list<Event*>();
	this->Na	= 0;
	this->Nd	= 0;
	this->No	= 0;
	this->Ndr	= 0;
	this->En	= 0;
	this->Et	= 0;
	this->idle	= 0;
}

EventScheduler::EventScheduler(double pRo, int pL, int pC, int pK) {
	this->Ro 	= pRo;
	this->lambda = pRo*pC/pL;
	this->alpha = this->lambda;
	this->L 	= pL;
	this->C 	= pC;
	this->K 	= pK;
	this->el	= new std::list<Event*>();
	this->Na	= 0;
	this->Nd	= 0;
	this->No	= 0;
	this->Ndr	= 0;
	this->En	= 0;
	this->Et	= 0;
	this->idle	= 0;
}

bool deleteAll(Event *e) {
	delete e;
	return true;
}

EventScheduler::~EventScheduler() {
	this->el->remove_if(deleteAll);
	delete el;
}

void EventScheduler::setup() {
	populateArrivals();
	populateObservers();

	sortES();
	return;
}

void EventScheduler::sortES() {
	el->sort(comparator);
}

Event *EventScheduler::nextEvent() {
	Event *e = el->front();
	el->pop_front();
	return e;
}

void EventScheduler::run() {
	double last_departure = 0;
	Event *cur_event = NULL;
	while(!el->empty()) {
		cur_event = nextEvent();

		switch (cur_event->type) {
			case ARRIVING:
				if(K > 0 && Na - Nd >= K) {
					++Ndr;
					continue;
				}

				double Td;
				Td = (last_departure > cur_event->time
									? last_departure
									: cur_event->time)
								+ ((double)cur_event->length / (double)C);

				if(Td < TIME) {
					insert_sort(new Event(Td, DEPARTING));
					last_departure = Td;
					Et += Td - cur_event->time;
				}

				++Na;

				break;
			case DEPARTING:
				++Nd;

				break;
			case OBSERVING:
				++No;

				idle = Na == Nd ? ++idle : idle;
				if(Na - Nd < 0 ) {
					int x = 0; // breakpoint

				}
				En += Na - Nd;
				break;
			default:
				break;
		}

		delete cur_event;
		cur_event = nextEvent();
	}

	printf("ro: %f\t| lambda: %f\t| E[N]: %f\t| E[T]: %f\t| Pidle: %f\n", this->Ro, this->lambda, (double)En/(double)No, (double)Et/(double)Nd, (double)idle/(double)No);
}

void EventScheduler::populateArrivals() {
	Event *e = NULL;
	double time = 0;
	time += RandomVar::Exponential(lambda);
	while ( time < TIME ) {
		e = new Event(time, ARRIVING);
		e->length = (int)RandomVar::Exponential(1.0 / (double)L);
		el->push_back(e);
		time += RandomVar::Exponential(lambda);
	}

}

void EventScheduler::populateObservers() {
	Event *e = NULL;
	double time = 0;
	time += RandomVar::Exponential(alpha);
	while( time < TIME) {
		e = new Event(time, OBSERVING);
		el->push_back(e);
		time += RandomVar::Exponential(alpha);
	}
}

void EventScheduler::insert_sort(Event *event) {
	for(std::list<Event*>::iterator cur_event = el->begin(); cur_event != el->end(); ++cur_event) {
		if(event->time > (*cur_event)->time) {
			el->insert(cur_event, event);
			return;
		}
		++cur_event;
	}
	el->push_back(event);
}

