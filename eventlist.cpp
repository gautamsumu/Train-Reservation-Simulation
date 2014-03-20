#include"eventlist.h"

EventList::EventList()
{}

void EventList::insert(Event* e)
{
	if(list.empty())								// if list is empty inserts directly
		list.push_back(e);
	else
	{										// else
		int itr1,itr2;
		for(itr1=0,itr2=list.size()-1;itr2-itr1>0;)			// does binary search to find the position to insert the event
		{
			int i=(itr1+itr2)/2;
			if(e->at()>list[i]->at())
				itr1=i+1;
			else
				itr2=(itr1+itr2)/2;
		}
		if(e->at()>list[itr1]->at())
			list.insert(list.begin()+itr1+1,e);
		else
			list.insert(list.begin()+itr1,e);
	}
}

Event* EventList::top()									// returns the latest event to take place
{
	Event* temp=list.front();
	list.erase(list.begin());
	return temp;
}
