#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

void convert();

vector<vector<string>> grammar;
vector<string> line;

int main()
{
    string input = "", hold = "", convert_input = "", terminal = "", prod = "";

    cout << "Enter your Context-Free Grammar in GNF (enter 'x' to stop): ";
    cout << endl << endl;
    
    for(;;)
    {
        getline(cin, hold); //S->ab

        if(hold == "x") break;
            else
            {
                input = hold + '\n';
                terminal = *hold.begin();
                line.push_back(terminal);
                
                //load production variable
                auto iter = input.begin() + 3;
                prod = "";
                while(iter != input.end())
                {
                    prod += *iter; //loaded with everything to the right of the arrow
                    ++iter;
                }
                
                string handle = "";
                
                for(auto p: prod) //loops through whole production to the right of the arrow
                {
                    if(isalpha(p)) handle += p;
                    
                    if((p =='\n') || (p == '|'))
                    {
                        line.push_back(handle);
                        handle = "";
                    }
                    
                }
            }

        grammar.push_back(line);
        line.clear();
    }

    // for(auto g : grammar)
    // {
    //     for(auto l : g)
    //     cout << l << " ";
    // }

    cout << "\nGrammar:\n" << input << endl;
    
    convert();

    cout << "\n\nBye\n";

    return EXIT_SUCCESS;
}

void convert()//string grammar)
{
    //use islower() and isupper() functions
    //PDA will have 3 states, q0 with transition to q1 with marking (lambda, z, Sz), q1 with loop to itself
    //with bunch of markings based on the grammar, and qf - final state with transition q1 to qf
    //with marking (lambda, z, lambda).

    /*
    (q1, a, a) = {q1, lambda)
    (q1, b, b) = {q1, lambda)
    (q1, lambda, S) = {q1, aAB)
    (q1, lambda, B) = {q1, b)
    (q1, lambda, A) = {q1, aAB)
    */

    int x = 0;
    cout << "d(q0, lambda, z) = { (q1, Sz) }" << endl;

    //loop one production line at a time
    for(int i = 0; i < grammar.size(); i++) //rules = everything to the right of the arrow
    {
        for(int j = 0; j < grammar[i].size() - 1; j++)
        {
            
            cout << "d(q1, " << grammar[i][1].at(x) << ", " << grammar[i][0] << ") = {(q1, ";
            
            if(grammar[i][1].size() == 1)
            {
                cout << "lambda";
            }else
            {
                for(int k = 1; k < grammar[i][1].size(); k++)
                {
                    cout << grammar[i][1].at(k);
                }
            }
            
            /*for(int k = 1; k < grammar[i][1].size(); k++)
            {
                if(grammar[i][1].size() == 1)
                {
                    cout << "lambda";
                }else
                {
                    cout << grammar[i][1].at(k);

                }
                
            }*/
            // grammar[0] = s aBBBB
            // grammar [1] = a cD
            cout << ")} ";
            x++;
        } 
        x = 0;
        cout << endl;
    }

    cout << "d(qf, lambda, z) = { (qz, lambda) }";

}