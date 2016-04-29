#include "builder.h"

#include <randomvar.hpp>

namespace RTSim {

  using namespace std;
  using namespace MetaSim;

  Builder::Builder(const std::vector<Task2 *> cores[],
                   unsigned int cpu_n)
  {
    buildKernels(cores, cpu_n);
  }

  Builder::~Builder()
  {
    while (_kernels.size() > 0) {
      delete _kernels.back();
      _kernels.pop_back();
    }
    while (_tasks_per.size() > 0) {
      delete _tasks_per.back();
      _tasks_per.pop_back();
    }
    while (_tasks_isr.size() > 0) {
      delete _tasks_isr.back();
      _tasks_isr.pop_back();
    }
    while (_schedulers.size() > 0) {
      delete _schedulers.back();
      _schedulers.pop_back();
    }
    while (_traces.size() > 0) {
      delete _traces.back();
      _traces.pop_back();
    }
  }


  int Builder::buildKernels(const std::vector<Task2 *> cores[],
                            unsigned int cpus)
  {
    for (unsigned int c=0; c<cpus; c++) {
      PSTrace * t = new PSTrace("trace_" + to_string(c) + ".pst");
      FPScheduler * s = new FPScheduler();
      RTKernel * k = new RTKernel(s);

      _traces.push_back(t);
      _schedulers.push_back(s);
      _kernels.push_back(k);

      buildTasks(cores[c], c);
    }
  }


  int Builder::buildTasks(const std::vector<Task2 *> &tasks,
                          unsigned int c)
  {
    for (unsigned int i=0; i<tasks.size(); i++) {
      Tick period(tasks.at(i)->getPeriod());
      Task * t;

      if (tasks.at(i)->isPeriodic())
        t = new PeriodicTask(period, period, 0, tasks.at(i)->getName());
      else
        t = new Task(new UniformVar(tasks.at(i)->getMinInterArrivalTime(),
                                    tasks.at(i)->getMaxInterArrivalTime()),
                     period,
                     0,
                     tasks.at(i)->getName());

      t->insertCode(buildRunnables(tasks.at(i)->runnables_list));

      _kernels.at(c)->addTask(*t, to_string(tasks.at(i)->getPriority()));

      _traces.at(c)->attachToTask(t);
    }
  }

  string Builder::buildRunnables(const vector<Runnable2 *> &runnables)
  {
    string instructions;

    for (unsigned int i=0; i<runnables.size(); ++i) {
      runnables.at(i);

      instructions.append("runnable(" + runnables.at(i)->getName() + ");");
    }

    const char * c = instructions.c_str();

    return "---TODO---lock(res);fixed(3);unlock(res);";
  }
}
