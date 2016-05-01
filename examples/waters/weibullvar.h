#ifndef WEIBULLVAR_H
#define WEIBULLVAR_H

#include <randomvar.hpp>

namespace MetaSim {

  using namespace std;

  class WeibullException: public exception
  {
      string problem;
    public:
      WeibullException(string cl) : problem(cl) {}
      virtual ~WeibullException() throw() {}
      virtual const char* what() const throw()
      {
        return problem.c_str();
      }
  };

  /**
       This class implements a Weibull distribution. */
  class WeibullVar : public UniformVar {
      double _lambda;
      double _k;
    public :
      WeibullVar(double lambda, double k, RandomGen *g = nullptr) :
        UniformVar(0, 1, g),
        _lambda(lambda),
        _k(k)
      {
        if (lambda <= 0 || k <= 0)
          throw WeibullException("lambda and k must be greater than zero");
      }

      virtual double get();
      double get(double min, double max, double weibull_limit);

      static RandomVar *createInstance(vector<string> &par);
      virtual double getMaximum() throw(MaxException)
          {throw MaxException("ExponentialVar");}
      virtual double getMinimum() throw(MaxException)
          {throw MaxException("ExponentialVar");}
  };
}
#endif // WEIBULLVAR_H
