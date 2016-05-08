#include "Runnable2.h"


Runnable2::Runnable2()
{

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
