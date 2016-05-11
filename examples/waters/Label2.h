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


    int read(Tick &ret_timestamp);
    int write(Tick predecessor_timestamp);

    void setInChain(bool en);
    void setLastInChain(bool en);
    void setFirstInChain(bool en);

    vector<Runnable2 *> runnablesRead_list;
    vector<Runnable2 *> runnablesWrite_list;


    bool firstInChain;
    bool timestampValid;
    bool inChain;

private:

    void init();

    int id;
    bool isconstant;
    int size_bit;

    bool lastInChain;

    Tick timestamp;
};
