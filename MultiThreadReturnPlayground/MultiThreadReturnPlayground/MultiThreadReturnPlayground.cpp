#include <iostream>
#include <thread>

using namespace std;

int const UPPER_BOUND = 100000;

bool shouldStop = false;

void ConstantStringConcat(string word, int* toReturnStringSize);
void getPlayerInput();

int main()
{
    int currentWordSize;
    thread GetSizeThread(ConstantStringConcat, "foo", &currentWordSize);

    getPlayerInput();

    GetSizeThread.join();
    cout << currentWordSize;
}

void ConstantStringConcat(string word, int* toReturnStringSize)
{
    // Continuously concat word and get size
    string indivWord = word;
    while (!shouldStop)
    {
        word += indivWord;
        // If reaching upper bound reset word
        if (UPPER_BOUND < word.size()) word = "";
    }
    *toReturnStringSize = word.size();
}

// Wait until player inputs "Q" to set stop
void getPlayerInput()
{
    char input = ' ';
    while (tolower(input) != 'q')
    {
        system("cls");
        cout << "Enter 'Q' when you wish to stop the program!: ";
        cin >> input;
    }
    shouldStop = true;
}