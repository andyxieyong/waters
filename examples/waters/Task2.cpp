#include "Task2.h"

using namespace std;

Task2::Task2()
{

}

Task2::~Task2()
{

}

void Task2::setName(string &n)
{
    name = n;
}

string Task2::getName()
{
    return name;
}

void Task2::setPriority(int p)
{
    priority = p;
}

int Task2::getPriority()
{
    return priority;
}

void Task2::setPeriod(int p)
{
    period = p;
    printf("Task2->setPeriod = %dus\n", p);
}

int Task2::getPeriod()
{
    return period;
}

void Task2::setStimuli(Task_Stimuli s)
{
    stimuli = s;
}

Task_Stimuli Task2::getStimuli()
{
    return stimuli;
}

void Task2::setPreemption(Task_Preemption p)
{
    preemption = p;
}

Task_Preemption Task2::getPreemption()
{
    return preemption;
}

void Task2::setInterArrivalTime(int min, int max)
{
    minInterArrivalTime = min;
    maxInterArrivalTime = max;

    printf("Task2->setInterArrivaltime min=%dus max=%dus\n", min, max);
}

int Task2::getMinInterArrivalTime()
{
    return minInterArrivalTime;
}

int Task2::getMaxInterArrivalTime()
{
    return maxInterArrivalTime;
}

void Task2::setMultipleActivationTaskLimit(int matl)
{
    multipleActivationTaskLimit = matl;
    printf("Task2->setMultipleActivationTaskLimit = %d\n", matl);
}

int Task2::getMultipleActivationTaskLimit()
{
    return multipleActivationTaskLimit;
}

void Task2::setRunnablesListSize(int size)
{
    runnables_list.reserve(size);
}

void Task2::insertRunnable(Runnable2 *r)
{
    runnables_list.push_back(r);
}

