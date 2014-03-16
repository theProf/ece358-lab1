/*
 * EventList.h
 *
 *  Created on: Mar 15, 2014
 *      Author: gerg
 */

#ifndef EVENTLIST_H_
#define EVENTLIST_H_

#include "Event.h"
#include <cstdlib>

class EventList {
public:
	EventList();
	virtual	~EventList();

	int			length;
	Event		*head;
	Event		*tail;

	int			push(Event *event);
	Event*		pop(void);
	int			insert(Event *event);
	int			append(Event *event);
	EventList*	merge(EventList *el);

	void		toString(void);

};


#endif /* EVENTLIST_H_ */
