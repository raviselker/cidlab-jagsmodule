#include <config.h>
#include "LogBernFun.h" // class header file
#include <util/nainf.h> // provides na and inf functions

#include <cmath> // basic math operations
#include <iostream>
#include <typeinfo>

using std::vector; // vector is used in the code
using std::string; // string is used in the code

// #define x(par) (*args[0])
// #define prob(par) (*args[1])

#define choice (args[0])
//#define reward (*args[1])
//#define va (*args[2])
//#define vb (*args[3])
//#define a (*args[4])

namespace jags {
namespace Bernoulli {

  // constructor function
  LogBernFun::LogBernFun() :ScalarFunction("logbern", 5)
  {}

  // checks if the parameter pi lies between 0 and 1
  bool LogBernFun::checkParameterValue(vector<double const *> const &args) const
  {
    //return (x(par) == 0.0 || x(par) == 1.0
    //  && (prob(par) <= 1.0 && prob(par) >= 0.0));
  }

  // does the computation that the logical node is supposed to do
  double LogBernFun::evaluate(vector<double const *> const &args) const
  {
    for (int i = 0; i < args.size(); i++) {
      printf("%i\n", i);
      printf("%.7lf\n", *args[i]);
    }
    // printf("%lo\n", sizeof(*args[2]));
    // printf("%.7lf\n",x(par));
    // printf("%.7lf\n",prob(par));
    // printf("%.7lf\n", *args[1]);
    //double d = ( (x(par) == 1) ? prob(par) : 1-prob(par) );
    //return (d == 0) ? JAGS_NEGINF : log(d);
  }

}
}
