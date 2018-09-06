#ifndef WADDk_FUNC_H_
#define WADDk_FUNC_H_

#include <function/VectorFunction.h>

namespace jags {
namespace cidlab {

    class WADDk : public VectorFunction
    {
    public:
        WADDk();

        void evaluate(double *value, std::vector <double const *> const &args,
                      std::vector <unsigned int> const &lengths) const;

        unsigned int length(std::vector<unsigned int> const &parlengths,
                            std::vector<double const *> const &parvalues) const;

        bool isDiscreteValued(std::vector<bool> const &mask) const;
    };

}}

#endif /* WADDk_FUNC_H_ */
