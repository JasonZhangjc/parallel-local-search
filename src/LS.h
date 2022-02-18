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
	the localSearchAll method
	considers all 1-bit flips at each Monte Carlo step
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
		// 1st parameter for the max number of iterations
		// 2nd parameter for initializing distinct random seed
		// accept <= states
		vector<vector<int>> localSearchAllEqual(int, int);

		// local search algorithm
		// consider all 1-bit flips
		// 1st parameter for the max number of iterations
		// 2nd parameter for initializing distinct random seed
		// accept < states
		vector<vector<int>> localSearchAllLess(int, int);

		// local search algorithm
		// simulated annealing
		// consider one 1-bit flips
		// 1st parameter for the max number of iterations
		// 2nd parameter for initializing distinct random seed
		// 3rd parameter for temperature
		vector<vector<int>> localSearchOne(int, int, int);

};

#endif // LS_H
