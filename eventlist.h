#include<vector>
#include"event.h"
using namespace std;

class EventList
{
	private:
		vector<Event*> list;				
		
	public:
		EventList();
		void insert(Event* e);
		Event* top();				// returns the latest event to take place
};
