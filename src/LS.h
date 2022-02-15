#ifndef LS_H
#define LS_H

#include <vector>
#include "QUBO.h"
#include "SOL.h"

using namespace std;

/*
There is no empty constructor for this class
must pass parameters
*/

class LS {
	/* 
	Local Search Algorithm for QUBO;
	Consider all 1-bit flips at each Monte Carlo step
	Guaranteed to reach local optima with sufficient time
	Two members: 
		a QUBO object: qubo
		a SOL object as the initial solution: sol
	Several functions to manipulate LS
	*/

	private:
		QUBO qubo;

		SOL sol_init;

	public:
		// constructor with a parameter of number_bits
		LS(QUBO, SOL); 

		// getter for qubo
		QUBO getQubo();

		// getter for sol_init
		SOL getSolInit();

		// calculate the value of a sol.x
		int calculateValue(vector<int>);

		// check whether a SOL is a local optima for the QUBO
		bool checkLocalOpt(SOL);

		// local search algorithm
		// consider all 1-bit flips
		// parameter for the max number of iterations
		vector<vector<int>> localSearchAll(int);

		// local search algorithm
		// consider one 1-bit flips
		// parameter for the max number of iterations
		void localSearchOne(int);

};

#endif // LS_H