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

    vector<Runnable2 *> runnablesRead_list;
    vector<Runnable2 *> runnablesWrite_list;

    void setMemoryResource(const string &mrs) {
        memory_res = mrs;
    }

    const string &getMemoryResource() {
        return memory_res;
    }

private:
    string memory_res; // GLOBAL
                            // LOCAL_0
                            // ...
                            // LOCAL_N

    void init();

    int id;
    bool isconstant;
    int size_bit;
};
