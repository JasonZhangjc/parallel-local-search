#ifndef SOL_H
#define SOL_H

#include <vector>
#include "QUBO.h"

using namespace std;

class SOL {
	/* 
	A class of the solution to QUBO;
	Three members: 
		n: number of bits
		x: a vector of bits;
		v: value of the solution
		v = x^T * Q * x
	Several functions to manipulate the solution 
	*/

	private:
		int n;

		vector<int> x;

		int v; 

	public:
		// empty constructor
		SOL(); 

		// constructor with n
		SOL(int); 

		// constructor with n, q_matrix, and constant
		SOL(int, vector<vector<int>>, int); 

		// constructor with n, x, q_matrix, and constant
		SOL(int, vector<int>, vector<vector<int>>, int); 

		// constructor with a QUBO object;
		SOL(QUBO); 

		// constructor with x and a QUBO object
		SOL(vector<int>, QUBO); 

		// getter for n
		int getN();

		// getter for x
		vector <int> getX();

		// getter for v
		int getV();

		// print SOL
		void printSOL();

};

#endif // SOL_H