#include "Label2.h"

#include <simul.hpp>

void Label2::init()
{
  isconstant = false;
  lastInChain = false;
  inChain = false;
  timestampValid = false;
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

int Label2::read(MetaSim::Tick &ret_timestamp)
{
  if(!inChain)
    return -1;
  //printf("Label_%d read()\n", id);

  if (!timestampValid) {
    //printf("\tERROR: read() - !timestampValid!\n");
    return -1;
  }

  ret_timestamp = timestamp;
  timestampValid = false;

  if (lastInChain)
  {
    printf("%d reaction delay = %d \n", this->getid(), MetaSim::SIMUL.getTime() - timestamp);
  }


  return 0;
}

int Label2::write(MetaSim::Tick predecessor_timestamp)
{
  if(!inChain) {
    return -1;
  }

  //printf("Label_%d write()\n", id);


  /*if (firstInChain)
  {
    timestamp = MetaSim::SIMUL.getTime();
    timestampValid = true;

    printf("\tFist timestamp written\n");

    return 0;
  }
  */

  if (timestampValid) {
    //printf("\tWarning: write() - timestampValid, overwriting!\n");
  }

  timestamp = predecessor_timestamp;
  timestampValid = true;

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

void Label2::setFirstInChain(bool en)
{
  firstInChain = en;
}

