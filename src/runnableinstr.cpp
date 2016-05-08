/***************************************************************************
    begin                : Thu Apr 24 15:54:58 CEST 2003
    copyright            : (C) 2003 by Giuseppe Lipari
    email                : lipari@sssup.it
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

#include <factory.hpp>
#include <simul.hpp>
#include <strtoken.hpp>

#include <cpu.hpp>
#include <runnableinstr.hpp>
#include <task.hpp>


namespace RTSim {

  using namespace MetaSim;
  using namespace std;
  using namespace parse_util;

  RunnableInstr::RunnableInstr(Task *f, const string &n) :
    Instr(f, n), cost_generator(new WeibullVar(1, 1.5)), _endEvt(this)
  {
    DBGTAG(_INSTR_DBG_LEV,"RunnableInstr");
  }

  Instr *RunnableInstr::createInstance(vector<string> &par)
  {
    return new RunnableInstr(dynamic_cast<Task *>(Entity::_find(par[1])), par[0]);
  }

  void RunnableInstr::newRun()
  {
    actTime = lastTime = 0;
    flag = true;
    execdTime = 0;
    executing = false;
  }

  void RunnableInstr::endRun()
  {
    _endEvt.drop();
  }

  Tick RunnableInstr::getExecTime() const
  {
    Tick t = SIMUL.getTime();
    if (executing) return (execdTime + t - lastTime);
    else return execdTime;
  }

  Tick RunnableInstr::getDuration() const
  {
    return currentCost;
  }

  Tick RunnableInstr::getWCET() const throw(RandomVar::MaxException)
  {
    return maximumcost;
  }

  void RunnableInstr::schedule() throw (InstrExc)
  {
    DBGENTER(_INSTR_DBG_LEV);

    Tick t = SIMUL.getTime();
    lastTime = t;
    executing = true;

    if (flag) {

      DBGPRINT_3("Initializing RunnableInstr ",
                 getName(),
                 " at first schedule.");
      DBGPRINT_2("Time executed during the prev. instance: ",
                 execdTime);

      execdTime = 0;
      actTime = 0;
      flag = false;

      Runnable2 *runnable = runnableName_runnableP[this->getName()];

      /*
      currentCost = Tick(dynamic_cast<WeibullVar *>(cost_generator.get())->get(lb, ub, 2.5));
      if (currentCost > ub || currentCost < lb)
        throw InstrExc("Wrong instruction cost chosen!", "RunnableInstr::schedule()");
        */
      currentCost = Tick(runnable->getComputationTime());// runnable->wv.get();

      //for (auto labels : runnable->labelsRead_list) {
      //   TODO: settare nel task i timestamp di lettura del runnable
      //}

      DBGPRINT_2("Time to execute for this instance: ",
                 currentCost);
    }

    CPU *p = _father->getCPU();
    if (!dynamic_cast<CPU *>(p))
      throw InstrExc("No CPU!", "ExeInstr::schedule()");

    double currentSpeed = p->getSpeed();

    Tick tmp = 0;
    if (((double)currentCost) > actTime)
      tmp = (Tick) ceil( ((double)currentCost - actTime)/currentSpeed);

    _endEvt.post(t + tmp);

    DBGPRINT("End of RunnableInstr::schedule() ");

  }

  void RunnableInstr::deschedule()
  {
    Tick t = SIMUL.getTime();

    DBGENTER(_INSTR_DBG_LEV);
    DBGPRINT("Descheduling RunnableInstr named: " << getName());

    _endEvt.drop();

    if (executing) {
      CPU *p = _father->getOldCPU();
      if (!dynamic_cast<CPU *>(p))
        throw InstrExc("No CPU!",
                       "ExeInstr::deschedule()");

      double currentSpeed = p->getSpeed();

      actTime += ((double)(t - lastTime))*currentSpeed;// number of cycles
      execdTime += (t - lastTime);// number of ticks
      lastTime = t;
    }
    executing = false;


  }

  void RunnableInstr::setTrace(Trace *t) {
    _endEvt.addTrace(t);
  }


  void RunnableInstr::onEnd()
  {
    DBGENTER(_INSTR_DBG_LEV);
    DBGPRINT("Ending RunnableInstr named: " << getName());

    Tick t = SIMUL.getTime();
    execdTime += t - lastTime;
    flag = true;
    executing = false;
    lastTime = t;
    actTime = 0;
    _endEvt.drop();

    DBGPRINT("internal data set... now calling the _father->onInstrEnd()");


    Runnable2 *runnable = runnableName_runnableP[this->getName()];

    //for (auto labels : runnable->labelsWrite_list) {
      // TODO: settare nelle label il timestamp di scrittura
    //}

    _father->onInstrEnd();
  }


  void RunnableInstr::reset()
  {
    DBGENTER(_INSTR_DBG_LEV);

    actTime = lastTime = 0;
    flag = true;
    execdTime = 0;
    _endEvt.drop();

    DBGPRINT("internal data reset...");


  }


  void RunnableInstr::refreshExec(double oldSpeed, double newSpeed){
    Tick t = SIMUL.getTime();
    _endEvt.drop();
    actTime += ((double)(t - lastTime))*oldSpeed;
    execdTime += (t - lastTime);
    lastTime = t;

    Tick tmp = 0;
    if (((double)currentCost) > actTime)
      tmp = (Tick) ceil ((((double) currentCost) - actTime)/newSpeed);

    _endEvt.post(t + tmp);
  }

}
