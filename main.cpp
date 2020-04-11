#include <iostream>
#include <string>
#include "convert.cpp"

using namespace std;

int main()
{
    string input = "", hold = "";

    cout << "Enter your Context-Free Grammar in GNF (enter 'x' to stop): ";
    cout << endl << endl;
    
    for(;;)
    {
        getline(cin, hold);
        if(hold == "x") break;
        input += hold + '\n';
    }

    cout << "\nGrammar:\n" << input;

    convert(input);

    return EXIT_SUCCESS;
}