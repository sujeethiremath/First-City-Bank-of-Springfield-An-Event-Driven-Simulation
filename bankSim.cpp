#include "Event.h"
#include<iomanip>
#include<iostream>
#include<queue>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

vector<string> split( const string& s , char delimiter )
{
  vector<string> tokens;          // vector of tokens
  string token;                   // a single token
  istringstream tokenStream(s);   // an input string stream
        // Tokenize s by grabbing individual tokens
  while( getline( tokenStream , token , delimiter ) )
    tokens.push_back(token);    // add found token

  return tokens;
}

//function to processing arrival events 
void processArrival(Event arrivalEvent , priority_queue<Event,vector<Event>,greater<vector<Event>::value_type>> &eventListPQueue , queue<Event> &bankQueue, bool &tellerAvailable, unsigned currentTime, double &totalDepartTime, double &totalTransactTime, double &arrivalTime )
{
    eventListPQueue.pop();
    Event customer(arrivalEvent);
    cout<<"Processing";
    cout<<setw(10);
    cout<<"arrival";
    cout<<" event at time:";
    cout<<setw(5);
    cout<<customer.getTime();
    cout<<setw(5)<<customer.getDuration()<<endl;
    arrivalTime += customer.getTime();
    
    if(bankQueue.empty() == true &&  tellerAvailable == true)
    {
      unsigned departureTime = currentTime + arrivalEvent.getDuration(); //calculating departure event time
      totalDepartTime += departureTime; //keeping record of total departure time
      totalTransactTime += arrivalEvent.getDuration(); //keeping track of total transaction time
      Event newDepartureEvent(Event::departure, departureTime, 0);  //creating new departure event object with previously calculated departure time
      eventListPQueue.push(newDepartureEvent); //inserting departure event back into eventList priority queue
      tellerAvailable = false;
    }
    else
    bankQueue.push(customer);
}

void processDeparture(Event arrivalEvent , priority_queue<Event,vector<Event>,greater<vector<Event>::value_type>> &eventListPQueue , queue<Event> &bankQueue, bool &tellerAvailable, unsigned currentTime, double &totalDepartTime, double &totalTransactTime, double &arrivalTime )
{

    eventListPQueue.pop();
    
     cout<<"Processing departure event at time:";
     cout<<setw(5);
     cout<<arrivalEvent.getTime()<<endl;
     
    if(bankQueue.empty() == false)
    {
      Event customer(bankQueue.front());
      bankQueue.pop();
      unsigned departureTime = currentTime + customer.getDuration();
      totalDepartTime += departureTime;
      totalTransactTime += customer.getDuration();
      Event newDepartureEvent(Event::departure, departureTime, 0);
      eventListPQueue.push(newDepartureEvent);
    }
    else
    tellerAvailable = true;
}

int main()
{
    string fileName,input;
    char delimiter = ' ';
    vector<string> inputFileNames,listOfTokens;
    ifstream eventFile;
    int eTime,eDuration;
    double totalDepartTime = 0, totalTransactTime = 0, arrivalTime=0;
    priority_queue<Event,vector<Event>,greater<vector<Event>::value_type>> eventListPQueue;
    queue<Event> bankQueue;
    bool tellerAvailable = true;
    int count=0;

    cin>>fileName;
    
    eventFile.open(fileName);
    
    if(eventFile.is_open())
    {
      while(getline(eventFile, input))
      {
        listOfTokens = split( input , delimiter );

        for(unsigned j=0;j<listOfTokens.size();j++)
          {
            if(j%2==0)
            eTime = stoi(listOfTokens[j]); 
            else
            {
              eDuration = stoi(listOfTokens[j]);
              Event E(Event::arrival,eTime,eDuration); //creating event object
              eventListPQueue.push(E); //inserting event object into priority queue which sorted according to eTime
              count++; //number of transactions
            }
          }
      }

      eventFile.close();
  }
  else
    {
      cout<<"Error opening File"<<endl;
    }
    
    cout<<"Simulation Begins"<<endl;
    while(eventListPQueue.empty()==false)
    {
    
      Event newEvent(eventListPQueue.top()); 
      unsigned currentTime = newEvent.getTime();
      
      if(newEvent.getType() == Event::arrival)
      processArrival( newEvent , eventListPQueue , bankQueue , tellerAvailable, currentTime, totalDepartTime, totalTransactTime, arrivalTime);
      else
      processDeparture( newEvent , eventListPQueue , bankQueue , tellerAvailable, currentTime, totalDepartTime, totalTransactTime, arrivalTime );
      
    }
    cout<<"Simulation Ends"<<endl<<endl;
    cout<<"Simulation Statistics"<<endl;
    cout<<setw(8)<<"Number";
    cout<<" of transactions processed:";
    cout<<setw(5)<<count<<endl;
    cout<<setw(17)<<"Average"; 
    cout<<" transaction time:";
    cout << fixed << showpoint;
    cout<<setw(8)<<setprecision(2)<<(totalTransactTime/count)<<endl;
    cout<<setw(24)<<"Average";
    cout<<" wait time:";
    cout << fixed << showpoint;
    cout<<setw(8)<<setprecision(2)<<(totalDepartTime - totalTransactTime - arrivalTime)/count;
    cout<<endl<<endl;
    
    return 0;
    

}