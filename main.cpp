#include <iostream>
#include <string>

using namespace std;

string convert(string);

int main()
{
    string input = "", hold = "", convert_input = "";

    cout << "Enter your Context-Free Grammar in GNF (enter 'x' to stop): ";
    cout << endl << endl;
    
    for(;;)
    {
        getline(cin, hold);
        if(hold == "x") break;
        input += hold + '\n';
    }

    cout << "\nGrammar:\n" << input;

    convert_input = convert(input);

    return EXIT_SUCCESS;
}

string convert(string grammar)
{
    //use islower() and isupper() functions
    //get grammar line by line
    string line = "", push_grammar = "";

    int i = 0; //i is declared outside of for loop scope so the index picks up where one line left off
    char x = 'l', check = *grammar.begin();
    char end = --*grammar.end();

    //deals with grammar line by line
    while(check != end)
    {
        for(i; i < grammar.size(); i++)
        {
            x = grammar.at(i);

            if(x == '\n') break;

            line += x;
            check++;
        }

        //deal with line
    }

    return push_grammar;
}