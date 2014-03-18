/*
 * EventScheduler.h
 *
 *  Created on: Mar 15, 2014
 *      Author: gerg
 */

#ifndef EVENTSCHEDULER_H_
#define EVENTSCHEDULER_H_

#include "Event.h"
#include "RandomVar.h"
#include <cmath>
#include <stdio.h>
#include <list>

class EventScheduler {
public:
	EventScheduler();
	EventScheduler(double pRo, int pL, int pC);
	EventScheduler(double pRo, int pL, int pC, int pK);
	virtual ~EventScheduler();

	/* Initialization Parameters */
	double 		lambda;
	double		alpha;
	double		Ro;
	int			L;
	int			C;
	int			K;
	/* end init params */

//	EventList	*el;
//	EventList	*arrivals;
//	EventList	*observers;

	std::list<Event*>	*el;

	/* global vars */
	int			Na;
	int			Nd;
	int			No;
	int			Ndr;
	int			En;
	double		Et;
	int			idle;

	/* step functions */
	void		setup(void);
	void		run(void);

	/* helper functions */
	void		toString(void);
	void		sortES(void);

private:
	void		populateArrivals(void);
	void		populateObservers(void);
	void		calc_departures(void);
	void		insert_sort(Event *event);
	Event		*nextEvent(void);
};



#endif /* EVENTSCHEDULER_H_ */
