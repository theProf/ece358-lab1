/*
 * Event.h
 *
 *  Created on: Mar 15, 2014
 *      Author: gerg
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <cstdlib>

typedef enum {
	ARRIVING = 1, DEPARTING = 2, OBSERVING = 3
} EventType;


class Event {
public:
	float 		time;
	int 		length;
	EventType 	type;
//	Event 		*next;s

	Event();
	Event(float pTime, EventType pType);
	virtual 	~Event();

	void 		toString(void);
};

#endif /* EVENT_H_ */
