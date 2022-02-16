#include <iostream>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "QUBO.h"
#include "SOL.h"
#include "LS.h"

using namespace std;




// constructor with a parameter of number_bits
LS::LS(QUBO qubo_, SOL sol_init_) {
	// check whether the dimensions match
	assert(qubo_.getNumberBits() == sol_init_.getN());
	qubo = qubo_;
	sol_init = sol_init_;
}


// getter for QUBO
QUBO LS::getQubo() {
	assert(qubo.getNumberBits() > 0);
	return qubo;
}


// getter for SOL
SOL LS::getSolInit() {
	assert(sol_init.getN() > 0);
	return sol_init;
}


// calculate the value of a sol.x
// considering the qubo.constant
int LS::calculateValue(vector<int> x_) {
	// initialization
	int n = x_.size();
	vector<vector<int>> q_matrix = qubo.getQMatrix();
	assert(qubo.getNumberBits() == n);
	int v = 0;

	// vector-matrix-vector multiplication
	// x^T * Q * x
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			v += x_[i] * q_matrix[i][j] * x_[j];
		}
	}

	return v + qubo.getConstant();
}


// check whether a solution is a local optima for the QUBO
bool LS::checkLocalOpt(SOL sol) {
	// check whether the dimensions match
	int n = sol.getN();
	assert(qubo.getNumberBits() == n);

	// evaluate local optima by calculating delta_v after an 1-bit flip
	vector<vector<int>> q_matrix = qubo.getQMatrix();
	vector<int> x = sol.getX();
	int delta_v = 0;

	for (int i=0; i<n; i++) {
		// for each bit
		for (int j=0; j<n; j++) {
			delta_v += x[j] * q_matrix[i][j];
			delta_v += x[j] * q_matrix[j][i];
		}
		delta_v -= q_matrix[i][i];
		delta_v *= (1 - 2*x[i]);
		if (delta_v < 0) {
			cout << "The solution is not local opt as bit #" \
			<< i << " fails the evaluation !" << endl;
			return false;
		}
	}
	return true;
}


// local search algorithm
// consider all 1-bit flips
vector<vector<int>> LS::localSearchAll(int max_iters) {
	cout << "Local search with ALL 1-bit flips is running ************" << endl;
	
	cout << "The max number of iterations is: " << max_iters << endl;
	
	// set the random seed
	time_t t;
	srand((unsigned) time(&t));

	// algo initialization
	int n = sol_init.getN();
	vector<vector<int>> q_matrix = qubo.getQMatrix();
	vector<int> x_current = sol_init.getX();
	int v_current = sol_init.getV();
	int constant = qubo.getConstant();
	int iter = 0;

	// x_list stores all the x until a local optima
	vector<vector<int>> x_list;
	x_list.push_back(x_current);

	// v_list stores all the v until a local optima
	vector<int> v_list;
	v_list.push_back(v_current);

	// flip_selected is the flip index accepted at each step
	int flip_selected;
	
	// the change of v after the flip
	int delta_v = 0;

	// flip_list stores all the bit index for flip
	vector<int> flip_list;

	// delta_v_list stores all the delta_v for each flip
	vector<int> delta_v_list;


	while (iter < max_iters) {
		// print x_current for comparison in debugging!
		// for (int i=0; i<n; i++) {
		// 	cout << x_current[i] << " ";
		// }
		// cout << endl;

		// for each bit flip
		for (int i=0; i<n; i++) {
			// calculate delta_v
			for (int j=0; j<n; j++) {
				delta_v += x_current[j] * q_matrix[i][j];
				delta_v += x_current[j] * q_matrix[j][i];
			}
			delta_v -= q_matrix[i][i];
			delta_v *= (1 - 2*x_current[i]);
			// evaluate delta_v
			if (delta_v <= 0) {
				flip_list.push_back(i);
				delta_v_list.push_back(delta_v);
			}
			delta_v = 0;
		}

		// update the iteration number
		iter ++;

		// select a beneficial flip to accept, if any
		// cout << "The size of flip_list is: " << flip_list.size() << endl;
		assert(flip_list.size() == delta_v_list.size());
		if (flip_list.size() > 0) {
			// randomly accept a flip
			int random_index = rand() % flip_list.size();
			flip_selected = flip_list[random_index];
			// cout << "The flip_selected is: " << flip_selected << endl;

			// update v_current and x_current
			v_current += delta_v_list[random_index];
			// cout << "The new v_current is: " << v_current << endl;
			// cout << "Former: " << x_current[flip_selected] << endl;
			x_current[flip_selected] = 1 - x_current[flip_selected];
			// cout << "Latter: " << x_current[flip_selected] << endl;

			// store x_current and v_current
			x_list.push_back(x_current);
			v_list.push_back(v_current + constant);

			// clear flip_list and delta_v_list
			flip_list.clear();
			delta_v_list.clear();
			// cout << "The size of cleaned flip_list: " << flip_list.size() << endl;

		} else {
			cout << "Reach local optima after iteration #" << iter << endl;
			cout << "The v_list is: " << endl;
			for (int i=0; i<v_list.size(); i++) {
				cout << v_list[i] << " ";
			}
			cout << endl;
			break;
		}
		
	}

	cout << "The final v_current + constant is: " << \
	v_current + constant << endl;
	return x_list;

}


// local search algorithm
// consider one 1-bit flips
// accept a worse flip under some probability
vector<vector<int>> LS::localSearchOne(int max_iters) {
	cout << "Local search with ONE 1-bit flips is running ************" << endl;
	
	cout << "The max number of iterations is: " << max_iters << endl;
	
	// set the random seed
	time_t t;
	srand((unsigned) time(&t));
	
	// algo initialization
	int n = sol_init.getN();
	vector<vector<int>> q_matrix = qubo.getQMatrix();
	vector<int> x_current = sol_init.getX();
	int v_current = sol_init.getV();
	int constant = qubo.getConstant();
	int iter = 0;

	// x_list stores all the x until a local optima
	vector<vector<int>> x_list;
	x_list.push_back(x_current);

	// v_list stores all the v until a local optima
	vector<int> v_list;
	v_list.push_back(v_current);

	// flip_selected is the flip index accepted at each step
	int flip_selected;
	
	// the change of v after the flip
	int delta_v = 0;
	
	// the probability of accept the flip or not
	int probability;

	while (iter < max_iters) {
		// print x_current for comparison in debugging!
		// for (int i=0; i<n; i++) {
		// 	cout << x_current[i] << " ";
		// }
		// cout << endl;
		
		// randomly select a bit to flip
		flip_selected = rand() % n;
		
		// calculate delta_v
		for (int j=0; j<n; j++) {
			delta_v += x_current[j] * q_matrix[flip_selected][j];
			delta_v += x_current[j] * q_matrix[j][flip_selected];
		}
		delta_v -= q_matrix[flip_selected][flip_selected];
		delta_v *= (1 - 2*x_current[flip_selected]);
		
		// evaluate delta_v
		// if delta_v <= 0, accept the flip
		if (delta_v <= 0) {
			// update v_current and x_current
			v_current += delta_v;
			// cout << "The new v_current is: " << v_current << endl;
			// cout << "Former: " << x_current[flip_selected] << endl;
			x_current[flip_selected] = 1 - x_current[flip_selected];
			// cout << "Latter: " << x_current[flip_selected] << endl;

			// store x_current and v_current
			x_list.push_back(x_current);
			v_list.push_back(v_current + constant);
		} else {
			probability = rand() % 100;
			if (delta_v < probability) {
				// update v_current and x_current
				v_current += delta_v;
				// cout << "The new v_current is: " << v_current << endl;
				// cout << "Former: " << x_current[flip_selected] << endl;
				x_current[flip_selected] = 1 - x_current[flip_selected];
				// cout << "Latter: " << x_current[flip_selected] << endl;

				// store x_current and v_current
				x_list.push_back(x_current);
				v_list.push_back(v_current + constant);
			}
		}
		
		// reset delta_v to 0
		delta_v = 0;

		// update the iteration number
		iter ++;
		
	}

	cout << "The final v_current + constant is: " << \
	v_current + constant << endl;
	return x_list;
}
