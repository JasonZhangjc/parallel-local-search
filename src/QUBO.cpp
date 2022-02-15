#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "QUBO.h"

using namespace std;


/*
In any constructor,
never initialize QUBO with random matrix,
only read QUBO matrix from qubo_NB_ID.txt
*/


// empty constructor
QUBO::QUBO() {
	// set random seed
	time_t t;
	srand((unsigned) time(&t));

	// Initialize a QUBO with a random size in range [1,100]
	int dim = 1 + (int)100 * rand() / (RAND_MAX);

	// set number_bits to dim
	number_bits = dim; 

	// set constant and penalty to 0
	constant = 0;
	penalty = 0;

	// set q_matrix to an empty matrix
	vector<vector<int>> q_matrix_(dim ,vector<int>(dim));
	q_matrix = q_matrix_;
} 


// constructor with a parameter of number_bits
QUBO::QUBO(int number_bits_) {
	// set number_bits to number_bits_ and 
	number_bits = number_bits_;
	
	// set q_matrix to a square matrix with dim=number_bits
	vector<vector<int>> q_matrix_(number_bits_ ,vector<int>(number_bits_));
	q_matrix = q_matrix_;

	// set constant and penalty to 0
	constant = 0;
	penalty = 0;
}


// getter for number_bits
int QUBO::getNumberBits() {
	// check whether number_bits is >= 0
	assert(number_bits >= 0);
	return number_bits;
}


// getter for q_matrix
vector<vector <int> > QUBO::getQMatrix() {
	// check the dimention of q_matrix
	assert(q_matrix.size() == number_bits);
	return q_matrix;
}


// getter for constant
int QUBO::getConstant() {
	return constant;
}


// getter for penalty
int QUBO::getPenalty() {
	// check whether penalty is > 0
	assert(penalty > 0);
	return penalty;
}


// read QUBO files and store information in the members
void QUBO::readQUBO(int number_bits_, int ID_) {
	cout << "Reading QUBO files #" << ID_ << " now!" << endl;
	
	if (number_bits != number_bits_) {
		cout << "set number_bits when reading QUBO files" << endl;
		number_bits = number_bits_;
	}

	// determine the filename
	string filename_head("qubo_");
	stringstream sstreamNB, sstreamID;
	sstreamNB << number_bits_;
	sstreamID << ID_;
	string str_NB = sstreamNB.str(); // NB: number_bits
	string str_ID = sstreamID.str();
	string filename_mid("_");
	string filename_tail(".txt");

	string filename;
	filename = filename_head + str_NB + filename_mid + \
			   str_ID + filename_tail;
	cout << "filename: " << filename << endl;

	// read file
	ifstream infile; 
   	infile.open(filename); 

   	// check whether infile is open
   	assert(infile.is_open());

   	// read the first line for NB, CO, PE, and ID
   	string line;
   	getline(infile, line);
   	stringstream ssline(line);
   	string NB;      // NB: number_bits
   	string CO;      // CO: constant
   	string PE;      // PE: penalty
   	string ID;
   	ssline >> NB;
   	ssline >> CO;
   	ssline >> PE;
   	ssline >> ID;
   	assert(stoi(NB) == number_bits_);
   	assert(stoi(ID) == ID_);

   	// directly assign CO and PE
   	constant = stoi(CO);
   	penalty = stoi(PE);

   	// read the matrix: NB nows and NB columns
   	// clear the q_matrix at first
   	q_matrix.clear();
    while(getline(infile, line)) {
        stringstream ssline(line);
        string pos;
        vector<int> q_matrix_row;
        while (ssline >> pos) {
        	q_matrix_row.push_back(stoi(pos));
        }

        // check the length of a row of q_matrix
        assert(q_matrix_row.size() == number_bits_);
        q_matrix.push_back(q_matrix_row);
    }

    // check the number of rows of q_matrix
    cout << "q_matrix.size() is: " << q_matrix.size() << endl;
    assert(q_matrix.size() == number_bits_);

   	// close the file
    infile.close();

}


// print QUBO
void QUBO::printQUBO() {
	// print the number of bits
	cout << "The number of bits is: " << number_bits << endl;
	assert(number_bits >= 0);

	// print the constant
	cout << "The constant is: " << constant << endl;

	// print the penalty
	cout << "The penalty is: " << penalty << endl;

	// print the q_matrix by rows
	cout << "The QUBO matrix is: " << endl;
	if (number_bits > 0) {
		for (int i=0; i<number_bits; i++) {
			for (int j=0; j<number_bits; j++) {
				cout << q_matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
}