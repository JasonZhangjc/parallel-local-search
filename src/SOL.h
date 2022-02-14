#ifndef SOL_H
#define SOL_H

#include <vector>

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

		// constructor with n and q_matrix;
		SOL(int, vector<vector<int>>); 

		// constructor with n, x, and q_matrix
		SOL(int, vector<int>, vector<vector<int>>); 

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