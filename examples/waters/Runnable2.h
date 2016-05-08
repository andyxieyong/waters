#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Label2.h"
#include "weibullvar.h"

using namespace std;


enum Label_Access {read, write};

class Task2;

class Runnable2
{
public:
    Runnable2();
    ~Runnable2();

    void setName(string &s);
    string getName();

    void setLabelsReadListSize(int size);
    void setLabelsWriteListSize(int size);

    void insertReadLabel(int id);
    void insertWriteLabel(int id);

    void setWeibull();

    void setDistribParams(int l, int u, string &prp, int m);

    void setTask(Task2 *t);
    void setPosInTask(int i);
    Task2 *getTask();
    int getPosInTask();

    int getComputationTime()
    {
      return wv->get(lowerBound);
    }

    vector<int> labelsRead_list;
    vector<int> labelsWrite_list;

private:
    string name;

    int lowerBound;
    int upperBound;

    std::unique_ptr<MetaSim::WeibullVar> wv;

    //distribution params
    string pRemainPromille;
    int mean;

    Task2 *task;
    int task_i;



};



