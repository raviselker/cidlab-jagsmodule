#include <config.h>
#include "LogBernFun.h" // class header file
#include <util/nainf.h> // provides na and inf functions

#include <cmath> // basic math operations
#include <iostream>
#include <typeinfo>

using std::vector; // vector is used in the code
using std::string; // string is used in the code

#define x(par) (*args[0])
#define prob(par) (*args[1])

namespace jags {
namespace Bernoulli {

  // constructor function
  LogBernFun::LogBernFun() :ScalarFunction("logbern", 2)
  {}

  // checks if the parameter pi lies between 0 and 1
  bool LogBernFun::checkParameterValue(vector<double const *> const &args) const
  {
    return (x(par) == 0.0 || x(par) == 1.0
     && (prob(par) <= 1.0 && prob(par) >= 0.0));
  }

  // does the computation that the logical node is supposed to do
  double LogBernFun::evaluate(vector<double const *> const &args) const
  {
    double d = ( (x(par) == 1) ? prob(par) : 1-prob(par) );
    return (d == 0) ? JAGS_NEGINF : log(d);
  }

}
}
