#include "Runnable2.h"

#include "shared.h"

#include <EventChains2.h>

#include <fstream>

Runnable2::Runnable2()
{
    job_id = 0;
}

Runnable2::~Runnable2()
{

}

void Runnable2::setName(string &s)
{
    name = s;
}

string Runnable2::getName()
{
    return name;
}

void Runnable2::setLabelsReadListSize(int size)
{
    labelsRead_list.reserve(size);
}

void Runnable2::setLabelsWriteListSize(int size)
{
    labelsWrite_list.reserve(size);
}

void Runnable2::insertReadLabel(int id)
{
    labelsRead_list.push_back(id);
}

void Runnable2::insertWriteLabel(int id)
{
    labelsWrite_list.push_back(id);
}

void Runnable2::setDistribParams(int l, int u, string &prp, int m)
{
    lowerBound = l;
    upperBound = u;
    pRemainPromille = prp;
    mean = m;
}

void Runnable2::setTask(Task2 *t)
{
    task = t;
}

void Runnable2::setPosInTask(int i)
{
    task_i = i;
}

Task2 *Runnable2::getTask()
{
    return task;
}

int Runnable2::getPosInTask()
{
    return task_i;
}

void Runnable2::setWeibull()
{
    wv = std::unique_ptr<MetaSim::WeibullVar>(new MetaSim::WeibullVar(MetaSim::weibullFromAmalthea(lowerBound,
                                                                                                   upperBound,
                                                                                                   mean,
                                                                                                   std::stod(pRemainPromille))));
}

Tick Runnable2::getComputationTime()
{
    return Tick(wv->get(lowerBound));
}


void Runnable2::readLabel(int l, const Tick &activationTime)
{
    Label2 * readLabel = labelList[l];

    for (EventChains2 *C : inChain) {
        C->read(this, readLabel, activationTime);
    }

    /*
    // If the runnable is not in chain, do nothing
    if (!inChain)
        return;

    Label2 * prevLabel = labelList[l];

    // If the label that the runnable reads from is
    // not in a chain, then do nothing
    if (!prevLabel->inChain)
        return;

    printf("%lld: %s <-- %d\n", (long long)SIMUL.getTime(), name.c_str(), l);

    vector< pair<long long int, Tick> > tmp_status;
    if (prevLabel->read(tmp_status) == -1) {
        printf("\tRead empty label, doing nothing!\n");
    } else {
        printf("\tStatus updated!\n");
        _status = tmp_status;

        if (prevLabel->getLastInChain()) {
            printf("\tThis is the last in chain\n");

            Tick t_f = SIMUL.getTime();

            if (_status[0].first != n_first) {

                Tick t_s1;

                if (n_first == -1) {
                    t_s1 = 0;
                } else {
                    Tick FF;

                    t_s1 = _status[0].second;

                    FF = t_f - t_s1;

                    printf("\tFF found: %lld\n", (long long)(FF));

                    _FF.push_back(FF);
                }


                n_first = _status[0].first;
            }

            if (_status[1].first != n_last) {
                if (n_last != -1) {
                    Tick LL;

                    LL = t_fCand - t_r0l;

                    printf("\tLL found: %lld\n", (long long)(LL));

                    _LL.push_back(LL);
                }
                n_last = _status[1].first;
                t_r0l = _status[1].second;
            }

            t_fCand = t_f;
        }
    }
*/
    /*
    // Try to reads the timestamp from the label
    MetaSim::Tick receivedTimestamp;
    if (labelList[l]->read(receivedTimestamp)) {
        // Something wrong happened

        printf("\tEmpty label timestamp\n");
    } else {
        // Timestamp succesfully read

        printf("\tTimestamp updated in runnable\n");

    }
    */
}

void Runnable2::writeLabel(int l)
{
    Label2 * writeLabel = labelList[l];

    for (EventChains2 *C : inChain) {
        C->write(this, writeLabel);
    }

    /*
    // If the runnable is not in chain, do nothing
    if (!inChain)
        return;

    Label2 * nextLabel = labelList[l];

    // If the label that the runnable is writing to
    // is not in a chain, then do nothing
    if (!nextLabel->inChain)
        return;

    printf("%lld: %s --> %d\n", (long long)SIMUL.getTime(), name.c_str(), l);

    if (nextLabel->firstInChain) {
        // The label is the first in chain, then the submitted time
        // must be the runnable's activation time

        printf("\tFistInChain, writing last activation time\n");

        _status = {
            pair<long long int, Tick>(job_id, activationTime),
            pair<long long int, Tick>(job_id, activationTime)
        };

        nextLabel->write(_status);
    } else {
        // The label is not the first one in chain, send its own
        // status to the next label

        if (_status.size() > 0) {
            printf("\tMiddle chain runnable, writing status\n");
            nextLabel->write(_status);
        } else {
            printf("\tMiddle chain runnable, no status to write\n");
            return;
        }
    }

    printf("\tStatus cleared\n");
    _status.clear();
    */
}

void Runnable2::increaseID()
{
    job_id++;
}

long long int Runnable2::getID() const
{
    return job_id;
}

void Runnable2::addChain(EventChains2 *C)
{
    if (find(inChain.begin(), inChain.end(), C) == inChain.end())
        inChain.push_back(C);
}
