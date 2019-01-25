#include "stdafx.h"
#include "CppUnitTest.h"
#include "../binaryTreeSort/pch.h"
#include "../binaryTreeSort/tree.h"
#include "../binaryTreeSort/tree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SortingTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(BasicOneHundredRandomLTG)
		{
			/*Test 100 Random numbers in the full signed short range. Uses
			the genStack function to recieve an observable in order stack
			of Least to Greatest (least being the top of the stack)*/
			default_random_engine gen;
			uniform_int_distribution<signed short int> distr(SHRT_MIN, SHRT_MAX);
			RBtree testTree = RBtree(distr(gen));
			stack<signed short int>* testStack;

			//Generate random numbers and insert into tree, then build the stack
			for (int x = 1; x < 100; x++) {
				testTree.insert(distr(gen));
			}
			testStack = testTree.genStack(true);

			//Check least to greatest order by observing that every element is greater than the last and the size is correct
			signed short int last = testStack->top();
			testStack->pop();
			int numPopped = 1;

			while (!testStack->empty()) {
				Assert::IsTrue((testStack->top() > last));
				last = testStack->top();
				testStack->pop();
				numPopped++;
			}
			Assert::AreEqual(numPopped, 100);
		}

		TEST_METHOD(BasicOneHundredRandomGTL) {
			/*Test 100 Random numbers in the full signed short range. Uses
			the genStack function to recieve an observable in order stack
			of Greatest to Least (greatest being the top of the stack)*/
			default_random_engine gen;
			uniform_int_distribution<signed short int> distr(SHRT_MIN, SHRT_MAX);
			RBtree testTree = RBtree(distr(gen));
			stack<signed short int>* testStack;

			//Generate random numbers and insert into tree, then build the stack
			for (int x = 1; x < 100; x++) {
				testTree.insert(distr(gen));
			}
			testStack = testTree.genStack(false);

			//Check greatest order by observing that every element is less than the last and the size is correct
			signed short int last = testStack->top();
			testStack->pop();
			int numPopped = 1;

			while (!testStack->empty()) {
				Assert::IsTrue((testStack->top() < last));
				last = testStack->top();
				testStack->pop();
				numPopped++;
			}
			Assert::AreEqual(numPopped, 100);
		} 

		TEST_METHOD(inOrderInsertionLTGNodes) {
			/*A 'worst case' scenrio where all the 100 inputs are pre-ordered at
			a randomly selected start point. Tests 100 nodes are created for 100
			unique numbers*/
			default_random_engine gen;
			uniform_int_distribution<signed short int> distr(SHRT_MIN, SHRT_MAX - 100);
			signed short start = distr(gen);

			RBtree testTree = RBtree(start);
			for (signed short int x = 1; x < 100; x++) {
				start++;
				testTree.insert(start);
			}
			Assert::AreEqual(testTree.getNodes(), (signed short int)100);
		}

		TEST_METHOD(inOrderInsertionLTGsort) {
			/*A 'worst case' scenrio where all the 100 inputs are pre-ordered at
			a randomly selected start point. Tests that the numbers are still 
			given sorted properly and comparing the runtime to the random number
			insertion tests.*/
			stack<signed short int>* testStack;
			default_random_engine gen;
			uniform_int_distribution<signed short int> distr(SHRT_MIN, SHRT_MAX - 100);

			signed short start = distr(gen);

			RBtree testTree = RBtree(start);
			for (signed short int x = 1; x < 100; x++) {
				start++;
				testTree.insert(start);
			}
			testStack = testTree.genStack(true);
			signed short int temp = testStack->top();
			int popped = 1;
			testStack->pop();
			while (!testStack->empty()) {
				Assert::IsTrue((temp < testStack->top()));
				temp = testStack->top();
				testStack->pop();
				popped++;
			}

		}

		TEST_METHOD(inOrderInsertionLTGdescend) {
			/*Worst case scenario where all inputs are 
			are preordered in a descending fashion from
			a random start point. Used to test that the
			numbers will still be sorted and for comparing
			runtime against the random insert tests.*/
			stack<signed short int>* testStack;
			default_random_engine gen;
			uniform_int_distribution<signed short int> distr(SHRT_MIN + 100, SHRT_MAX);

			signed short start = distr(gen);

			RBtree testTree = RBtree(start);
			for (signed short int x = 1; x < 100; x++) {
				start--;
				testTree.insert(start);
			}
			testStack = testTree.genStack(true);
			signed short int temp = testStack->top();
			int popped = 1;
			testStack->pop();
			
			while (!testStack->empty()) {
				Assert::IsTrue((temp < testStack->top()));
				temp = testStack->top();
				testStack->pop();
				popped++;
			}
		}
	};
}