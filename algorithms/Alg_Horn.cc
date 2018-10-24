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

StatusCode Horn::printMaxHornSAT1(){
    
    // pppppppnnnnnnn
    //Variant 1: The p_i variables have the same index as the original variables; the n_i variables start with index n+1 (where n is the number variables)
     
 
    
    int hard_weight = maxsat_formula->nVars()*2+1; //hard_weight is number of p_i's and n_i's plus 1
    int num_vars = 2 * maxsat_formula->nVars(); //two new vars (p and n) for each x
    int num_clause = num_vars + maxsat_formula->nVars() + maxsat_formula->nHard()+maxsat_formula->nSoft();
    // Print header
    printf("c MaxHornSAT formula\n");
    printf("p wcnf %d %d %d\n",num_vars, num_clause, hard_weight);
    
    //The soft clauses that are just p_i and n_i
    for (int i = 0; i < maxsat_formula->nVars() * 2;i++){
        printf("%d %d %d\n", 1, i+1, 0);
    }
    
    //The -p_i or -n_i
    for (int i = 0; i < maxsat_formula->nVars();i++){
        printf("%d -%d -%d %d\n",  hard_weight, i+1, i+1+maxsat_formula->nVars(), 0);
    }
    // Traverse all hard clauses and print them
    
    for (int i = 0; i < maxsat_formula->nSoft(); i++){
        // Clauses are stored in vectors
        printf("%d ",hard_weight);
        for (int j = 0; j < maxsat_formula->getSoftClause(i).clause.size(); j++){
            // if it has a sign then the variable is negated, e.g. ~x_i
            if ((sign(maxsat_formula->getSoftClause(i).clause[j])))
                printf("-%d ",(var(maxsat_formula->getSoftClause(i).clause[j]))+1);
            else
                printf("-%d ",(var(maxsat_formula->getSoftClause(i).clause[j]))+1+maxsat_formula->nVars());
            // 'var' returns the variable integer that corresponds to that clause
        }
        // end of clause
        printf("0\n");
    }
    
    
    
    return _UNKNOWN_;
}




StatusCode Horn::printMaxHornSAT2(){
    
    // nnnnnnppppppp
     // Variant 2: The n_i variables have the same index as the original variables; the p_i variables start with index n+1 (where n is the number variables
    
    
    int hard_weight = maxsat_formula->nVars()*2+1; //hard_weight is number of p_i's and n_i's plus 1
    int num_vars = 2 * maxsat_formula->nVars(); //two new vars (p and n) for each x
    int num_clause = num_vars + maxsat_formula->nVars() + maxsat_formula->nHard()+maxsat_formula->nSoft();
    // Print header
    printf("c MaxHornSAT formula\n");
    printf("p wcnf %d %d %d\n",num_vars, num_clause, hard_weight);
    
    //The soft clauses that are just p_i and n_i
    for (int i = 0; i < maxsat_formula->nVars() * 2;i++){
        printf("%d %d %d\n", 1, i+1, 0);
    }
    
    //The -p_i or -n_i
    for (int i = 0; i < maxsat_formula->nVars();i++){
        printf("%d -%d -%d %d\n",  hard_weight, i+1, i+1+maxsat_formula->nVars(), 0);
    }
    // Traverse all hard clauses and print them
    for (int i = 0; i < maxsat_formula->nSoft(); i++){
        // Clauses are stored in vectors
        printf("%d ",hard_weight);
        for (int j = 0; j < maxsat_formula->getSoftClause(i).clause.size(); j++){
            // if it has a sign then the variable is negated, e.g. ~x_i
            if ((sign(maxsat_formula->getSoftClause(i).clause[j])))
                printf("-%d ",(var(maxsat_formula->getSoftClause(i).clause[j]))+1+maxsat_formula->nVars());
            else
                printf("-%d ",(var(maxsat_formula->getSoftClause(i).clause[j]))+1);
            // 'var' returns the variable integer that corresponds to that clause
        }
        // end of clause
        printf("0\n");
    }
    
    
    return _UNKNOWN_;
}


StatusCode Horn::printMaxHornSAT3(){
    
    // pnpnpnpnpn
    //Variant 3: Do the following variable mapping: x_1 will get the mapped to p_1 (variable 1) and n_1 (variable 2); x_2 will be mapped to p_2 (variable 3) and n_2 (variable 4); etc.
     
 
    
    int hard_weight = maxsat_formula->nVars()*2+1; //hard_weight is number of p_i's and n_i's plus 1
    int num_vars = 2 * maxsat_formula->nVars(); //two new vars (p and n) for each x
    int num_clause = num_vars + maxsat_formula->nVars() + maxsat_formula->nHard()+maxsat_formula->nSoft();
    // Print header
    printf("c MaxHornSAT formula\n");
    printf("p wcnf %d %d %d\n",num_vars, num_clause, hard_weight);
    
    //The soft clauses that are just p_i and n_i
    for (int i = 0; i < maxsat_formula->nVars() * 2;i++){
        printf("%d %d %d\n", 1, i+1, 0);
    }
    
    //The -p_i or -n_i
    for (int i = 0; i < maxsat_formula->nVars();i++){
        printf("%d -%d -%d %d\n",  hard_weight, (2*i)+1, (2*i)+2, 0);
    }
    // Traverse all hard clauses and print them
    
    for (int i = 0; i < maxsat_formula->nSoft(); i++){
        // Clauses are stored in vectors
        printf("%d ",hard_weight);
        for (int j = 0; j < maxsat_formula->getSoftClause(i).clause.size(); j++){
            // if it has a sign then the variable is negated, e.g. ~x_i
            if ((sign(maxsat_formula->getSoftClause(i).clause[j])))
                printf("-%d ",(var(maxsat_formula->getSoftClause(i).clause[j])*2)+1);
            else
                printf("-%d ",(var(maxsat_formula->getSoftClause(i).clause[j])*2)+2);
            // 'var' returns the variable integer that corresponds to that clause
        }
        // end of clause
        printf("0\n");
    }
    
    
    return _UNKNOWN_;
}



StatusCode Horn::printMaxHornSAT4(){
    
    // npnpnpnpnp
    //"Current translation" but i think its supposed to have ps and ns reversed from current bc variant 3's description is the current one
 
    
    int hard_weight = maxsat_formula->nVars()*2+1; //hard_weight is number of p_i's and n_i's plus 1
    int num_vars = 2 * maxsat_formula->nVars(); //two new vars (p and n) for each x
    int num_clause = num_vars + maxsat_formula->nVars() + maxsat_formula->nHard()+maxsat_formula->nSoft();
    // Print header
    printf("c MaxHornSAT formula\n");
    printf("p wcnf %d %d %d\n",num_vars, num_clause, hard_weight);
    
    //The soft clauses that are just p_i and n_i
    for (int i = 0; i < maxsat_formula->nVars() * 2;i++){
        printf("%d %d %d\n", 1, i+1, 0);
    }
    
    //The -p_i or -n_i
    for (int i = 0; i < maxsat_formula->nVars();i++){
        printf("%d -%d -%d %d\n",  hard_weight, (2*i)+1, (2*i)+2, 0);
    }
    // Traverse all hard clauses and print them
    for (int i = 0; i < maxsat_formula->nSoft(); i++){
        // Clauses are stored in vectors
        printf("%d ",hard_weight);
        for (int j = 0; j < maxsat_formula->getSoftClause(i).clause.size(); j++){
            // if it has a sign then the variable is negated, e.g. ~x_i
            if ((sign(maxsat_formula->getSoftClause(i).clause[j])))
                printf("-%d ",(var(maxsat_formula->getSoftClause(i).clause[j])*2)+2);
            else
                printf("-%d ",(var(maxsat_formula->getSoftClause(i).clause[j])*2)+1);
            // 'var' returns the variable integer that corresponds to that clause
        }
        // end of clause
        printf("0\n");
    }
    
    return _UNKNOWN_;
}



