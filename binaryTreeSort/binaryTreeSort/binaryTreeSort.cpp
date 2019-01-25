// binaryTreeSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc != 5) {
		for (int x = 0; x < argc; x++) {
			cout << argv[x] << endl;
		}
		return -1;
	}
	else {
		default_random_engine gen;
		uniform_int_distribution<short signed int> distr(SHRT_MIN, SHRT_MAX);
		fstream randomFile = fstream(argv[1], fstream::out);
		fstream gtl = fstream(argv[2], fstream::out);
		fstream ltg = fstream(argv[3], fstream::out);
		stack<short signed int>* gtlstack;
		stack<short signed int>* ltgstack;

		
		signed short int v = distr(gen);
		RBtree master = RBtree(v);
		//Generate random numbers for the tree, capture numbers into log file for checking
		int len = stoi(argv[4]);
		for (int x = 1; x < len; x++) {
			v = distr(gen);
			cout << v << endl;
			randomFile << v << endl;
			master.insert(v);
		}
		ltgstack = master.genStack(true);
		gtlstack = master.genStack(false);
		randomFile.close();

		//output to files
		while (!gtlstack->empty()) {
			gtl << gtlstack->top() << endl;
			gtlstack->pop();

			ltg << ltgstack->top() << endl;
			ltgstack->pop();
		}
		gtl.close();
		ltg.close();
	}
	return 1;
}




