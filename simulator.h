#include"eventlist.h"
#include"train.h"

class Simulator
{
	private:
		int clock;
		int totalTrains;
		int trainLeft;
		EventList E;
		vector<Train*> T;
	
	public:
		Simulator();
		int variableTime(int seed);
		void start();
};
