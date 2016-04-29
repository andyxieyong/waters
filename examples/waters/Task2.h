#pragma once

#include <string>
#include <vector>

#include "Runnable2.h"

using namespace std;

enum Task_Stimuli {periodic, sporadic};
enum Task_Preemption {cooperative, preemptive};

class Task2
{
public:
    Task2();
    ~Task2();

    void setName(string &n);
    string getName();

    void setPriority(int p);
    int getPriority();

    void setPeriod(int p);
    int getPeriod();

    void setStimuli(Task_Stimuli s);
    Task_Stimuli getStimuli();

    void setPreemption(Task_Preemption p);
    Task_Preemption getPreemption();


    void setInterArrivalTime(int min, int max);
    int getMinInterArrivalTime();
    int getMaxInterArrivalTime();


    void setMultipleActivationTaskLimit(int matl);
    int getMultipleActivationTaskLimit();

    void setRunnablesListSize(int size);
    void insertRunnable(Runnable2 *r);

private:

    string name;
    int priority;

    union
    {
        int period;
        int minInterArrivalTime;
    };
    int maxInterArrivalTime;


    int multipleActivationTaskLimit;


    Task_Stimuli stimuli;
    Task_Preemption preemption;


    vector<Runnable2 *> runnables_list;

};
