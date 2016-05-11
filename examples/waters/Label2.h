#pragma once

#include <string>
#include <vector>

#include <metasim.hpp>

using namespace MetaSim;
using namespace std;

class Runnable2;

class Label2
{
public:

    Label2();
    Label2(int id);
    //Label2(int id, bool c);


    ~Label2();

    string getName();
    int getid();
    void setid(int id);
    bool isConstant();

    void setBitSize(int bs);
    int getBitSize();

    void setIsConstant(bool ic);
    bool getIsConstant();


    int read(vector< pair<long long int, Tick> > &status);
    int write(vector<pair<long long, Tick> > status);

    void setInChain(bool en);
    void setLastInChain(bool en);
    bool getLastInChain();
    void setFirstInChain(bool en);

    vector<Runnable2 *> runnablesRead_list;
    vector<Runnable2 *> runnablesWrite_list;


    bool firstInChain;
    bool inChain;

private:

    void init();

    int id;
    bool isconstant;
    int size_bit;

    bool lastInChain;

    vector< pair<long long int, Tick> > _status;
};
