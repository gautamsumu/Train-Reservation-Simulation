#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"train.h"
using namespace std;

Train::Train()
{
	cout<<"Train Number : ";									// getting informations about train
	cin>>trainNumber;
	cout<<"Departure Day (today->'0' , tomorrow->'1' and so on): ";
	int day;
	cin>>day;
	cout<<"Departure Time (hhmm): ";
	int t[2];
	scanf("%2d%2d", &t[0] , &t[1]);
	departureTime=day*1440+t[0]*60+t[1];
	cout<<"AC Berths = ";
	cin>>ACBerths;
	cout<<"AC Fare = ";
	cin>>ACfare;
	cout<<"SL Berths = ";
	cin>>SLBerths;
	cout<<"Sl Fare = ";
	cin>>SLfare;
	cout<<"Customer Preference (on scale of 1-10) : ";
	int q;
	cin>>q;
	avgBookTimeRange=q*40;										// setting inter booking time according to preference for train
	avgCancelTimeRange=(11-q)*500;								// setting inter cancellation time according to preference for train
	cout<<"Cost of running Train : ";
	cin>>runningCost;
	ACfilled=0;
	SLfilled=0;
	ACwaiting=0;
	SLwaiting=0;
	cancelled=0;
	customerLost=0;
	revenue=0;
}

void Train::book(int c)									// booking of ticket
{
	if(c==0)										// first type of person who will always buy only AC tickets
	{
		revenue+=ACfare;
		if(ACfilled<ACBerths)
		{
			ACfilled++;
			cout<<" AC Confirmed ";
		}
		else
		{
			if(ACwaiting<ACBerths)						// if waiting has increased to the original number of births, no more booking
			{
				if(rand()%2==0)
				{
					ACwaiting++;					// if there is waiting, a person can decide whether to book or not
					cout<<" AC Waiting ";
				}
				else
				{
					cout<<" Customer Lost ";
					customerLost++;
				}
			}
			else
			{
				revenue-=ACfare;
				customerLost++;
				cout<<" REGRET ";
			}
		}
	}
	else if(c==1 || c==2)								// second type of person who will prefer AC over Sleeper
	{
		if(ACfilled<ACBerths)
		{
			ACfilled++;
			cout<<" AC Confirmed ";
			revenue+=ACfare;
		}
		else
		{
			revenue+=SLfare;
			if(SLfilled<SLBerths)
			{
				SLfilled++;
				cout<<" SL Confirmed ";
			}
			else
			{
				if(SLwaiting<SLBerths)					// if waiting has increased to the original number of births, no more booking
				{
					if(rand()%2==0)					// if there is waiting, a person can decide whether to book or not
					{
						SLwaiting++;
						cout<<" SL Waiting ";
					}
					else
					{
						cout<<" Customer Lost ";
						customerLost++;
					}
				}
				else
				{
					revenue-=SLfare;
					customerLost++;
					cout<<" REGRET ";
				}
			}
		}
	}
	else												// third kind of person always buy Sleeper tickets
	{
		revenue+=SLfare;
		if(SLfilled<SLBerths)
		{
			SLfilled++;
			cout<<" SL Confirmed ";
		}
		else
		{
			if(SLwaiting<SLBerths)							// if waiting has increased to the original number of births, no more booking
			{
				if(rand()%2==0)							// if there is waiting, a person can decide whether to book or not
				{
					SLwaiting++;
					cout<<" SL Waiting ";
				}
				else
				{
					cout<<" Customer Lost ";
					customerLost++;
				}
			}
			else
			{
				revenue-=SLfare;							// if number of waiting exceeds a limit REGRET is being shown
				customerLost++;
				cout<<" REGRET ";
			}
		}
	}
}

void Train::cancel(int c)								// cancellation of tickets
{
	cancelled++;
	if(c==0)										// for each type of person, different cancellation
	{
		revenue-=ACfare;
		if(ACwaiting==0)
			ACfilled--;
		else
			ACwaiting--;
		cout<<" AC Cancelled ";
	}
	else if(c==1 || c==2)
	{
		if(ACfilled<ACBerths)
		{
			ACfilled--;
			cout<<" AC Cancelled ";
			revenue-=ACfare;
		}
		else
		{
			revenue-=SLfare;
			if(SLwaiting==0)
				SLfilled--;
			else
				SLwaiting--;
			cout<<" SL Cancelled ";
		}
	}
	else
	{
		revenue-=SLfare;
		if(SLwaiting==0)
			SLfilled--;
		else
			SLwaiting--;
		cout<<" SL Cancelled ";
	}
}
int Train::departAt()								// returns departure time of train
{
	return departureTime;
}

void Train::status()								// returns current booking status of train
{
	cout<<" AC filled : "<<ACfilled<<"\t AC Waiting : "<<ACwaiting<<"\t SL filled : "<<SLfilled<<"\t SL waiting : "<<SLwaiting<<"\t Cancelled : "<<cancelled;
}

void Train::financial()								// returns financial status of train
{
	cout<<" Train : "<<trainNumber<<"\t Running Cost = "<<runningCost<<"\t Revenue = "<<revenue<<"\t Profit = "<<revenue-runningCost<<endl;
}

int Train::number()								// returns train number
{
	return trainNumber;
}

int Train::bookTime(int t)							// returns inter booking time using linear dependence with the departure time
{
	int bookTimeRange=avgBookTimeRange-(int)(((avgBookTimeRange-1)*t)/departureTime);
	return bookTimeRange;
}

int Train::cancelTime(int t)							// returns inter cancellation time using linear dependence with the departure time
{
	int cancelTimeRange=avgCancelTimeRange-(int)(((avgCancelTimeRange-3)*t)/departureTime);
	return cancelTimeRange;
}
