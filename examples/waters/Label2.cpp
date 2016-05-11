#include "Label2.h"

#include <simul.hpp>

void Label2::init()
{
  isconstant = false;
  lastInChain = false;
  inChain = false;
}

Label2::Label2()
{
  init();
}

Label2::Label2(int id)
{
  init();
  this->id = id;
}

/*
Label2::Label2(int id, bool c)
{
  init();
  this->id = id;
}
*/
Label2::~Label2()
{

}

string Label2::getName()
{
  return string("Label_") + to_string(id);
}

int Label2::getid()
{
  return id;
}

void Label2::setid(int id)
{
  this->id = id;
}

bool Label2::isConstant()
{
  return isconstant;
}

void Label2::setBitSize(int bs)
{
  size_bit = bs;
}

int Label2::getBitSize()
{
  return size_bit;
}

void Label2::setIsConstant(bool ic)
{
  isconstant = ic;
}


bool Label2::getIsConstant()
{
  return isconstant;
}

int Label2::read(vector<pair<long long, Tick> > &status)
{
  if(!inChain)
    return -1;

  printf("\t\tReturning and clearing status\n");

  status = _status;

  if (status.size() == 0)
      return -1;

  _status.clear();

  return 0;
}

int Label2::write(vector< pair<long long int, Tick> > status)
{
  if(!inChain) {
    return -1;
  }

  if (_status.size() == 0) {
      printf("\t\tEmpty label, copying status\n");
      _status = status;
  } else {
      printf("\t\tFull label, updating second element\n");
      if (status[0] != status[1]) {
          printf("\t\tError!");
          exit(1);
      }
      _status[1] = status[0];
  }

  return 0;
}

void Label2::setInChain(bool en)
{
  inChain = en;
}


void Label2::setLastInChain(bool en)
{
  lastInChain = en;
}

bool Label2::getLastInChain()
{
  return lastInChain;
}

void Label2::setFirstInChain(bool en)
{
  firstInChain = en;
}

