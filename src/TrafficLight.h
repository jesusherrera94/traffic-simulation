#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"
#include "TrafficLightPhase.h"

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue
{
public:
    MessageQueue();
    T receive();
    void send(T &&msg);

private:
    std::deque<T> _queue;
    std::condition_variable _condition;
    std::mutex _mutex;
    
};

class TrafficLight : public TrafficObject
{
public:
    TrafficLight();
    ~TrafficLight();
    TrafficLightPhase getCurrentPhase();
    void waitForGreen();
    void simulate();

private:
    void cycleThroughPhases();

    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.

    std::condition_variable _condition;
    std::mutex _mutex;
    TrafficLightPhase _currentPhase;
};

#endif