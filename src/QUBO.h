#ifndef QUBO_H
#define QUBO_H

#include <vector>

using namespace std;

class QUBO {
	/* 
	Quadratic Unconstrained Binary Optimization;
	Two members: 
		number of bits in QUBO: number_bits;
		QUBO matrix: q_matrix 
	Several functions to manipulate QUBO 
	*/

	private:
		int number_bits;

		vector<vector<int>> q_matrix; 

	public:
		// empty constructor
		QUBO(); 

		// constructor with a parameter of number_bits
		QUBO(int); 

		// getter for number_bits
		int getNumberBits();

		// getter for q_matrix
		vector<vector <int> > getQMatrix();

		// read QUBO files
		void readQUBO(int, int);

		// print QUBO
		void printQUBO();

};

#endif // QUBO_H