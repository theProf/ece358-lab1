/*
 * EventList.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: gerg
 */

#include "EventList.h"

EventList::EventList() {
	head 	= NULL;
	tail 	= NULL;
	length 	= 0;
}

EventList::~EventList() {
	Event *tmp = NULL;
	tail = NULL;
	// while we have nodes in the list: delete them
	while(head != NULL) {
		// tmp will be the node to be deleted
		tmp = head;
		head = head->next;
		// unlink tmp from the list and delete
		tmp->next = NULL;
		delete tmp;
	};
}

Event* EventList::pop(void) {
	/*
	 * Cases:
	 * 	1) empty list
	 * 	2) 1 in list
	 * 	3) 2+ in list
	 */

	Event *out = NULL;

	if(length == 0) {
		return out;
	}

	out = head;
	head = head->next;
	out->next = NULL;

	if(length == 1) {
		tail = NULL;
	}

	--length;
	return out;
}

int EventList::push(Event *event) {
	if(length == 0) {
		tail = event;
	} else {
		event->next = head;
	}

	head = event;
	++length;
	return 0;
}

/*
 * append: add to the end of the list
 */
int EventList::append(Event *event) {
	/*
	 * Cases:
	 * 	1) empty
	 * 	2) 1+
	 */

	if(length == 0) {
		head = event;
	} else {
		tail->next = event;
	}

	tail = event;
	++length;
	return 0;
}

/*
 * insert: insert a node into chronological position
 */
int EventList::insert(Event *event) {
	/*
	 * Cases:
	 * 	1) empty
	 * 	2) 1 node
	 * 		before
	 * 		after
	 * 	3) 2+
	 */

	if(this->length == 0) {
		this->push(event);
		return 0;
	}

	Event *tmp = head;
	Event *prev = NULL;

	while(tmp != NULL && event->time < tmp->time) {
		prev = tmp;
		tmp = tmp->next;
	}

	if(tmp == NULL) {
		this->append(event);
		return 0;
	}

	if(prev == NULL) {
		this->push(event);
		return 0;
	}

	event->next = tmp;
	prev->next = event;
	++length;
	return 0;
}

/*
 * merge: merge sort a secont EventList.
 * 	Returns a new EventList with both
 */
EventList* EventList::merge(EventList *el) {
	if(el == NULL) {
		return NULL;
	}

	EventList *out = new EventList();

	while(this->length > 0 && el->length > 0) {
		// still nodes left
		out->append(this->head->time <= el->head->time
						? this->pop()
						: el->pop()
					);
	}

	// empty out the leftovers of this
	while(this->length > 0) {
		out->append(this->pop());
	}

	// empty out leftovers of el
	while(el->length > 0) {
		out->append(el->pop());
	}

	// delete these two? or let that happen after?
	return out;
}


