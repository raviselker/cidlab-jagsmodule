#include <config.h>   // system configuration file, created by Autoconf
                      // and defined in configure.ac
#include "DBern.h"    // header file containing class prototype
#include <rng/RNG.h>  // provides random functions
#include <util/nainf.h> // provides na and inf functions etc.

#include <cmath>      // library for standard math operations

using std::vector;    // vector is used in code
using std::min;       // min is used in code
using std::max;       // max is used in code

#define PROB(par) (*par[0]) // makes code more readable

namespace jags {
namespace wfComboPack { // module namespace

DBern::DBern() : ScalarDist("dbern2", 1, DIST_PROPORTION)
{}

bool DBern::checkParameterValue (vector<double const *> const &
    parameters) const
{
  return (PROB(parameters) >= 0.0 && PROB(parameters) <= 1.0);
}

double DBern::logDensity(double x, PDFType type,
    vector<double const *> const &parameters,
    double const *lbound, double const *ubound) const
{
  double d = (x ? PROB(parameters) : 1 - PROB(parameters));
  return(d == 0) ? JAGS_NEGINF : log(d);
}

double DBern::randomSample(vector<double const *> const &parameters,
    double const *lbound, double const *ubound,
    RNG *rng) const
{
  return (rng->uniform() < PROB(parameters)) ? 1 : 0;
}

double DBern::typicalValue(vector<double const *> const &parameters,
    double const *lbound, double const *ubound) const
{
  return (PROB(parameters) > 0.5) ? 1 : 0;
}

bool DBern::isDiscreteValued(vector<bool> const &mask) const
{
    return true;
}

}
}
