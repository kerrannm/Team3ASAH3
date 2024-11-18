/*  Kerry Manolagas
/   Mervyn Harp
/-Program will perform a sorting algorithm on a data set from a file
/ (File declared as global const 'filename'). After the
/ sorting algorithm has completed, the time elapsed while performing the
/ sort will be displayed to the console in seconds, microseconds, and
/ nanoseconds. These values will only display fully elapsed units of
/ each time - fractional values of seconds and microseconds can be
/ inferred by looking at smaller units of time displayed in the
/ results.
/
/ INSTRUCTIONS FOR RUNNING: This is one of six .cpps associated
/ with this project! Only one main() will run at a time when
/ using Visual Studio. To ensure the succesful compilation
/ of code, follow these steps:
/
/ 1. Go to the Solution Explorer (typically on righthand side)
/ 2. Show all Files (icon should look like a few overlapping rectangles)
/ 3. Once all of the associated with the .cpp are shown, right click
/ to either include or exclude a .cpp from executing. Only ONE
/ .cpp should be included at a time - if a file is
/ included, the icon to the left of its name should appear as
/ two purple plus signs. If a file is excluded, the icon to the
/ the left of its name will appear as a rectangle with a red
/ circle with a white minus sign inside of it.
/ 4. Repeat the process of inclusion/exclusion for each file
/ that you wish to run.                                          */

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
timingResult timeAlgo(int[]);
void printResults(timingResult&);
void readData(int[]);
int partition(int[], int, int);
void quickSortIterative(int[], int, int);


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

    infile.close();
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
    quickSortIterative(arr, 0, SIZE - 1);  //   <--------   ALGORITHM HERE  !!!!!

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
    cout << "Time elapsed in seconds:      " << setw(12) << right << times.sec << " seconds\n";
    cout << "------------------------------------------------------------------------------\n";
    cout << "Time elapsed in microseconds: " << setw(12) << right << times.microSec << " microseconds\n";
    cout << "------------------------------------------------------------------------------\n";
    cout << "Time elapsed in nanoseconds:  " << setw(12) << right << times.nanoSec << " nanoseconds\n";
    cout << "------------------------------------------------------------------------------\n";
}

/***********************************************************
*      QUICK SORT UTILIZES THE TWO FOLLOWING FUNCTIONS
*************************************************************
* SOURCE FOR THIS ALGORITHM:
* https://www.geeksforgeeks.org/iterative-quick-sort/
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
int partition(int arr[], int l, int h)
{
    //int pivotIndex = medianOfThree(arr, l, h);
    int x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[h]);
    return (i + 1);
}

/************************************************************
* SOURCE FOR THIS ALGORITHM:
* https://www.geeksforgeeks.org/iterative-quick-sort/
*
* Name: quickSort
* Parameters: int [], int, int
* Returns: void
* 	This is a iterative version of QuickSort that allows
* for sorting or larger data sets without fear of the
* function-call exceeding the limits of the Stack.
*   It accomplishes this by creating a dynamic array to be
* used as a temporary stack that will hold the sorted
* values to be then added back to the main array.
***********************************************************/
void quickSortIterative(int arr[], int l, int h)
{
    // Create an auxiliary stack 
    int* tempStack = new int[h - l + 1];

    // initialize top of stack 
    int top = -1;

    // push initial values of l and h to stack 
    tempStack[++top] = l;
    tempStack[++top] = h;

    // Keep popping from stack while is not empty 
    while (top >= 0) {
        // Pop h and l 
        h = tempStack[top--];
        l = tempStack[top--];

        // Set pivot element at its correct position 
        // in sorted array 
        int p = partition(arr, l, h);

        // If there are elements on left side of pivot, 
        // then push left side to stack 
        if (p - 1 > l) {
            tempStack[++top] = l;
            tempStack[++top] = p - 1;
        }

        // If there are elements on right side of pivot, 
        // then push right side to stack 
        if (p + 1 < h) {
            tempStack[++top] = p + 1;
            tempStack[++top] = h;
        }
    }
}