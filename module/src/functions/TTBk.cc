#include <config.h>
#include "TTBk.h" // class header file
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
#define s (args[2]) // order of validities
#define k (*args[3]) // number of discriminating cues before decision is made

namespace jags {
namespace cidlab {

    TTBk::TTBk() :VectorFunction ("TTBk", 4)
    {}

    void TTBk::evaluate (double *value, vector <double const *> const &args,
                         vector<unsigned int> const &lengths) const
    {
        int N = lengths[0];
        std::vector<int> index (N, 0);
        for (unsigned int i = 0; i < N; i++) {
            index[i] = (int)s[i]-1;
        }

        unsigned int kA = 0;
        unsigned int kB = 0;
        for (unsigned int i = 0; i < N; i++) {
            if (stimA[index[i]] > stimB[index[i]]) {
                kA++;
                if (kA == k) {
                    value[0] = 1;
                    value[1] = i + 1;
                    break;
                }
            } else if (stimB[index[i]] > stimA[index[i]]) {
                kB++;
                if (kB == k) {
                    value[0] = 0;
                    value[1] = i + 1;
                    break;
                }
            }

            if (i == (N - 1)) {
                value[0] = 0.5;
                value[1] = N;
                break;
            }
        }
    }

    unsigned int TTBk::length (vector<unsigned int> const &parlengths,
                               vector<double const *> const &parvalues) const
    {
        return 2;
    }

    bool TTBk::isDiscreteValued(vector<bool> const &mask) const
    {
        return allTrue(mask);
    }
}}
