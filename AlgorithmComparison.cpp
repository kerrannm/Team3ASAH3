// THIS IS A WIP FOR ASAH3
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  
#include <chrono>   
using namespace std;

//establish size for array
const int SIZE = 65000;

/*************************************
* struct timingResult:
* the timingResult struct is comprised of
* three long longs, each representing
* a different duration: seconds, 
* microseconds, and nanoseconds.
* a struct is used so that the timing
* functions will be able to return all
* of these values at once.
**************************************/
struct timingResult
{
	long long sec;
	long long microSec;
	long long nanoSec;
};

//fx prototypes
timingResult timeAlgo(ifstream&);
void insertionSort(int []);


int main()
{

	// thoughts for variable names
	
	//timingResult insDesc, insAsc, insRand;
	//timingResult quickDesc, quickAsc, quickRand;

	//ifstream infile;
	//ofstream outfile;

}

//I'm thinking that we can put another input parameter (int?) for an if/else that would indicate whether to choose
// insertion sort or quick sort?
timingResult timeAlgo(ifstream& infile)
{
	//i to iterate the index
	//create array to hold numbers from file
	int i = 0;
	int DUMMY[SIZE];

	//while the file has not ended, add data to an
	//index and then iterate
	while (!infile.eof())
	{
		infile >> DUMMY[i];
		i++;
	}

	//start timer, call sorting algorithm, end timer
	auto start = std::chrono::steady_clock::now();
	insertionSort(DUMMY);
	auto end = std::chrono::steady_clock::now(); 

	//capture the duration in the form of seconds, microseconds, and nanoseconds
	auto sc = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	// create a timingResult and set its values to the duration
	timingResult results;
	results.sec = sc.count();
	results.microSec = us.count();
	results.nanoSec = ns.count();

	return results;
}

/***********************************************************
* SOURCE FOR THIS ALGORITHM:
* https://www.geeksforgeeks.org/insertion-sort-algorithm/
* 
* Name: insertionSort
* Parameters: int []
* Returns: N/A
* This function will pass in an array and sort its values
* with the insertion sort algorithm.SIZE
***********************************************************/
void insertionSort(int arr[])
{
	for (int i = 1; i < SIZE; ++i) {
		int key = arr[i];
		int j = i - 1;

		/* Move elements of arr[0..i-1], that are
		   greater than key, to one position ahead
		   of their current position */
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
