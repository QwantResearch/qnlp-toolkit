#include "tokenizer.h"

using namespace qnlp;


vector< string > Tokenizer::normalize(vector< string > &vecToken)
{
    vector< string > to_return;
    for (int l_inc=0; l_inc < (int) vecToken.size() ; l_inc++)
    {
        to_return.push_back(normalize(vecToken.at(l_inc)));
    }
    return to_return;
    
}
string Tokenizer::normalize(string &token)
{
    if (token[(int)token.size()-1] == ' ') token=token.substr(0,((int)token.size())-1);
    return  boost::locale::conv::utf_to_utf<char>(token.c_str());
}


vector<string> Tokenizer::tokenize(string& str)
{
    vector<string> to_return;
    vector<unsigned short> utf16str;
    vector<unsigned int> utf32str;
    vector<wstring> to_return_wchar;
    wstring wtoken;
    bool process_numbers_todo=false;
    utf8::utf8to16(str.begin(), str.end(), back_inserter(utf16str));
    auto utf16str_it=utf16str.begin();
    while (utf16str_it != utf16str.end())
    {
        unsigned short wc=wtoken[0];
        unsigned short cwc=(*utf16str_it);
        if (seps(wc))
        {
            if ((int)wtoken.size() > 0)
            to_return_wchar.push_back(wtoken);
            wtoken.clear();
        }
        if (seps(cwc))
        {
            if ((int)wtoken.size() > 0)
            to_return_wchar.push_back(wtoken);
            wtoken.clear();
            
        }
        if (cwc > 32 ) wtoken.push_back(cwc);
        else
        {
            if ((int)wtoken.size() > 0)
            to_return_wchar.push_back(wtoken);
            wtoken.clear();
            to_return_wchar.push_back(L"@@@");            
        }
        if (cwc > 47 && cwc < 58 ) process_numbers_todo=true;
        
        utf16str_it++;
    }
    if ((int)wtoken.size() > 0) to_return_wchar.push_back(wtoken);
    wtoken.clear();
    process_cots(to_return_wchar);
    if (process_numbers_todo)
    {
        while (process_numbers(to_return_wchar) )
        {
            continue;
        }
    }
    
    process_dots(to_return_wchar);
    
    while (process_lang(to_return_wchar))
    {
        to_return_wchar=clean_vector(to_return_wchar);
    }
    if (lowercased) process_lowercase(to_return_wchar);
    auto to_return_wchar_it=to_return_wchar.begin();
    while (to_return_wchar_it != to_return_wchar.end())
    {
        string utf8str;
        wstring utf16str=(*to_return_wchar_it);
        utf8::utf16to8(utf16str.begin(), utf16str.end(), back_inserter(utf8str));
        if ((int)utf8str.size() > 0 && ! is_separator(utf8str)) to_return.push_back(utf8str);
        to_return_wchar_it++;
    }
    return to_return;
}
bool Tokenizer::process_lang (vector<wstring>& vecwtoken)
{
    return false;
}

bool Tokenizer::is_abrv (string& token) {
    int tksize = (int)token.size();

    if ((int)token.find(".") != (tksize-1)) return true;
    int l_i =0;
    while (l_i < (int)abrvs.size())
    {
        if ((int)token.find(abrvs.at(l_i)) > -1 ) {return true;}
        l_i++;
    }
    if (tksize >= 2 && token[tksize-2]== '.' && token[tksize-1]=='.') return false;
    if (tksize > 2 && (int)token.find(".") == (tksize-1)) return false;
    if ((tksize >= 2 && token[tksize-2]<'\x05B' && token[tksize-2]>'\x040') || (tksize == 2 && (token[0]=='e' || token[0]=='i' || token[0]=='c'))) return true;
    return false;
}

bool Tokenizer::is_nbr(string& token) {
    int tksize = (int)token.size();

    int l_i =0;
    while (l_i < tksize) {
        if (l_i == 0 && token[0] == '-') {
            l_i++;
            continue;
        } 

        if ((token[l_i] <= 0x39 && token[l_i] >= 0x30) || token[l_i] == '.' || token[l_i] == ',')
            l_i++;
        else
            return false;

        l_i++;
    }
    return true;
}

bool Tokenizer::is_nbr(wstring& wtoken) {
    int tksize = (int)wtoken.size();

    int l_i =0;
    while (l_i < tksize) {
        if (l_i == 0 && wtoken[0] == u'-') 
        {
            l_i++;
            continue;
        } 
        if ((wtoken[l_i] <= 0x39 && wtoken[l_i] >= 0x30) || wtoken[l_i] == u'.' || wtoken[l_i] == u',')
            l_i++;
        else
            return false;
        l_i++;
    }
    return true;
}
/*
bool Tokenizer::is_nbr(char& c) {
}*/

bool Tokenizer::seps (char& c) {
    if (c == -62) return true;
    if (c == -30) return true;
    if (c <= '\x020' && c > 0) {
        return true;
    } else {
        if (c == '-' && !dash ) return false;
        if (c == '_' && !underscore) return false;
        return (c == '\x07F');
    }
}

bool Tokenizer::seps_wide (char& c) {
    if (c == -62 ) return true;
    if (c == -30 ) return true;
    if (c == '-' && !dash ) return false;
    if (c == '_' && !underscore) return false;
    if (c <= '\x02f' && c > 0) {
        return true;
    } else {
        return (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e');
    }
}


bool Tokenizer::seps (unsigned char& c) {
    if (c == u'-' && !dash ) return false;
    if (c == u'_' && !underscore) return false;
    return ((c <= '\x02F' && c > 0) || (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e'));
//     {
//         return true;
//     } else {
//         return (c == '\x07F');
//     }
}

bool Tokenizer::seps_wide (unsigned char& c) {
    if (c == '-' && !dash ) return false;
    if (c == '_' && !underscore) return false;
    if (c <= '\x02f' && c > 0) {
        return true;
    } else {
        return (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e');
    }
}


bool Tokenizer::seps (unsigned int& c) {
    if (c == u'-' && !dash ) return false;
    if (c == u'_' && !underscore) return false;
    return ((c <= '\x02F' && c > 0) || (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e'));
//     {
//         return true;
//     } else {
//         return (c == '\x07F');
//     }
}

bool Tokenizer::seps_wide (unsigned int& c) {
    if (c == '-' && !dash ) return false;
    if (c == '_' && !underscore) return false;
    if (c <= '\x02f' && c > 0) {
        return true;
    } else {
        return (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e');
    }
}


bool Tokenizer::seps (unsigned short& c) {
    if (c == u'-' && !dash ) return false;
    if (c == u'‒' && !dash ) return false;
    if (c == u'_' && !underscore) return false;
    if (c == u'…' ) return true;
    if (c == u'«' ) return true;
    if (c == u'»' ) return true;
    if (c == u'€' ) return true;
    
    return ((c <= '\x02F' && c > 0) || (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e') || (c >= '\x07f' && c <= '\x0bf'));
//     {
//         return true;
//     } else {
//         return (c == '\x07F');
//     }
}

bool Tokenizer::seps_wide (unsigned short& c) {
    if (c == u'-' && !dash ) return false;
    if (c == u'_' && !underscore) return false;
    if (c == u'…' ) return true;
    if (c <= '\x02f' && c > 0) {
        return true;
    } else {
        return (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e');
    }
}




bool qnlp::Tokenizer::process_cots(vector<std::__cxx11::wstring>& vecwtoken)
{
    return true;
}


bool qnlp::Tokenizer::process_acronym(vector<wstring>& vecwtoken)
{
    vector<wstring> vecwtoken_to_return;
    auto vecwtoken_it=vecwtoken.end();
    if (vecwtoken_it != vecwtoken.begin()) vecwtoken_it--; else return false;
    auto vecwtoken_prev_it=vecwtoken.end();
    if (vecwtoken_prev_it != vecwtoken.begin()) vecwtoken_prev_it--; else return false;
    if (vecwtoken_prev_it != vecwtoken.begin()) vecwtoken_prev_it--; else return false;
    vector<wstring>::iterator vecwtoken_curr_it;
    vector<wstring>::iterator vecwtoken_start_it;
    vector<wstring>::iterator vecwtoken_end_it=vecwtoken.end();
    wstring wtoken_prev;
    wstring wtoken;
    while (vecwtoken_prev_it != vecwtoken.begin())
    {
        wtoken_prev=(*vecwtoken_prev_it);
        wtoken=(*vecwtoken_it);
        if (((int)wtoken.size() == 1 && (int)wtoken_prev.size() == 1 )  && (wtoken_prev[0] > 64 && wtoken_prev[0] < 91 && wtoken[0] == u'.' ) )
        {
            vecwtoken_start_it=vecwtoken_prev_it;
            if (vecwtoken_end_it==vecwtoken.end()) vecwtoken_end_it=vecwtoken_it;
        }
        else
        {            
            if (vecwtoken_end_it!=vecwtoken.end()) break;
        }
        vecwtoken_prev_it--;
        vecwtoken_it--;
        if (vecwtoken_end_it!=vecwtoken.end()) 
        {
            if (vecwtoken_prev_it != vecwtoken.begin()) vecwtoken_prev_it--; else break;
            if (vecwtoken_it != vecwtoken.begin()) vecwtoken_it--; else break;
        }
    }
    wtoken_prev=(*vecwtoken_prev_it);
    wtoken=(*vecwtoken_it);
    if (((int)wtoken.size() == 1 && (int)wtoken_prev.size() == 1 )  && (wtoken_prev[0] > 64 && wtoken_prev[0] < 91 && wtoken[0] == u'.' ) )
    {
        vecwtoken_start_it=vecwtoken_prev_it;
        if (vecwtoken_end_it==vecwtoken.end()) vecwtoken_end_it=vecwtoken_it;
    }
    if (vecwtoken_end_it==vecwtoken.end()) return false;
    wstring toConcatenate;
    vecwtoken_curr_it=vecwtoken_start_it;
    while (vecwtoken_curr_it != vecwtoken_end_it)
    {
        toConcatenate=toConcatenate+(*vecwtoken_curr_it);
        (*vecwtoken_curr_it)=L"";
        vecwtoken_curr_it++;
    }
    toConcatenate=toConcatenate+(*vecwtoken_curr_it);
    (*vecwtoken_end_it)=toConcatenate;
    return true;
}
bool qnlp::Tokenizer::process_abrv(vector<std::__cxx11::wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    auto vecwtoken_it_prev=vecwtoken.begin();
    if (vecwtoken_it != vecwtoken.end()) vecwtoken_it++; else return false;
    wstring toTest;
    while (vecwtoken_it != vecwtoken.end() )
    {
        toTest=(*vecwtoken_it_prev)+(*vecwtoken_it);
        if (std::find(wabrvs.begin(), wabrvs.end(), toTest) != wabrvs.end()) // && (*vecwtoken_it) == L"."
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

bool qnlp::Tokenizer::process_dots(vector<std::__cxx11::wstring>& vecwtoken)
{
    while (process_abrv(vecwtoken))
    {
        vecwtoken=clean_vector(vecwtoken);
        continue;
    }
    while (process_acronym(vecwtoken))
    {
        continue;
    }
    while (process_ldots(vecwtoken))
    {
        continue;
    }
    return true;
}

bool qnlp::Tokenizer::process_numbers(vector<std::__cxx11::wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    auto vecwtoken_it_prev=vecwtoken.begin();
    auto vecwtoken_it_next=vecwtoken.begin();
    wstring toTest;
    if (vecwtoken_it != vecwtoken.end())vecwtoken_it++; else return false;
    if (vecwtoken_it_next != vecwtoken.end())vecwtoken_it_next++; else return false;
    if (vecwtoken_it_next != vecwtoken.end())vecwtoken_it_next++; else return false;
    while (vecwtoken_it_next != vecwtoken.end())
    {
        if (is_nbr(*vecwtoken_it_prev) && is_nbr(*vecwtoken_it_next) && ((*vecwtoken_it)==L"." || (*vecwtoken_it)==L",") )
        {
            (*vecwtoken_it_next)=(*vecwtoken_it_prev)+(*vecwtoken_it)+(*vecwtoken_it_next);
            (*vecwtoken_it)=L"";
            (*vecwtoken_it_prev)=L"";
            return true;
        }
        vecwtoken_it++;
        vecwtoken_it_next++;
        vecwtoken_it_prev++;
    }
    return false;

}

bool qnlp::Tokenizer::process_lowercase(vector<std::__cxx11::wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    while (vecwtoken_it != vecwtoken.end())
    {
        
        auto wtoken_it=(*vecwtoken_it).begin();
        while (wtoken_it != (*vecwtoken_it).end())
        {
            unsigned int wc=(*wtoken_it);
            (*wtoken_it)=ToLower(wc);
            wtoken_it++;
        }
        vecwtoken_it++;
    }
    return true;
}


bool Tokenizer::stopChecker (string& ref, string& leq) {
    size_t s_ref = ref.size();
    size_t s_leq = leq.size();
    size_t s_delta = s_leq - s_ref;

    for (int i = s_ref; i >= 0; i--) {
        if (ref[i] != leq[i+s_delta])
            return false;
    }

    return true;
}

vector<wstring> qnlp::Tokenizer::clean_vector(vector<wstring>& vecwtoken)
{
    vector<wstring> vecwtoken_to_return;
    auto vecwtoken_it=vecwtoken.begin();
    while (vecwtoken_it != vecwtoken.end())
    {
        if ((int)(*vecwtoken_it).size()>0) 
        {
            vecwtoken_to_return.push_back((*vecwtoken_it));
        }
        vecwtoken_it++;
    }
    return vecwtoken_to_return;
}

bool qnlp::Tokenizer::process_ldots(vector<wstring>& vecwtoken)
{
    vector<wstring> vecwtoken_to_return;
    auto vecwtoken_it=vecwtoken.end();
    if (vecwtoken_it != vecwtoken.begin()) vecwtoken_it--; else return false;
    auto vecwtoken_prev_it=vecwtoken.end();
    if (vecwtoken_prev_it != vecwtoken.begin()) vecwtoken_prev_it--; else return false;
    if (vecwtoken_prev_it != vecwtoken.begin()) vecwtoken_prev_it--; else return false;
    auto vecwtoken_prev_prev_it=vecwtoken.end();
    if (vecwtoken_prev_prev_it != vecwtoken.begin()) vecwtoken_prev_prev_it--; else return false;
    if (vecwtoken_prev_prev_it != vecwtoken.begin()) vecwtoken_prev_prev_it--; else return false;
    if (vecwtoken_prev_prev_it != vecwtoken.begin()) vecwtoken_prev_prev_it--; else return false;
    while (vecwtoken_prev_prev_it != vecwtoken.begin())
    {
        wstring wtoken_prev_prev=(*vecwtoken_prev_prev_it);
        wstring wtoken_prev=(*vecwtoken_prev_it);
        wstring wtoken=(*vecwtoken_it);
        if (((int)wtoken.size() == 1 && (int)wtoken_prev.size() == 1 && (int)wtoken_prev_prev.size() == 1)  && (wtoken[0] == u'.' && wtoken_prev[0] == u'.' && wtoken_prev_prev[0] == u'.' ) )
        {
            (*vecwtoken_it)=L"...";
            (*vecwtoken_prev_it)=L"";
            (*vecwtoken_prev_prev_it)=L"";
            return true;
        }
        vecwtoken_prev_prev_it--;
        vecwtoken_prev_it--;
        vecwtoken_it--;
    }
    return false;
}

bool qnlp::Tokenizer::is_separator(string& token)
{
    if ((int)token.size() == 3)
    {
        if (token[0]=='@' && token[1]=='@' && token[2]=='@') return true;
        return false;
    }
    return false;
}

bool qnlp::Tokenizer::is_separator(std::__cxx11::wstring& wtoken)
{
    if ((int)wtoken.size() == 3)
    {
        if (wtoken[0]==u'@' && wtoken[1]==u'@' && wtoken[2]==u'@') return true;
        return false;
    }
    return false;
}
bool qnlp::Tokenizer::print_vector(vector<std::__cxx11::wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    while (vecwtoken_it != vecwtoken.end())
    {
        wcerr << (*vecwtoken_it) << L"|" ;
        vecwtoken_it++;
    }
    cerr << endl;
    return true;
}


void Tokenizer::add_seps(char& c, string& lang, string& token)
{
    return;
}

string Tokenizer::getlang()
{
    return lang;
}

string Tokenizer::tokenize_sentence_to_string(string & str)
{
    vector<string> to_return = tokenize(str);
    return qnlp::Join(to_return , " ");
}
