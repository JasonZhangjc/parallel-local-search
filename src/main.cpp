#include <iostream>
#include "QUBO.h"
#include "SOL.h"
#include "LS.h"

using namespace std;
 
int main( ) {

   // initialize two QUBO objects
   QUBO qubo1;
   QUBO qubo2(10);

   int n1 = qubo1.getNumberBits(); 
   int n2 = qubo2.getNumberBits();
   cout << "Bit number of qubo1: " << n1 << endl;
   cout << "Bit number of qubo2: " << n2 << endl;

   // read QUBO: penalty is 100
   qubo1.readQUBO(100, 1);
   // qubo1.printQUBO();

   // randomly generate a solution for qubo1
   SOL sol1(qubo1);
   // sol1.printSOL();

   // verify whether the solution is a local optima
   LS ls1(qubo1, sol1);
   ls1.checkLocalOpt(sol1);
   ls1.localSearchAll(100);
   ls1.localSearchOne(10000);

   return 0;
}
