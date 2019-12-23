#include "Event.h"

using namespace std;

// Creates an undefined event
  Event :: Event( )
  {
    eType = undefined;
    eTime = 0;
    eDuration = 0;
  }
  
  // Creates an event of a given type, occurance time, and duration
  Event :: Event( eventType type , unsigned time , unsigned duration )
  {
      eType = type;
      eTime = time;
      eDuration = duration;
  }
  
  // Copy constructor
  Event :: Event( const Event& otherEvent )
  {
      eType = otherEvent.eType;
      eTime = otherEvent.eTime;
      eDuration = otherEvent.eDuration;
  }
  
  // Determines the type of the event
  Event::eventType Event :: getType() const
  {
      return  eType; 
  }
  
  // Determines the time of the event
  unsigned Event :: getTime() const
  {
      return eTime;
  }
  
  // Determines the duration of the (arrival) event
  unsigned Event :: getDuration() const
  {
      return eDuration;
  }
  
  // Events are ordered by their event time (occurance)
  bool operator<( const Event& lhs , const Event& rhs )
  {
      return (lhs.eTime<rhs.eTime);
  }
  
  bool operator>( const Event& lhs , const Event& rhs )
  {
      return (lhs.eTime > rhs.eTime); 
  }
  
  
  