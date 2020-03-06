#include "en_tokenizer.h"

using namespace qnlp;

bool Tokenizer_en::process_lang (vector<wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    auto vecwtoken_it_prev=vecwtoken.begin();
    if (vecwtoken_it != vecwtoken.end()) vecwtoken_it++; else return false;
    wstring toTest;
    while (vecwtoken_it != vecwtoken.end() )
    {
        toTest=(*vecwtoken_it_prev)+(*vecwtoken_it);
        if (std::find(wlang_process.begin(), wlang_process.end(), toTest) != wlang_process.end()) // && (*vecwtoken_it) == L"."
        {
            (*vecwtoken_it_prev)=toTest;
            (*vecwtoken_it)=L"";
            return true;
        }
        if (std::find(wlang_process_not.begin(), wlang_process_not.end(), toTest) != wlang_process_not.end() && ((int)(*vecwtoken_it).size()>0 && (*vecwtoken_it)[0]==u'\'')) // && (*vecwtoken_it) == L"."
        {
            wcerr << (*vecwtoken_it_prev) << "|" << (*vecwtoken_it) << endl;
            (*vecwtoken_it_prev)=toTest.substr(0,toTest.find(u'n'));
            (*vecwtoken_it)=L"n't";
            return true;
        }
        vecwtoken_it++;
        vecwtoken_it_prev++;
    }
    return false;
}

