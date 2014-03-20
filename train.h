class Train{
	private:
		int trainNumber;
		int ACBerths;
		int SLBerths;
		int departureTime;
		int avgBookTimeRange;
		int avgCancelTimeRange;
		int runningCost;
		int ACfare;
		int SLfare;
		int revenue;
		int ACfilled;
		int SLfilled;
		int ACwaiting;
		int SLwaiting;
		int customerLost;
		int cancelled;
	
	public:
		Train();
		void book(int c);
		void cancel(int c);
		int departAt();
		void status();
		void financial();
		int number();
		int bookTime(int t);
		int cancelTime(int t);
};
