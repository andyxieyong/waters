#pragma once

#include <string>

using namespace std;

class Label2
{

public:

    Label2();
    Label2(int id);
    Label2(int id, bool c);

    ~Label2();

    string getName();
    int getid();
    void setid(int id);
    bool isConstant();

private:
    int id;
    bool isconstant;


};
