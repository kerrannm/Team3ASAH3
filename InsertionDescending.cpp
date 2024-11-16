/*  Kerry Manolagas
	Mervyn Harp
	-Program will perform a sorting algorithm on a data set from a file
	(File declared as global const 'filename')
	-Before compiling, ensure all data files are within the same folder as this
	source file                                                              */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  
#include <chrono>   
#include <array>

using namespace std;

//establish size for array
const int SIZE = 65000;
const string filename = "DescendingOrder.txt";
const string algType = "Insertion Sort";

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
	double sec;
	long long microSec;
	long long nanoSec;
};

//fx prototypes
timingResult timeAlgo(int[]);
void insertionSort(int[]);
void printResults(timingResult& times);
void readData(int arr[]);


int main()
{


	//Initialize array
	int DUMMY[SIZE];

	//Populate with data from file
	readData(DUMMY);

	//Performs timing of algorithm (quickSort call is inside timeAlgo())
	timingResult results = timeAlgo(DUMMY);

	//Displays the timing results 
	printResults(results);




}

/************************************************************
* Name: readData
* Parameters: string, int []
* Returns: void
* 	This function reads the data from the file into an array
* to then be utilzied by the sorting algorithm.
***********************************************************/
void readData(int arr[])
{
	ifstream infile;
	infile.open("DescendingOrder.txt");

	//i to iterate the index
	int i = 0;

	//while the file has not ended, add data to an
	//index and then iterate
	while (!infile.eof() && i < SIZE)
	{
		infile >> arr[i];
		i++;
	}

	infile.close();
}
timingResult timeAlgo(int arr[])
{
	//Start Timer
	auto start = std::chrono::steady_clock::now();

	//Perform algorithm
	insertionSort(arr);  //   <--------   ALGORITHM HERE  !!!!!

	//End Timer
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
/************************************************************
* Name: printResults
* Parameters: timingResult
* Returns: void
* 	This function outputs the recorded timing from the
* algorithm into the terminal
***********************************************************/
void printResults(timingResult& times)
{

	cout << "Time Elapsed While Sorting " << filename << " with " << algType << ":\n";
	cout << "------------------------------------------------------------------------------\n";
	cout << "Time elapsed in seconds: " << setw(8) << right << times.sec << " seconds\n";
	cout << "------------------------------------------------------------------------------\n";
	cout << "Time elapsed in microseconds: " << setw(5) << right << times.microSec << " microseconds\n";
	cout << "------------------------------------------------------------------------------\n";
	cout << "Time elapsed in nanoseconds: " << setw(9) << right << times.nanoSec << " nanoseconds\n";
	cout << "------------------------------------------------------------------------------\n";

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