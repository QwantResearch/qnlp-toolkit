#include "stopwords.h"



using namespace qnlp;
Stopwords::Stopwords()
{
    int iter_l = 0;
    int iter_d = 0;
    for (iter_l =0; iter_l < (int)_data.size(); iter_l++)
    {
        std::unordered_map<string,int> l_data;
        for (iter_d =0; iter_d < (int)_data.at(iter_l).second.size(); iter_d++)
        {
            string word=_data.at(iter_l).second.at(iter_d);
            int length = (int) word.length();
            pair<string,int> l_p(word,length);
            l_data.insert(l_p);
        }
        pair<std::string,std::unordered_map<string,int> > l_ps(_data.at(iter_l).first,l_data);
        _list_stopwords.insert(l_ps);
    }
}


bool Stopwords::checkword(string& token, string lang)
{
    std::unordered_map< string, std::unordered_map<string,int> >::iterator l_iterator=_list_stopwords.find(lang);
    if (l_iterator!=_list_stopwords.end())
    {
        std::unordered_map<string,int>::iterator l_iter2 = l_iterator->second.find(token);
        if (l_iter2!= l_iterator->second.end())
        {
            return true;
        }
        return false;
    }
    return false;
}

vector< string > Stopwords::filter_stopwords(vector< string >& sentence, string lang)
{
    int l_iter = 0;
    vector<string> to_return;
    for (l_iter = 0 ; l_iter < (int)sentence.size(); l_iter++)
    {
        if ( ! checkword(sentence.at(l_iter),lang))
        {
            to_return.push_back(sentence.at(l_iter));
        }
    }
    return to_return;
}
