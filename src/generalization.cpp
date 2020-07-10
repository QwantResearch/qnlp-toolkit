#include "generalization.h"



using namespace qnlp;
Generalization::Generalization()
{
    int iter_l = 0;
}


bool Generalization::checknumbers(string& token)
{
    int l_iter = 0;
    if (token[0] < ':' && token[0] > '/' && token[(int)token.size()-1] < ':' && token[(int)token.size()-1] > '/' )
    {
        for (l_iter = 1 ; l_iter < (int)token.size(); l_iter++)
        {
            if (token[l_iter] == '.' || token[l_iter] == ',' || (token[l_iter] < ':' && token[l_iter] > '/')) continue;
            else return false;
        }
    }
    else return false;
    return true;
}

bool Generalization::checkhours(string& token)
{
    int l_iter = 0;
    if (token[0] < ':' && token[0] > '/')
    {
        
        for (l_iter = 1 ; l_iter < (int)token.size(); l_iter++)
        {
            if (token[l_iter] == 'H' || token[l_iter] == 'h' || token[l_iter] == ':' || token[l_iter] == 'p' || token[l_iter] == 'm' || (token[l_iter] < ':' && token[l_iter] > '/')) continue;
            else return false;
        }
    }
    else return false;
    return true;
}

vector< string > Generalization::filter_numbers(vector< string >& sentence)
{
    int l_iter = 0;
    vector<string> to_return;
    for (l_iter = 0 ; l_iter < (int)sentence.size(); l_iter++)
    {
        if (checknumbers(sentence.at(l_iter)))
        {
            to_return.push_back("XNUMBER");
        }
        else
        {
            to_return.push_back(sentence.at(l_iter));
        }
    }
    return to_return;
}
vector< string > Generalization::filter_hours(vector< string >& sentence)
{
    int l_iter = 0;
    vector<string> to_return;
    for (l_iter = 0 ; l_iter < (int)sentence.size(); l_iter++)
    {
        if (checkhours(sentence.at(l_iter)))
        {
            to_return.push_back("XHOURS");
        }
        else
        {
            to_return.push_back(sentence.at(l_iter));
        }
    }
    return to_return;
}




