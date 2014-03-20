#include"event.h"

Event::Event(int ty, int o, int t)				// ty -> type of event, o -> party related, t -> event time
{
	type=ty;
	on=o;
	time=t;
}

int Event::eventType()						// returns type of event
{
	return type;
}

int Event::at()							// returns time of event
{
	return time;
}

int Event::of()							// returns party related to event
{
	return on;
}
