#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "QUBO.h"
#include "SOL.h"

using namespace std;


/*
In any constructor, 
if the information is not enough,
always use random generation
*/



// empty constructor
SOL::SOL() {
	// set random seed
	time_t t;
	srand((unsigned) time(&t));

	// generate a solution with random n, x, and v
	// the range is in [1,100]
	n = 1 + (int)100 * rand() / (RAND_MAX);
	vector<int> x_(n);
	for (int i=0; i<n; i++) {
		x_[i] = rand()%2;
	}
	x = x_;
	v = 1 + (int)100 * rand() / (RAND_MAX);
} 


// constructor with n
SOL::SOL(int n_) {
	// set random seed
	time_t t;
	srand((unsigned) time(&t));

	n = n_;
	// randomly set x 
	vector<int> x_(n);
	for (int i=0; i<n; i++) {
		x_[i] = rand()%2;
	}
	x = x_;
	// randomly set v in range [1,100]
	v = 1 + (int)100 * rand() / (RAND_MAX);
}


// constructor with n, q_matrix, and constant;
// commonly used in this class
SOL::SOL(int n_, vector<vector<int>> q_matrix, int constant) {
	// set random seed
	time_t t;
	srand((unsigned) time(&t));

	n = n_;

	// randomly set x 
	vector<int> x_(n);
	for (int i=0; i<n; i++) {
		x_[i] = rand()%2;
	}
	x = x_;

	// calculate v
	assert(q_matrix.size() == n);
	int v_ = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			v_ = v_ + x[i] * q_matrix[i][j] * x[j];
		}
	}
	v = v_ + constant;
}


// constructor with n, x, q_matrix, and constant
// commonly used in this class
SOL::SOL(int n_, vector<int> x_, vector<vector<int>> q_matrix,  int constant) {
	n = n_;

	assert(x_.size() == n);
	x = x_;

	// calculate v
	assert(q_matrix.size() == n);
	int v_ = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			v_ = v_ + x[i] * q_matrix[i][j] * x[j];
		}
	}
	v = v_ + constant;
}


// constructor with a QUBO object;
SOL::SOL(QUBO qubo) {
	// set random seed
	time_t t;
	srand((unsigned) time(&t));

	n = qubo.getNumberBits();

	// randomly set x 
	vector<int> x_(n);
	for (int i=0; i<n; i++) {
		x_[i] = rand()%2;
	}
	x = x_;

	// calculate v
	vector<vector<int>> q_matrix = qubo.getQMatrix();
	assert(q_matrix.size() == n);
	int v_ = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			v_ = v_ + x[i] * q_matrix[i][j] * x[j];
		}
	}
	v = v_ + qubo.getConstant();
} 


// constructor with x and a QUBO object
SOL::SOL(vector<int> x_, QUBO qubo) {
	n = qubo.getNumberBits();

	assert(x_.size() == n);
	x = x_;

	// calculate v
	vector<vector<int>> q_matrix = qubo.getQMatrix();
	assert(q_matrix.size() == n);
	int v_ = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			v_ = v_ + x[i] * q_matrix[i][j] * x[j];
		}
	}
	v = v_ + qubo.getConstant();
}


// getter for n
int SOL::getN() {
	// check n is valid or not
	assert(n >= 0);
	return n;
}


// getter for x
vector <int> SOL::getX() {
	// check the length of x
	assert(x.size() == n);
	return x;
}


// getter for v
int SOL::getV() {
	// check v is valid or not
	assert(v >= 0);
	return v;
}


// read a solution (a local optima usually)
// parameters: number of bits, ID of the QUBO, ID of the solution
void SOL::readSOL(int number_bits, int QUBO_ID, int SOL_ID) {
	cout << "Reading QUBO_SOL files #" << SOL_ID << " now!" << endl;
	
	if (number_bits != n) {
		cout << "set number_bits when reading QUBO_SOL files" << endl;
		n = number_bits;
	}

	// determine the filename
	string filename_head("qubo_sol_");
	stringstream sstreamNB, sstreamQuboID, sstreamSolID;
	sstreamNB << number_bits;
	sstreamQuboID << QUBO_ID;
	sstreamSolID << SOL_ID;
	string str_NB = sstreamNB.str(); // NB: number_bits
	string str_QuboID = sstreamQuboID.str();
	string str_SolID = sstreamSolID.str();
	string filename_mid("_");
	string filename_tail(".txt");

	string filename;
	filename = filename_head + str_NB + filename_mid + \
			   str_QuboID + filename_mid + str_SolID + filename_tail;
	cout << "filename: " << filename << endl;

	// read file
	ifstream infile; 
   	infile.open(filename); 

   	// check whether infile is open
   	assert(infile.is_open());

   	// read the first line for NB, QuboID, and SolID
   	string line;
   	getline(infile, line);
   	stringstream ssline(line);
   	string NB;      // NB: number_bits
   	string QuboID;      // CO: constant
   	string SolID;      // PE: penalty
   	ssline >> NB;
   	ssline >> QuboID;
   	ssline >> SolID;
   	assert(stoi(NB) == number_bits);
   	assert(stoi(QuboID) == QUBO_ID);
   	assert(stoi(SolID) == SOL_ID);

   	// read the solution vector: NB entries
   	// clear the x at first
   	x.clear();
    getline(infile, line);
    stringstream ssline_x(line);
    string pos;
    while (ssline_x >> pos) {
    	x.push_back(stoi(pos));
    }

    // check the number of rows of x
    cout << "x.size() is: " << x.size() << endl;
    assert(x.size() == number_bits);

    // read the value of the solution
    getline(infile, line);
    stringstream ssline_v(line);
    ssline_v >> pos;
    v = stoi(pos);
    cout << "The v is: " << v << endl;

   	// close the file
    infile.close();
}


// print SOL
void SOL::printSOL() {
	// print n
	cout << "The number of bits is: " << n << endl;

	// print x
	cout << "The size of x is: " << x.size() << endl;
	assert(x.size() == n);
	cout << "The solution x is: " << endl;
	for (int i=0; i<x.size(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;

	// print v
	cout << "The value v is: " << v << endl;
}
