#include "EventChains2_elem.h"

using namespace std;

EventChains2_elem::EventChains2_elem()
{

}

EventChains2_elem::~EventChains2_elem()
{

}

int EventChains2_elem::pushRunnable(const vector< pair<long long int, Tick> > &status)
{
    for (auto s : status)
        _statusStimulusRunnable.push_back(s);

    return 0;
}

int EventChains2_elem::pushLastRunnable(const vector< pair<long long int, Tick> > &status)
{
    for (auto s : status)
        _statusResponseRunnable.push_back(s);

    return 0;
}

int EventChains2_elem::pullLabel(vector< pair<long long int, Tick> > &status)
{
    if (_statusLabel.size() == 0)
        return -1;

    status.clear();
    status.push_back(_statusLabel.front());
    status.push_back(_statusLabel.back());

    _statusLabel.clear();

    return 0;
}


int EventChains2_elem::pushLabel(const vector< pair<long long int, Tick> > &status)
{
    _statusLabel = status;

    return 0;
}


int EventChains2_elem::pullRunnable(vector< pair<long long int, Tick> > &status)
{
    if (_statusStimulusRunnable.size() == 0)
        return -1;

    status.clear();
    status.push_back(_statusStimulusRunnable.front());
    status.push_back(_statusStimulusRunnable.back());

    _statusStimulusRunnable.clear();

    return 0;
}

int EventChains2_elem::pullLastRunnable(vector< pair<long long int, Tick> > &status)
{
    if (_statusResponseRunnable.size() == 0)
        return -1;

    status.clear();
    status.push_back(_statusResponseRunnable.front());
    status.push_back(_statusResponseRunnable.back());

    _statusResponseRunnable.clear();

    return 0;
}
