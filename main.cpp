#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

map<string, vector<string>> rules; //fix code to reflect this new vector element
vector<string> terminals;

string convert();//string);

int main()
{
    string input = "", hold = "", convert_input = "", terminal = "", prod = "";

    cout << "Enter your Context-Free Grammar in GNF (enter 'x' to stop): ";
    cout << endl << endl;
    
    for(;;)
    {
        getline(cin, hold);
        if(hold == "x") break;
            else
            {
                input += hold + '\n';
                terminal = *hold.begin();
                terminals.push_back(terminal);
                // cout << "terminal: " << terminal << endl;
                
                //load production variable
                auto iter = hold.begin() + 3;
                while(iter != hold.end()) // handle case: | adD | adf 
                {
                    prod += *iter;
                    // cout << "Prod: " << prod << endl;
                    ++iter;
                }

                string handle = "";
                for(auto p: prod) //loops through whole production to the right of the arrow
                {
                    
                    handle += p;
                    
                    if((p == '|') || (p == '\n'))
                    {
                        //push back handle
                        
                        handle = "";
                        continue;
                    }
                }

                rules.insert(pair<string, string> (terminal, prod)); //insert prod into second's vector

                // for(pair<string, string> p: rules)
                // cout << p.first << " " << p.second;
            }
    }

    cout << "\nGrammar:\n" << input;

    convert_input = convert();//input);

    cout << "\nBye\n";

    return EXIT_SUCCESS;
}

string convert()//string grammar)
{
    //use islower() and isupper() functions
    //PDA will have 3 states, q0 with transition to q1 with marking (lambda, z, Sz), q1 with loop to itself
    //with bunch of markings based on the grammar, and qf - final state with transition q1 to qf
    //with marking (lambda, z, lambda).

    string push_grammar = "";
    vector<string> input_symbols = "";

    string g_line = "";
    g_line = "d(q0, lambda, z) = { (q1, Sz) }" + '\n';
    push_grammar += g_line;

    //loop through every production line
    for(int i = 0; i < rules.size(); i++)
    {
        auto t = terminals.at(i); //current terminal
        pair<string, string> p = rules[t];
        input_symbols = p.second;
        
        //convert input_symbols to c string to access characters
        char new_input_symbols[input_symbols.size() + 1];
        strcpy(new_input_symbols, input_symbols.c_str());

        //loop through the right side of arrow, character by character
        for(int j = 0; j < input_symbols.size(); j++)
        {
            //aAB
            if(islower(new_input_symbols.at(j))) g_line = "d(q1, " + new_input_symbols.at(j) + ", " + t + ") = { (q1,";
                else g_line += new_input_symbols.at(j);
        }

        g_line += ") }\n"; 

        push_grammar += g_line;
    }

    g_line = "d(qf, lambda, z) = { (qz, lambda) }" + '\n';
    push_grammar += g_line;

    return push_grammar;
}