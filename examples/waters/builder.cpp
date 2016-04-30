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
    while (_res_managers.size() > 0) {
      delete _res_managers.back();
      _res_managers.pop_back();
    }
    while (_CPUs.size() > 0) {
      delete _CPUs.back();
      _CPUs.pop_back();
    }
  }


  int Builder::buildKernels(const std::vector<Task2 *> cores[],
                            unsigned int cpus)
  {
    for (unsigned int c=0; c<cpus; c++) {
        PSTrace * t = new PSTrace("trace_" + to_string(c) + ".pst");
        FPScheduler * s = new FPScheduler();
        CPU * cpu = new CPU("CPU" + to_string(c));
        RTKernel * k = new RTKernel(s, "Kernel" + to_string(c), cpu);
        FCFSResManager * rm = new FCFSResManager("preemptResMng_" + to_string(c));

        rm->addResource("preemptRes" + to_string(c));
        k->setResManager(rm);

        _CPUs.push_back(cpu);
        _res_managers.push_back(rm);
        _traces.push_back(t);
        _schedulers.push_back(s);
        _kernels.push_back(k);

        buildTasks(cores[c], c);
    }

    return 0;
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
        t = new Task(new DeltaVar((tasks.at(i)->getMinInterArrivalTime() + tasks.at(i)->getMaxInterArrivalTime()) / 2), //TODO
                     period,
                     0,
                     tasks.at(i)->getName());

      t->insertCode(buildRunnables(tasks.at(i)->runnables_list, c));

      unsigned int priority = tasks.at(i)->getPriority();

      _kernels.at(c)->addTask(*t, to_string(priority));

      _traces.at(c)->attachToTask(t);
    }

    return 0;
  }

  string Builder::buildRunnables(const vector<Runnable2 *> &runnables, unsigned int c)
  {
    string instructions;

    for (unsigned int i=0; i<runnables.size(); ++i) {
      runnables.at(i);

      //instructions.append("fixed(10);");
      instructions.append("wait(preemptRes" + to_string(c) + ");fixed(10);signal(preemptRes" + to_string(c) + ");");
    }

    const char * s = instructions.c_str();

    return instructions;
  }
}
