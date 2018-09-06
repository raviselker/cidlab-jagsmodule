#include <config.h>
#include "WFCP.h" // class header file
#include <util/nainf.h> // provides na and inf functions

#include <cmath> // basic math operations
#include <iostream>
#include <typeinfo>

#include <algorithm>

#include <util/dim.h>
#include <util/logical.h>

using std::vector; // vector is used in the code
using std::string; // string is used in the code

#define stimA (args[0])
#define stimB (args[1])
#define v (args[2]) // validities
#define s (args[3]) // order of validities
#define begin (*args[4]) // beginning point
#define lower (*args[5]) // lower boundry
#define upper (*args[6]) // upper boundry

namespace jags {
namespace cidlab {

    WFCP::WFCP() :VectorFunction ("WFCP", 7)
    {}

    void WFCP::evaluate (double *value, vector <double const *> const &args,
                         vector<unsigned int> const &lengths) const
    {
        int N = lengths[0];
        std::vector<int> index (N, 0);
        for (unsigned int i = 0; i < N; i++) {
            index[i] = (int)s[i]-1;
        }

        double val = begin;
        for (unsigned int i = 0; i < N; i++) {
            if (stimA[index[i]] > stimB[index[i]]) {
                val += v[ index[i] ];
            } else if (stimB[index[i]] > stimA[index[i]]) {
                val -= v[ index[i] ];
            }

            if (val >= upper) {
                value[0] = 1;
                value[1] = i + 1;
                break;
            } else if (val <= lower) {
                value[0] = 0;
                value[1] = i + 1;
                break;
            } else if (i == (N - 1)) {
                value[0] = 0.5;
                value[1] = N;
                break;
            }
        }
    }

    unsigned int WFCP::length (vector<unsigned int> const &parlengths,
                               vector<double const *> const &parvalues) const
    {
        return 2;
    }

    bool WFCP::isDiscreteValued(vector<bool> const &mask) const
    {
        return allTrue(mask);
    }
}}
