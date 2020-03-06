#include "fr_tokenizer.h"

using namespace qnlp;

bool Tokenizer_fr::process_lang (vector<wstring>& vecwtoken)
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
        vecwtoken_it++;
        vecwtoken_it_prev++;
    }
    return false;
}

