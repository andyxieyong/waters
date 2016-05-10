#include "Runnable2.h"

#include "shared.h"

Runnable2::Runnable2()
{
  timestampValid = false;
  inChain = false;
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

int Runnable2::getComputationTime()
{
  return wv->get(lowerBound);
}


void Runnable2::readLabel(int l)
{
  // If the runnable is not in chain, do nothing
  if (!inChain)
    return;

  // If the label that the runnable reads from is
  // not in a chain, then do nothing
  if (!labelList[l]->inChain)
    return;

  printf("%d: %s <-- %d\n", MetaSim::SIMUL.getTime(), name.c_str(), l);

  // Try to reads the timestamp from the label
  MetaSim::Tick receivedTimestamp;
  if (labelList[l]->read(receivedTimestamp)) {
    // Something wrong happened

    printf("\tEmpty label timestamp\n");
  } else {
    // Timestamp succesfully read

    printf("\tTimestamp updated in runnable\n");

    timestamp = receivedTimestamp;
    timestampValid = true;
  }
}

void Runnable2::writeLabel(int l)
{
  // If the runnable is not in chain, do nothing
  if (!inChain)
    return;

  // If the label that the runnable is writing to
  // is not in a chain, then do nothing
  if (!labelList[l]->inChain)
    return;

  printf("%d: %s --> %d\n", MetaSim::SIMUL.getTime(), name.c_str(), l);

  // Write the label timestamp only if the predecessor's timestamp is
  // valid, otherwise write the current simulation time
  if (timestampValid) {

    printf("\tWriting own predecessor timestamp\n");

    labelList[l]->write(timestamp);
  } else {

    if (labelList[l]->firstInChain) {
      printf("\tWriting first in chain simulation timestamp\n");

      labelList[l]->write(MetaSim::SIMUL.getTime());
    }
  }

  //timestampValid = false;
}

void Runnable2::setInChain(bool en)
{
  inChain = en;
}
