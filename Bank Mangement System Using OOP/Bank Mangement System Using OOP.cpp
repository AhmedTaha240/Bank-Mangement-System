// Bank Mangement System Using OOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clsLoginScreen.h"
#include "clsCurrency.h"

//#include "clsCurrencyExchangeScreen.h"

using namespace std;

void _PrintCurrency(clsCurrency Currency)
{
    cout << "\nCurrency Card:\n";
    cout << "_____________________________\n";
    cout << "\nCountry    : " << Currency.Country();
    cout << "\nCode       : " << Currency.CurrencyCode();
    cout << "\nName       : " << Currency.CurrencyName();
    cout << "\nRate(1$)   : " << Currency.Rate();

    cout << "\n_____________________________\n";
}

int main()
{
    char Answer = 'n';
    while (tolower(Answer) == 'n')
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }

        cout << "\nDo you want to Exit this Form of System! [Y / N] ";
        cin >> ws >> Answer;
    }

    cout << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
