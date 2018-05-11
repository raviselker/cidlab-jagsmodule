#include <module/Module.h> // include JAGS module base class
#include <distributions/DBern.h> // include Bernoulli distribution class
#include <functions/LogBernFun.h> // include Bernoulli function class

namespace jags {
namespace Bernoulli { // start defining the module namespace

  // Module class
  class BERNModule : public Module {
    public:
      BERNModule(); // constructor
      ~BERNModule(); // destructor
  };

  // Constructor function
  BERNModule::BERNModule() : Module("Bernoulli") {
    insert(new DBern); // inherited function to load objects into JAGS
    insert(new LogBernFun);
  }

  // Destructor function
  BERNModule::~BERNModule() {
    std::vector<Distribution*> const &dvec = distributions();
    for (unsigned int i = 0; i < dvec.size(); ++i) {
      delete dvec[i]; // delete all instantiated distribution objects
    }

    std::vector<Function*> const &fvec = functions();
    for (unsigned int i = 0; i < fvec.size(); ++i) {
      delete fvec[i];
    }
  }

} // end namespace definition
}

jags::Bernoulli::BERNModule _Bernoulli_module;
