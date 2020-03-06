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
        if (((int)(*vecwtoken_it).size() == 1) && (*vecwtoken_it)[0] == u'\'')
        {
            int vecwtoken_it_prev_size=(int)(*vecwtoken_it_prev).size();
            if (vecwtoken_it_prev_size > 2)
            {
                if ((*vecwtoken_it_prev)[vecwtoken_it_prev_size-2] == '-' && ((*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'd' || (*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'l' || (*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'n' || (*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'j'))
                (*vecwtoken_it_prev)=toTest;
                (*vecwtoken_it)=L"";
                auto vecwtoken_it_next=vecwtoken_it;
                if (vecwtoken_it_next != vecwtoken.end()) vecwtoken_it_next++; else return false;
                (*vecwtoken_it_prev)=(*vecwtoken_it_prev)+(*vecwtoken_it_next);
                (*vecwtoken_it_next)=L"";
                return true;
            }
        }
        vecwtoken_it++;
        vecwtoken_it_prev++;
    }
    return false;
}

