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
  Horn() {
  }
  ~Horn() {
  }

  StatusCode search();

protected:
  
  StatusCode printSAT();
  StatusCode printMaxHornSAT();

};
} // namespace openwbo

#endif
