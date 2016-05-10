#include "weibullvar.h"

#include <cmath>
#include <fstream>

#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>

namespace MetaSim {

  double WeibullVar::get()
  {
    double x = UniformVar::get();
    //return 1 - pow(M_El, p);
    return _lambda * pow(-log(x), 1/_k);
  }

  double WeibullVar::get(double min)
  {
    if (min < 0)
      throw WeibullException("Min cannot be smaller than zero");

    return get() + min;
  }

  RandomVar *WeibullVar::createInstance(vector<string> &par)
  {
    if (par.size() != 2)
      throw WeibullException("Wrong number of parameters");

    double a = atof(par[0].c_str());
    double b = atof(par[1].c_str());

    return new WeibullVar(a, b);
  }


  struct weibull_params_t {
      long double x;
      long double logP;
      long double eta;
  };


  long double weibullLambda(long double x, long double logP, long double k)
  {
    return x / pow(-logP, 1/k);
  }

  double fn1(double k, void * params)
  {
    weibull_params_t *p = (weibull_params_t *)params;
    long double x = p->x;
    long double logP = p->logP;
    long double eta = p->eta;

    long double gammaK = gsl_sf_gamma(1 + 1 / k);
    long double l = weibullLambda(x, logP, k);
    return fabs(l * gammaK - eta);
  }


  WeibullVar weibullFromAmalthea(double min, double max, double mean, double pRemainPromille)
  {
    long double x = max - min;
    long double eta = mean - min;

    long double logP = log(pRemainPromille / 1000);


    weibull_params_t p;
    p.eta = eta;
    p.x = x;
    p.logP = logP;

    // The GSL minimization routines only work in the case of
    // f(lowerBound)>f(x)<f(upperBound), so, a fast search of
    // the bounds must be performed

    long double lowerBound = 0.05;
    long double upperBound = 50;
    long double m = lowerBound;
    long double f_lowerBound, f_upperBound, f_m;

    f_lowerBound = fn1(lowerBound, (void *)&p);
    f_upperBound = fn1(upperBound, (void *)&p);

    do {
      f_m = fn1(m, (void *)&p);
      m += 0.02;
    } while(f_m >= f_lowerBound || f_m >= f_upperBound);



    int status;
    int iter = 0, max_iter = 10000;
    const gsl_min_fminimizer_type *T;
    gsl_min_fminimizer *s;
    double k = m;
    double a = lowerBound, b = upperBound;
    gsl_function F;

    F.function = &fn1;
    F.params = &p;

    T = gsl_min_fminimizer_goldensection;//gsl_min_fminimizer_brent;
    s = gsl_min_fminimizer_alloc (T);
    gsl_min_fminimizer_set (s, &F, k, a, b);

    do {
      iter++;
      /*status = */gsl_min_fminimizer_iterate (s);

      k = gsl_min_fminimizer_x_minimum(s);
      a = gsl_min_fminimizer_x_lower(s);
      b = gsl_min_fminimizer_x_upper(s);

      status = gsl_min_test_interval (a, b, 0.000001, 0.0);

      //if (status == GSL_SUCCESS)
      //  printf ("Converged:\n");

      //std::cout << "(" << iter << ")" << "[" << a << ", " << b << "]: " << k << " Err: " << fn1(k, (void *)&p) << " Range: " << b - a << endl;
    }
    while (status == GSL_CONTINUE && iter < max_iter);

    gsl_min_fminimizer_free (s);
    double lambda = weibullLambda(x, logP, k);

    //std::cout << "weibullFromAmalthea(" << min << ", " << max << ", " << mean << ", " << pRemainPromille << ") : <" << lambda << ", " << k << ">" << endl;

    return WeibullVar(lambda, k);
  }


  void weibullConverterTest()
  {
    double min = 100;
    double max = 200;
    double mean = 130;
    WeibullVar wv = weibullFromAmalthea(min, max, mean, 0.000005);

    ofstream outF;

    outF.open("weibullDistribution.txt", ios::out);
    for (unsigned int i=0; i<1000000; ++i) {
      outF << wv.get(min) << endl;
    }
    outF.close();
  }
}

