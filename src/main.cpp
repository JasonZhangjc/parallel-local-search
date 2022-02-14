#include <iostream>
#include "QUBO.h"
#include "SOL.h"

using namespace std;
 
int main( ) {

   // initialize two QUBO objects
   QUBO qubo1;
   QUBO qubo2(10);

   int n1 = qubo1.getNumberBits(); 
   int n2 = qubo2.getNumberBits();
   cout << "Bit number of qubo1: " << n1 << endl;
   cout << "Bit number of qubo2: " << n2 << endl;

   // read QUBO
   qubo1.readQUBO(100, 1);
   // qubo1.printQUBO();

   // randomly generate a solution for qubo1
   SOL sol1(100, qubo1.getQMatrix());
   sol1.printSOL();

   return 0;
}