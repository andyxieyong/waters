#pragma once

#include <string>
#include <vector>

#include "Label2.h"

using namespace std;


enum Label_Access {read, write};



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


    void setDistribParams(int l, int u, string &prp, int m);

private:
    string name;
    vector<int> labelsRead_list;
    vector<int> labelsWrite_list;


    //distribution params
    int lowerBound;
    int upperBound;
    string pRemainPromille;
    int mean;



};

