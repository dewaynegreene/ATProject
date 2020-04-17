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

    cout << "\nGrammar:\n";

    for(int i = 0; i < grammar.size(); i++) //rules = everything to the right of the arrow
    {
        for(int j = 1; j < grammar[i].size(); j++)
        {
            if(grammar[i].size() > 2)
            {
                if(j < 2) cout << grammar[i][0] << "->" << grammar[i][j];
                if(j >= 2) cout << "|" << grammar[i][j];
                    else if(j == (grammar[i].size() - 1)) cout << grammar[i][j];
            } else cout << grammar[i][0] << "->" << grammar[i][j];
        } 
        
        cout << endl;
    }

    cout << endl;

    convert();

    cout << "\n\nBye\n";

    return EXIT_SUCCESS;
}

void convert()
{
    cout << "PDA CONVERSION:\n";
    cout << "d(q0, lambda, z) = { (q1, Sz) }" << endl;

    //loop one production line at a time
    for(int i = 0; i < grammar.size(); i++) //rules = everything to the right of the arrow
    {
        cout << "d(q1, " << grammar[i][1].at(0) << ", " << grammar[i][0] << ") = ";//{(q1, ";

        if(grammar[i].size() > 2)
        {
            cout << "{(q1, ";
            for(int c = 1; c < grammar[i].size(); c++) // "-1" to not count terminal 
            {
                for(int k = 1; k < grammar[i][c].size(); k++)
                {
                    cout << grammar[i][c].at(k);
                }
                
                if(c == (grammar[i].size() - 1)) break;
                
                cout << "), (q1, ";
            }
        } else if(grammar[i][1].size() == 1)
            {
                cout << "{(q1, lambda";
            }else if(grammar[i][1].size() > 1)
            {
                cout << "{(q1, ";
                for(int k = 1; k < grammar[i][1].size(); k++)
                {
                    cout << grammar[i][1].at(k);
                }
            }
            
        cout << ")} ";
        cout << endl;
    }

    cout << "d(qf, lambda, z) = { (qz, lambda) }";

}