#include "fr_tokenizer.h"

using namespace qnlp;

bool Tokenizer_fr::process_lang (vector<wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    auto vecwtoken_it_prev=vecwtoken.begin();
    if (vecwtoken_it != vecwtoken.end()) vecwtoken_it++; else return false;
    while (vecwtoken_it != vecwtoken.end() )
    {
        if (std::find(wlang_process.begin(), wlang_process.end(), (*vecwtoken_it_prev)+(*vecwtoken_it)) != wlang_process.end()) // && (*vecwtoken_it) == L"."
        {
            (*vecwtoken_it_prev)=(*vecwtoken_it_prev)+(*vecwtoken_it);
            (*vecwtoken_it)=L"";
            return true;
        }
        vecwtoken_it++;
        vecwtoken_it_prev++;
    }
    return false;
}

bool Tokenizer_fr::process_cots(vector<wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    auto vecwtoken_it_prev=vecwtoken.begin();
    if (vecwtoken_it != vecwtoken.end()) vecwtoken_it++; else return false;
    while (vecwtoken_it != vecwtoken.end() )
    {
        if (((int)(*vecwtoken_it).size() == 1) && (*vecwtoken_it)[0] == u'\'')
        {
            int vecwtoken_it_prev_size=(int)(*vecwtoken_it_prev).size();
            if (vecwtoken_it_prev_size == 1)
            {
                if ((*vecwtoken_it_prev)[0] == 'c' || (*vecwtoken_it_prev)[0] == 'd' || (*vecwtoken_it_prev)[0] == 'l' || (*vecwtoken_it_prev)[0] == 'n' || (*vecwtoken_it_prev)[0] == 'j' || (*vecwtoken_it_prev)[0] == 's' || (*vecwtoken_it_prev)[0] == 't' ||
                    (*vecwtoken_it_prev)[0] == 'C' || (*vecwtoken_it_prev)[0] == 'D' || (*vecwtoken_it_prev)[0] == 'L' || (*vecwtoken_it_prev)[0] == 'N' || (*vecwtoken_it_prev)[0] == 'J' || (*vecwtoken_it_prev)[0] == 'S' || (*vecwtoken_it_prev)[0] == 'T' 
                    )
                {
                    (*vecwtoken_it_prev)=(*vecwtoken_it_prev)+(*vecwtoken_it);
                    (*vecwtoken_it)=L"";
                    return true;
                }
            }
            if (vecwtoken_it_prev_size == 2)
            {
                if (((*vecwtoken_it_prev)[vecwtoken_it_prev_size-2] == 'q' || (*vecwtoken_it_prev)[vecwtoken_it_prev_size-2] == 'Q') && ((*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'u' ))
                {
                    (*vecwtoken_it_prev)=(*vecwtoken_it_prev)+(*vecwtoken_it);
                    (*vecwtoken_it)=L"";
                    return true;
                }
            }
            if (vecwtoken_it_prev_size > 2)
            {
                if (((*vecwtoken_it_prev)[vecwtoken_it_prev_size-2] == '-' && ((*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'd' || (*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'l' || (*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'n' || (*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'j' || (*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 's')) || ((*vecwtoken_it_prev)[vecwtoken_it_prev_size-3] == '-' && (*vecwtoken_it_prev)[vecwtoken_it_prev_size-2] == 'q' && (*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'u' ))
                {
                    (*vecwtoken_it_prev)=(*vecwtoken_it_prev)+(*vecwtoken_it);
                    (*vecwtoken_it)=L"";
                    auto vecwtoken_it_next=vecwtoken_it;
                    if (vecwtoken_it_next != vecwtoken.end()) vecwtoken_it_next++;
                    if (vecwtoken_it_next != vecwtoken.end())
                    {
                        (*vecwtoken_it_prev)=(*vecwtoken_it_prev)+(*vecwtoken_it_next);
                        (*vecwtoken_it_next)=L"";
                    }
                    return true;
                }
                if ((*vecwtoken_it_prev)[vecwtoken_it_prev_size-2] == 'q' && ((*vecwtoken_it_prev)[vecwtoken_it_prev_size-1] == 'u' ))
                {
                    (*vecwtoken_it_prev)=(*vecwtoken_it_prev)+(*vecwtoken_it);
                    (*vecwtoken_it)=L"";
                    return true;
                }
            }
//             return false;
        }
        vecwtoken_it++;
        vecwtoken_it_prev++;
    }
    return false;
}

