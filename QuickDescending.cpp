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
const string algType = "Quick Sort";

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
timingResult timeAlgo(int []);
void printResults(timingResult &);
void readData(int []);
int medianOfThree(int [], int, int);
int partition(int [], int, int);
void quickSort(int [], int, int);


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
    infile.open(filename);

    //i to iterate the index
	int i = 0;

	//while the file has not ended, add data to an
	//index and then iterate
	while (!infile.eof())
	{
		infile >> arr[i];
		i++;
	}
}

/************************************************************
* Name: timeAlgo
* Parameters: int []
* Returns: timingResult
* 	This function performs the timing of the algorithm. 
* Results are then saved and returned as timingResult struct
***********************************************************/
timingResult timeAlgo(int arr[])
{
	//Start Timer
	auto start = std::chrono::steady_clock::now();

    //Perform algorithm
	quickSort(arr, 0, SIZE - 1);  //<--------       ALGORITHM HERE  !!!!!

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
void printResults(timingResult &times)
{
    cout << filename << "   " << algType << '\n';
    cout << setw(10) << right << times.sec << " seconds\n";
    cout << setw(10) << right << times.microSec << " microseconds\n";
    cout << setw(10) << right << times.nanoSec << " nanoseconds";
}

/***********************************************************
*      QUICK SORT UTILIZES THE THREE FOLLOWING FUNCTIONS 
************************************************************
* Name: medianofThree
* Parameters: int [], int, int
* Returns: int
* 	This function is meant to find a different pivot point
* rather than always selecting the final index. This helps 
* to avoid any worst-case scenarios for time complexity, as 
* well as avoiding segmentation faults when sorting large 
* slices of the array. 
*   This was added after reaching segmentation faults when
* using QuickSort at times of worst-complexity
***********************************************************/
int medianOfThree(int arr[], int low, int high) 
{
    int mid = low + (high - low) / 2;

    //Perform swaps between low, high, and mid to their respective spots
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);

    return mid; // Return the pivot index
}

/************************************************************
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
    int pivotIndex = medianOfThree(arr, low, high);
    int pivot = arr[pivotIndex];
    swap(arr[pivotIndex], arr[high]);  // Move pivot to the end

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// /************************************************************
// * SOURCE FOR THIS ALGORITHM:
// * https://www.geeksforgeeks.org/cpp-program-for-quicksort/
// * 
// * Name: quickSort
// * Parameters: int [], int, int
// * Returns: void
// * 	This is a recursive function that will select ever-
// * shrinking slices of the array to be sorted through the
// * partition() function. 
// * 	quickSort() passes an array to partition(), which then 
// * returns a more sorted array, as well as the correct index
// * of the pivot (original parameter: 'high'). 
// * 	Afterwards, quickSort is recursively applied to the 
// * slices of the array on either side of the new pivot index
// ***********************************************************/
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Get the partition index

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}