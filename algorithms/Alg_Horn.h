#ifndef Alg_Horn_h
#define Alg_Horn_h

#ifdef SIMP
#include "simp/SimpSolver.h"
#else
#include "core/Solver.h"
#endif

#include "../Encoder.h"
#include "../MaxSAT.h"
#include <algorithm>
#include <map>
#include <set>

namespace openwbo {

//=================================================================================================
class Horn : public MaxSAT {

public:
  Horn(int opt) {
      option = opt;
  }
    
    Horn(MaxSATFormula* mx){
        maxsat_formula = mx;
    }
    
  ~Horn() {
  }

  StatusCode search();
  MaxSATFormula* printMaxHornSAT1();

protected:
    
    int option;
  
  StatusCode printSAT();
    StatusCode printMaxSAT(MaxSATFormula *mx);
  StatusCode printMaxHornSAT();
    StatusCode printMaxHornSAT2();
    StatusCode printMaxHornSAT3();
    StatusCode printMaxHornSAT4();

};
} // namespace openwbo

#endif
