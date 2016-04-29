#include "builder.h"


namespace RTSim {

  using namespace std;
  using namespace MetaSim;

  Builder::Builder(const std::vector<Task2 *> &tasks,
                   const std::vector<Runnable2 *> &runnables,
                   const std::vector<Label2 *> &labels)
  {
    buildKernels();
    buildTasks(/*tasks, labels*/);
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


  int Builder::buildKernels()
  {
    for (unsigned int c=0; c<4; c++) {
      PSTrace * t = new PSTrace("trace_" + to_string(c) + ".txt");
      FPScheduler * s = new FPScheduler();
      RTKernel * k = new RTKernel(s);

      _traces.push_back(t);
      _schedulers.push_back(s);
      _kernels.push_back(k);
    }
  }


  int Builder::buildTasks()
  {
    for (unsigned int c=0; c<4; c++) {
      for (unsigned int i=0; i<3; i++) {
        Tick period(int(100 + 10 * i));
        PeriodicTask * t = new PeriodicTask(period, period, 0, "Task_" + to_string(c) + to_string(i));

        t->insertCode("fixed(10);");

        _kernels.at(c)->addTask(*t, to_string(i));

        _traces.at(c)->attachToTask(t);
      }
    }
  }
}
