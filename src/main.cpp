#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "QUBO.h"
#include "SOL.h"
#include "LS.h"
#include "RLS.h"

using namespace std;


/*
NUMBER_BITS: number of bits
QUBO_ID: 1 for TSP, 2 for JSP, 3 for LBP, 4 for LBP+RPC
SOL_ID: solution ID

When QUBO_ID==2, things are weird
*/

 
int main( ) {

   int NUMBER_BITS = 100;
   int QUBO_ID = 2;
   int SOL_ID = 1;

   // initialize two QUBO objects
   QUBO qubo1;
   QUBO qubo2(10);

   int n1 = qubo1.getNumberBits(); 
   int n2 = qubo2.getNumberBits();
   cout << "Bit number of qubo1: " << n1 << endl;
   cout << "Bit number of qubo2: " << n2 << endl;

   // read QUBO: penalty is 100
   qubo1.readQUBO(NUMBER_BITS, QUBO_ID);
   // qubo1.printQUBO();

   // randomly generate a solution for qubo1
   SOL sol1(qubo1);

   // create a local search object
   LS ls1(qubo1, sol1);
   cout << "Test localSearchAll----------------------------------------" << endl;
   vector<vector<int>> solution_list_ALL;
   solution_list_ALL = ls1.localSearchAll(100, 1);

   // create a reversed local search object
   RLS rls1(qubo1, sol1);
   cout << "Test reversedLocalSearchAll--------------------------------" << endl;
   vector<vector<int>> worse_solution_list_ALL;
   worse_solution_list_ALL = rls1.reversedLocalSearchAll(1000, 1);


   // read a good loca optima!
   sol1.readSOL(NUMBER_BITS, QUBO_ID, SOL_ID);
   // sol1.printSOL();

   // create a reversed local search object
   RLS rls2(qubo1, sol1);
   cout << "Test reversedLocalSearchAll--------------------------------" << endl;
   worse_solution_list_ALL = rls2.reversedLocalSearchAll(1000, 1);


   // some for loop ***********************************************************
   // create a local search object
   // LS ls1(qubo1, sol1);

   // evaluate some random solutions and 
   // calculate the probability of good local optima
   // set the number of random solutions for testing
   // int number_solutions = 10;
   // cout << "Test " << number_solutions \
   // << " random solutions-----------------------------------" << endl;

   // vector<int> for returns of the LS::localSearchAll()
   // vector<vector<int>> solution_list_ALL;
   // vector<vector<int>> solution_list_ONE;

   // counter of good local optima
   // int count_good_ALL = 0;
   // int count_good_ONE = 0;

   // for (int i=0; i<number_solutions; i++) {
      // randomly generate a solution
      // SOL sol1(qubo1);

      // verify whether the solution is a local optima
      // ls1.checkLocalOpt(sol1);
      // solution_list_ALL = ls1.localSearchAll(100, i);
      // solution_list_ONE = ls1.localSearchOne(10000000, i, 10000);

      // evaluate the last solution in the solution_list_ALL
      // int value_ALL = \
      // ls1.calculateValue(solution_list_ALL[solution_list_ALL.size()-1]);
      // cout << "The value_ALL at iteration " << i \
      // << " is " << value_ALL << endl;
      // if (value_ALL < 200) {
      //    count_good_ALL ++;
      // }

      // evaluate the last solution in the solution_list_ONE
      // int value_ONE = \
      // ls1.calculateValue(solution_list_ONE[solution_list_ONE.size()-1]);
      // cout << "The value_ONE at iteration " << i \
      // << " is " << value_ONE << endl;
      // if (value_ONE < 200) {
      //    count_good_ONE ++;
      // }
   // }

   // cout << "The count_good_ALL is: " << count_good_ALL << endl;
   // cout << "The count_good_ONE is: " << count_good_ONE << endl;
   

   // TODO: store results in a file



   return 0;
}
