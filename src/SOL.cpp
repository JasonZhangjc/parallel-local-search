#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include "SOL.h"

using namespace std;


/*
In any constructor, 
if the information is not enough,
always use random generation
*/


// empty constructor
SOL::SOL() {
	// generate a solution with random n, x, and v
	// the range is in [1,100]
	n = 1 + (int)100 * rand() / (RAND_MAX);
	vector<int> x_(n);
	for (int i=0; i<n; i++) {
		x_.push_back((int) (0.5+rand()/RAND_MAX));
	}
	x = x_;
	v = 1 + (int)100 * rand() / (RAND_MAX);
} 


// constructor with n
SOL::SOL(int n_) {
	n = n_;
	// randomly set x 
	vector<int> x_(n);
	for (int i=0; i<n; i++) {
		x_.push_back((int) (0.5+rand()/RAND_MAX));
	}
	x = x_;
	// randomly set v in range [1,100]
	v = 1 + (int)100 * rand() / (RAND_MAX);
} 


// constructor with n and q_matrix;
// commonly used in this class
SOL::SOL(int n_, vector<vector<int>> q_matrix) {
	n = n_;

	// randomly set x 
	vector<int> x_(n);
	for (int i=0; i<n; i++) {
		x_.push_back((int) (0.5+rand()/RAND_MAX));
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
	v = v_;
}


// constructor with n, x, and q_matrix
// commonly used in this class
SOL::SOL(int n_, vector<int> x_, vector<vector<int>> q_matrix) {
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
	v = v_;
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