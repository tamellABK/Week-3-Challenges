#include <iostream>
#include <thread>

using namespace std;

bool shouldStop = false;
int const UPPER_BOUND = 100000;

void getSize(string word, int* toReturn)
{
    string indivWord = word;
    while(!shouldStop)
    {
        word += indivWord;
        if (UPPER_BOUND < word.size())
        {
            word = "";
        }
    }
    *toReturn = word.size();
}

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

int main()
{
    int fin = 0;
    thread GetSizeThread(getSize, "foo", &fin);

    getPlayerInput();

    GetSizeThread.join();
    cout << fin;
}