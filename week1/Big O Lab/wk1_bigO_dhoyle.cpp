/*
    Dante Hoyle
    wk1_bigO_dhoyle.cpp
    March 29th, 2022

    <summary>
*/

#include <iostream>
#include <cstdlib>          // For rand, srand, and NULL
#include <ctime>            // For time to seed srand
#include <chrono>           // To track how long 
using namespace std;

// Constants used for hard coding the array size
const int SMALL = 10;
const int BIG = 1000;

/* Functions created for assignment */

// Will take O(log(n)) time to complete scaling with the length
// of the array passed as an argument
void bigOLogN(int[], int[]);
// Will take O(n^2) time to complete scaling with the length of the array
// passed as an argument
void bigONSquared(int[], int[], int[], int[]);

// Bubble sort algorithm borrowed from the internet
// source: https://www.geeksforgeeks.org/recursive-bubble-sort/
void bubbleSort(int[], int);

// Assumes array is sorted; returns true if function has no repeating numbers;
bool hasRepeats(int[], int);

void fillArrays(int[], int[], int[], int[]);

int binarySearch(int ar[], int start, int end, int target);

int main()
{
    int arrayBig[BIG],
        arraySmall[SMALL],
        arrayBigUnique[BIG],
        arraySmallUnique[SMALL];

    // seed random number generator with time program begins
    srand(time(NULL));

    fillArrays(arraySmall, arraySmallUnique, arrayBig, arrayBigUnique);

    bigOLogN(arraySmallUnique, arrayBigUnique);

    bigONSquared(arraySmall, arraySmallUnique, arrayBig, arrayBigUnique);

    return 0;
}

void bigOLogN(int arraySmallUnique[], int arrayBigUnique[])
{

    // Time points used to keep track of how long operations take
    chrono::steady_clock::time_point start, end;

    cout << "O(log n) results:\n";

    /* Small Array*/

    // Records start time
    start = chrono::steady_clock::now();
    // Performs binary search which takes O(log n) time to complete
    binarySearch(arraySmallUnique, 0, SMALL - 1, rand() % 10);
    // Records end time
    end = chrono::steady_clock::now();

    // Output the results
    cout << "Small list with unique values: " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " (ns)\n";

    /* Large Array */
    // Records start time
    start = chrono::steady_clock::now();
    binarySearch(arrayBigUnique, 0, BIG - 1, 10);
    // Records end time
    end = chrono::steady_clock::now();

    // Output results
    cout << "Big list with repeats: " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " (ns)\n\n";

    return;
}

void bigONSquared(int arraySmall[], int arraySmallUnique[], int arrayBig[], int arrayBigUnique[])
{
    // Time points used to keep track of how long operations take
    chrono::steady_clock::time_point start, end;

    cout << "O(n^2) results: \n";

    /* Small Array*/
    start = chrono::steady_clock::now();
    // Accesses different parts of the small array to simulate performing a calculation
    for (int i = 0; i < SMALL; i++)
        for (int j = 0; j < SMALL; j++)
            arraySmall[(i + j)/2];
    end = chrono::steady_clock::now();

    cout << "Small array no repeats: " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " (ns)\n";

    /* Small Array No Repeats*/
    start = chrono::steady_clock::now();
    for (int i = 0; i < SMALL; i++)
        for (int j = 0; j < SMALL; j++)
            arraySmallUnique[(i + j) / 2];
    end = chrono::steady_clock::now();

    cout << "Small array with unique values: " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " (ns)\n";

     /* Big Array*/
    start = chrono::steady_clock::now();
    // Accesses different parts of the small array to simulate performing a calculation
    for (int i = 0; i < BIG; i++)
        for (int j = 0; j < BIG; j++)
            arrayBig[(i + j)/2];
    end = chrono::steady_clock::now();

    cout << "Big array no repeats: " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " (ns)\n";

    /* Small Array No Repeats*/
    start = chrono::steady_clock::now();
    for (int i = 0; i < BIG; i++)
        for (int j = 0; j < BIG; j++)
            arraySmallUnique[(i + j) / 2];
    end = chrono::steady_clock::now();

    cout << "Big array with unique values: " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " (ns)\n";
    return;
}

void bubbleSort(int ar[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (ar[j] > ar[j + 1])
            {
                // swap ar[j] and ar[j+1]
                int tmp = ar[j];
                ar[j] = ar[j + 1];
                ar[j + 1] = tmp;
            }
        }
    }
}

bool hasRepeats(int ar[], int size)
{
    // since the function can assumes ar is sorted, this only has to check that
    // no number repeats with it's neighbors

    bool repeats = false;
    int tmp = ar[0];

    for (int i = 1; i < size; i++)
    {
        if (ar[i] == tmp)
        {
            repeats = true;
            break;
        }

        tmp = ar[i];
    }
    return repeats;
}

void fillArrays(int arraySmall[], int arraySmallUnique[], int arrayBig[], int arrayBigUnique[])
{
    // fill small array with random numbers between 0-1499
    for (int i = 0; i < SMALL; i++)
        arraySmall[i] = rand() % 1500;
    // fill large array with random numbers between 0-1499999
    for (int i = 0; i < BIG; i++)
        arrayBig[i] = rand() % 150000;

    // fill small array with unique numbers between 0 - 1499, probably overkill
    do 
    {
        for (int i = 0; i < SMALL; i++)
            arraySmallUnique[i] = rand() % 150000;
        bubbleSort(arraySmallUnique, SMALL);
    } while (!hasRepeats(arraySmallUnique, SMALL));

    // fill large array with unique numbers between 0 - 1,499,999
    do
    {
        for (int i = 0; i < BIG; i++)
            arrayBigUnique[i] = rand() % 1500000000;
        bubbleSort(arrayBigUnique, BIG);
    } while (!hasRepeats(arrayBigUnique, BIG));

    // sort the arrays
    bubbleSort(arraySmall, SMALL);
    bubbleSort(arrayBig, BIG);
}

int binarySearch(int ar[], int start, int end, int target)
{
    if (end >= 1)
    {
        int mid = start + ((end - start) / 2);

        if (ar[mid] == target)
            return mid;

        if (ar[mid] > target)
            return binarySearch(ar, start, mid - 1, target);

        return binarySearch(ar, mid + 1, end, target);
    }
    return -1;
}