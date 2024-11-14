// THIS IS A WIP FOR ASAH3
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  
#include <chrono>   
#include <array>

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
int partition(int [], int, int);
void quickSort(int[], int, int);


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

/***********************************************************
*      QUICK SORT UTILIZES THE TWO FOLLOWING FUNCTIONS 
************************************************************
* SOURCE FOR THIS ALGORITHM:
* https://www.geeksforgeeks.org/cpp-program-for-quicksort/
* 
* Name: partition
* Parameters: int [], int, int
* Returns: int
* 	This function performs the actual swapping found within 
* a QuickSort Algorithm. It will loop through the array, 
* swapping the leftmost array values with any found to be
* LESS THAN the current pivot (which is the last array member).
*	Once finished looping, it will then swap the pivot value 
* to its correct location in the array
*	Finally, it will return the index in which pivot has been
* placed, allowing the recursive QuickSort to then target a 
* different slice of the array. 
***********************************************************/
int partition(int arr[], int low, int high) {

    // Selecting last element as the pivot
    int pivot = arr[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

	// Loop traverses array, comparing each value to pivot
	// --If a value is found to be LESS THAN pivot, it is swapped with arr[i],
	// 	 which is an incremented counter at the BEGININNING of the array
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // Put pivot to its position after finding each value LESS than pivot
    swap(arr[i + 1], arr[high]);

    // Return the point of partition
    return (i + 1);
}
/************************************************************
* SOURCE FOR THIS ALGORITHM:
* https://www.geeksforgeeks.org/cpp-program-for-quicksort/
* 
* Name: quickSort
* Parameters: int [], int, int
* Returns: void
* 	This is a recursive function that will select ever-
* shrinking slices of the array to be sorted through the
* partition() function. 
* 	quickSort() passes an array to partition(), which then 
* returns a more sorted array, as well as the correct index
* of the pivot (original parameter: 'high'). 
* 	Afterwards, quickSort is recursively applied to the 
* slices of the array on either side of the new pivot index
***********************************************************/
void quickSort(int arr[], int low, int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(arr, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

