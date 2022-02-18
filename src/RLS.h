#ifndef RLS_H
#define RLS_H

#include <vector>
#include "QUBO.h"
#include "SOL.h"

using namespace std;

/*
There is no empty constructor for this class
must pass parameters
*/

class RLS {
	/* 
	REVERSED Local Search Algorithm for QUBO;
	Why it is reversed?
	Because it starts from a local optima and
	exhaustively search outward
	Consider all 1-bit flips at each Monte Carlo step
	Guaranteed to reach local optima with sufficient time
	Two members: 
		a QUBO object: qubo
		a SOL object as the initial solution: sol
	Several functions to manipulate RLS
	*/

	private:
		QUBO qubo;

		SOL sol_init;

	public:
		// constructor with a parameter of number_bits
		RLS(QUBO, SOL); 

		// getter for qubo
		QUBO getQubo();

		// getter for sol_init
		SOL getSolInit();

		// calculate the value of a sol.x
		int calculateValue(vector<int>);

		// check whether a SOL is a local worst for the QUBO
		// a local worst is the worst solution in the neighborhood
		bool checkLocalWorst(SOL);

		// reversed local search algorithm: the opposite to LS::localSearchALl()
		// consider all 1-bit flips
		// 1st parameter for the max number of iterations
		// 2nd parameter for initializing distinct random seed
		// accept >= states
		vector<vector<int>> reversedLocalSearchAllEqual(int, int);

		// reversed local search algorithm: the opposite to LS::localSearchALl()
		// consider all 1-bit flips
		// 1st parameter for the max number of iterations
		// 2nd parameter for initializing distinct random seed
		// accept > states
		vector<vector<int>> reversedLocalSearchAllMore(int, int);

		// reversed local search algorithm: the opposite to RLS::localSearchOne()
		// consider one 1-bit flips
		// 1st parameter for the max number of iterations
		// 2nd parameter for initializing distinct random seed
		// 3rd parameter for temperature
		vector<vector<int>> reversedLocalSearchOne(int, int, int);

};

#endif // RLS_H
