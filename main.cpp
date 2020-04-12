#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<string, vector<string>> rules; //fix code to reflect this new vector element
vector<string> terminals;

void convert();//string);

int main()
{
    string input = "", hold = "", convert_input = "", terminal = "", prod = "";
    vector<string> prod_vec;

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
                        prod_vec.push_back(handle);
                        handle = "";
                        continue;
                    }
                }

                rules.insert(pair<string, vector<string>> (terminal, prod_vec)); //insert prod into second's vector
                
                // for(pair<string, string> p: rules)
                // cout << p.first << " " << p.second;
            }
    }

    cout << "\nGrammar:\n" << input << endl;
    
    convert();

    cout << "\nBye\n";

    return EXIT_SUCCESS;
}

void convert()//string grammar)
{
    //use islower() and isupper() functions
    //PDA will have 3 states, q0 with transition to q1 with marking (lambda, z, Sz), q1 with loop to itself
    //with bunch of markings based on the grammar, and qf - final state with transition q1 to qf
    //with marking (lambda, z, lambda).

    vector<string> input_symbols;

    cout << "d(q0, lambda, z) = { (q1, Sz) }" << endl;

    //loop through every production line
    for(int i = 0; i < rules.size(); i++)
    {
        auto t = terminals.at(i); //current terminal
        pair<string, vector<string>> p {t, rules[t]}; //must be a string
        
        for(int x = 0; x < p.second.size(); x++)
        {
            //loop through the right side of arrow, character by character
            for(int j = 0; j < input_symbols.size(); j++)
            {
                //aAB
                string s = p.second.at(x); //one of the rules
                auto c = s[j]; //one rule at index j
                cout << "\n";

                // if(islower(c))
                // {   
                //    //d(q1, a, S) = { (q1,
                //     cout << "d(q1, " + c;
                //     cout << ", " + t + ") = { (q1,"; 
                // } else cout << c;
            }
        }
 
        // cout << ") }\n";
    }

    cout << "d(qf, lambda, z) = { (qz, lambda) }";

}