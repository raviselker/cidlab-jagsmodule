#include <config.h>
#include "TTB.h" // class header file
#include <util/nainf.h> // provides na and inf functions

#include <cmath> // basic math operations
#include <iostream>
#include <typeinfo>
#include <stdlib.h>

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

    TTB::TTB() :ScalarVectorFunction ("TTB", 4)
    {}

    double TTB::scalarEval (vector <double const *> const &args,
			                      vector<unsigned int> const &lengths) const
    {
      int N = lengths[0];
      std::vector<int> index (N, 0);
      for (unsigned int i = 0; i < N; i++) {
        index[i] = (int)s[i]-1;
      }

      unsigned int kA = 0;
      unsigned int kB = 0;
      unsigned int value;
      for (unsigned int i = 0; i < N; i++) {
        if (stimA[index[i]] > stimB[index[i]]) {
          kA++;
          if (kA == k) {
            value = 0;
            break;
          }
        } else if (stimB[index[i]] > stimA[index[i]]) {
          kB++;
          if (kB == k) {
            value = 1;
            break;
          }
        }

        if (i == (N - 1)) {
          std::cout << "Random" << '\n';
          value = rand()%(2);
          break;
        }
      }

      return(value);
    }

    bool TTB::checkParameterLength (vector<unsigned int> const &lengths) const
    {
	      return lengths[0] >= 2;
    }

    bool TTB::isDiscreteValued(vector<bool> const &mask) const
    {
	      return allTrue(mask);
    }
}}
