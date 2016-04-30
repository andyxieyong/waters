#include "weibullvar.h"

#include <cmath>

namespace MetaSim {

  double WeibullVar::get()
  {
    double x = UniformVar::get();
    //return 1 - pow(M_El, p);
    return _lambda * pow(-log(x), 1/_k);
  }

  RandomVar *WeibullVar::createInstance(vector<string> &par)
  {
      if (par.size() != 2)
          throw WeibullException("Wrong number of parameters");

      double a = atof(par[0].c_str());
      double b = atof(par[1].c_str());

      return new WeibullVar(a, b);
  }

}

