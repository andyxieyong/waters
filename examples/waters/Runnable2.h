#pragma once

#include <string>
#include <vector>
#include <memory>

#include <metasim.hpp>

#include "Label2.h"
#include "weibullvar.h"

using namespace MetaSim;
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

    void setInChain(bool en);

    void readLabel(int l);
    void writeLabel(int l);

    Tick getComputationTime();

    vector<int> labelsRead_list;
    vector<int> labelsWrite_list;

private:
    string name;

    bool inChain;

    Tick lowerBound;
    Tick upperBound;

    std::unique_ptr<MetaSim::WeibullVar> wv;

    //distribution params
    string pRemainPromille;
    Tick mean;

    Task2 *task;
    int task_i;

    bool timestampValid;
    MetaSim::Tick timestamp;

};



