#include <iostream>
#include <chrono>

using namespace std;

int const RAND_UPPER_BOUND = 10000;

int UserInput();
void InvalidInputEvent();

void InsertionSort(int arrayToSort[], int sizeOfArray);
void PopulateArray(int generatedArray[], int sizeOfArray);
void OuputArray(int generatedArray[], int sizeOfArray);


int main()
{
    chrono::steady_clock::time_point timerStart, timerEnd;
    chrono::duration<double> elapsedTime;

    int arraySize = UserInput();

    // Random seed based on time since epoch
    srand(chrono::steady_clock::now().time_since_epoch().count());

    int* generatedArray = new int[arraySize];
    PopulateArray(generatedArray, arraySize);

    cout << "\nOriginal Array Layout\n";
    OuputArray(generatedArray, arraySize);

    // Time function in seconds
    timerStart = chrono::steady_clock::now();
    InsertionSort(generatedArray, arraySize);
    timerEnd = chrono::steady_clock::now();

    cout << "\nSorted Array Layout\n";
    OuputArray(generatedArray, arraySize);

    elapsedTime = timerEnd - timerStart;
    cout << "\nSorting Elapsed Time: " << elapsedTime.count() << " Seconds!\n";

    // Array Cleanup
    delete[] generatedArray;
    generatedArray = nullptr;
}

int UserInput()
{
    int userGivenSize;
    while (true)
    {
        cout << "Choose size of the array to sort: ";
        cin >> userGivenSize;

        if (!cin.fail()) break;
        InvalidInputEvent();
    }
    return userGivenSize;
}

void InvalidInputEvent()
{
    cin.clear();
    cin.ignore(99999, '\n');
    system("cls");
    cout << "Invalid Input!" << endl;
}

void InsertionSort(int arrayToSort[], int sizeOfArray)
{
    int valToSort, comparingIndex;
    for (int i = 1; i < sizeOfArray; i++)
    {
        valToSort = arrayToSort[i];
        comparingIndex = i - 1;

        // Keep comparing while sorting value is in wrong space
        while (arrayToSort[comparingIndex] > valToSort && comparingIndex >= 0)
        {
            // Push left value into right value
            arrayToSort[comparingIndex + 1] = arrayToSort[comparingIndex];
            comparingIndex -= 1;
        }

        arrayToSort[comparingIndex + 1] = valToSort;
    }
}

void PopulateArray(int generatedArray[], int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        // Fill array with random numbers between 1 and 1000
        generatedArray[i] = rand() % RAND_UPPER_BOUND + 1;
    }
}

void OuputArray(int generatedArray[], int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        cout << generatedArray[i] << " ";
    }
    cout << endl;
}