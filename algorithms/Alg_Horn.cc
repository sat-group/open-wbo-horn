#include "Alg_Horn.h"

using namespace openwbo;

StatusCode Horn::search() {
  // Here you can control which algorithm is being used!
  // It if useful if we implement different transformations from SAT to MaxHornSAT
  
  return printMaxHornSAT();
}

StatusCode Horn::printSAT(){

  /*
   * The 'maxsat_formula' will contain all the information from the SAT/MaxSAT 
   * formula that is read from the standard input
   */

  // Print header
  printf("c original SAT formula\n");
  printf("p cnf %d %d\n",maxsat_formula->nVars(),maxsat_formula->nHard()+maxsat_formula->nSoft());

  // Traverse all hard clauses and print them
  for (int i = 0; i < maxsat_formula->nHard(); i++){
    // Clauses are stored in vectors
    for (int j = 0; j < maxsat_formula->getHardClause(i).clause.size(); j++){
      // if it has a sign then the variable is negated, e.g. ~x_i
      if ((sign(maxsat_formula->getHardClause(i).clause[j])))
        printf("-");
      // 'var' returns the variable integer that corresponds to that clause
      printf("%d ",var(maxsat_formula->getHardClause(i).clause[j])+1);
    }
    // end of clause
    printf("0\n");
  }

  // Traverse all soft clauses and print them
  for (int i = 0; i < maxsat_formula->nSoft(); i++){
    // Clauses are stored in vectors
    for (int j = 0; j < maxsat_formula->getSoftClause(i).clause.size(); j++){
      // if it has a sign then the variable is negated, e.g. ~x_i
      if ((sign(maxsat_formula->getSoftClause(i).clause[j])))
        printf("-");
      // 'var' returns the variable integer that corresponds to that clause
      // Note: variables start at 0 but when printing you should start by 1
      printf("%d ",var(maxsat_formula->getSoftClause(i).clause[j])+1);
    }
    // end of clause
    printf("0\n");
  }

  return _UNKNOWN_;
}

StatusCode Horn::printMaxHornSAT(){

  /*
   * Implement the conversion from SAT to MaxHornSAT
   */
    // Print header
    printf("c MaxHornSAT formula\n");
    printf("p wcnf %d %d %d\n",maxsat_formula->nVars(),maxsat_formula->nHard()+maxsat_formula->nSoft(), maxsat_formula->nSoft()+1);
    
    //The soft clauses that are just p_i and n_i
    for (int i = 0; i < maxsat_formula->nVars() * 2;i++){
        printf("%d %d %d\n", 1, i+1, 0)
    }
    
    //The -p_i or -n_i
    for (int i = 0; i < maxsat_formula->nVars() * 2;i++){
        printf("%d -%d -%d %d\n",  (maxsat_formula->nVars() * 2) + 1, (2*i)+1, (2*i)+2, 0)
    }
    // Traverse all hard clauses and print them
    for (int i = 0; i < maxsat_formula->nHard(); i++){
        // Clauses are stored in vectors
        for (int j = 0; j < maxsat_formula->getHardClause(i).clause.size(); j++){
            // if it has a sign then the variable is negated, e.g. ~x_i
            if ((sign(maxsat_formula->getHardClause(i).clause[j])))
                printf("-%d ",(var(maxsat_formula->getHardClause(i).clause[j])*2)+1);
            else
                printf("-%d ",(var(maxsat_formula->getHardClause(i).clause[j])*2)+2);
            // 'var' returns the variable integer that corresponds to that clause
        }
        // end of clause
        printf("0\n");
    }
   

  // Hint: for each variable you will need to create p_i and n_i variables.
  //       You will need to store a mapping between x_i -> p_i an x_i -> n_i 
  //       and when you traverse the formula print the corresponding variable.
  //       Do not forget to add the clauses that say that exactly one p_i and 
  //       n_i can occur.

  return _UNKNOWN_;
}
