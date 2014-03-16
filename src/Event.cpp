/*
 * Event.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: gerg
 */

#include "Event.h"

Event::Event() {
	this->time = 0;
	this->length = 0;
	this->type = ARRIVING;
//	this->next = NULL;
}

Event::Event(float pTime, EventType pType) {
	this->time = pTime;
	this->type = pType;
	this->length = 0;
//	this->next = NULL;
}

Event::~Event() {
//	this->next = NULL;
}

