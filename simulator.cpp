#include<iostream>
#include<ctime>
#include<cstdlib>
#include"simulator.h"
using namespace std;

#define DEPARTURE 0
#define BOOKING 1
#define CANCELLATION 2

Simulator::Simulator()
{
	clock=0;
	cout<<"Number Of trains = ";					// constructor takes number of trains to be simulated
	cin>>totalTrains;
	trainLeft=totalTrains;
}		

int Simulator::variableTime(int seed)
{
	return 1+rand()%(int)seed;					// generates random time in range of 1 to 'seed'
}

void Simulator::start()
{
	int stat[totalTrains];						// variable for keeping status for train
	srand(time(NULL));						
	for(int i=0;i<totalTrains;i++)				// loop creating given number of train objects
	{
		stat[i]=0;							// status is '0' initially i.e, available for booking
		Train* tr=new Train();
		T.push_back(tr);
		Event* departure=new Event(DEPARTURE,i,tr->departAt());		// departure event of the train pushed in eventlist
		E.insert(departure);
		Event* arrival=new Event(BOOKING,i,variableTime(tr->bookTime(0)));	// first customer arrival event is created
		E.insert(arrival);	
		Event* cancellation=new Event(CANCELLATION,i,variableTime(tr->cancelTime(0)));	// first cancellation event is created
		E.insert(cancellation);
	}
	int trace=0;
	cout<<"If you want to set a trace, press 1 : ";				// trace to see the status of train on each event
	cin>>trace;
	int day=-1;
	while(trainLeft>0)								// loop runs until all trains are departed
	{
		Event* e=E.top();
		int c,l;
		int trainNum=e->of();
		clock=e->at();
		if(day<clock/1440)
		{
			day=clock/1440;
			cout<<endl<<endl<<"Day "<<day<<endl<<endl;		// prints day of observetion
		}
		switch(e->eventType())
		{
		
		case BOOKING:								// booking event
			if(T[trainNum]->departAt()-clock<120)			// if only 2 hours are left for departure booking stops
				stat[trainNum]=2;
			if(stat[trainNum]!=0) continue;				
			cout<<"clock : "<<(clock%1440)/60<<"h "<<(clock%1440)%60<<"m "<<"\t Train : "<<T[trainNum]->number()<<"\t";
			c=rand()%10;							// generates type of customer on scale of 1-10
			T[trainNum]->book(c);
			l=variableTime(T[trainNum]->bookTime(clock));
			E.insert(new Event(BOOKING,trainNum,clock+l));		// inserts next booking of train in eventlist
			if(trace==1) T[trainNum]->status();
			cout<<endl;
			break;
			
		case CANCELLATION:							// cancellation event
			if(stat[trainNum]==1) continue;
			cout<<"clock : "<<(clock%1440)/60<<"h "<<(clock%1440)%60<<"m "<<"\t Train : "<<T[trainNum]->number()<<"\t";
			c=rand()%10;
			T[trainNum]->cancel(c);
			l=variableTime(T[trainNum]->cancelTime(clock));
			E.insert(new Event(CANCELLATION,trainNum,clock+l));	// inserts next cancellation event in eventlist
			if(trace==1) T[trainNum]->status();
			cout<<endl;
			break;
		
		case DEPARTURE:								// departure event
			stat[trainNum]=1;							// the train status after departure becomes '1'
			cout<<endl;
			cout<<"clock : "<<(clock%1440)/60<<"h "<<(clock%1440)%60<<"m "<<"\t Train : "<<T[trainNum]->number()<<"\t";
			T[trainNum]->status();
			cout<<endl<<endl;
			trainLeft--;
		}
	}
	
	cout<<endl<<endl;
	for(int i=0;i<totalTrains;i++)				// final output
	{
		T[i]->financial();					// financial of each train 
		T[i]->status();						// status of train when departed
		cout<<endl<<endl;
	}
}
