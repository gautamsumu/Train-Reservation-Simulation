class Event
{
	private:
		int type;
		int on;
		int time;
		
	public:
		Event(int ty, int o, int t);
		int eventType();				// returns type of event
		int at();					// returns time of event
		int of();					// returns party related to event
};
