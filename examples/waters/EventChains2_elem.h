#pragma once

#include <string>
#include <vector>

#include "Runnable2.h"
#include "Label2.h"

using namespace std;


class EventChains2_elem
{
public:
    EventChains2_elem();
    ~EventChains2_elem();


    Runnable2 *runnable_stimulus;
    Runnable2 *runnable_response;

    Label2 *label_wr;


private:

};
