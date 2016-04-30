#pragma once

#include <string>
#include <vector>

#include "Runnable2.h"
#include "EventChains2_elem.h"


using namespace std;

class EventChains2
{
public:
    EventChains2();
    ~EventChains2();


    Runnable2 *runnable_stimulus;
    Runnable2 *runnable_response;

    string name;

    vector<EventChains2_elem *> eventChains_elems;


private:

};
