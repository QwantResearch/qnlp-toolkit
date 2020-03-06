#include "car_tokenizer.h"

using namespace qnlp;

vector<string> Tokenizer_car::tokenize(string& str)
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
        unsigned short cwc=(*utf16str_it);
        if (cwc > 31 ) 
        {
            wtoken.push_back(cwc);
            to_return_wchar.push_back(wtoken);
            wtoken.clear();
        }
        utf16str_it++;
    }
    if ((int)wtoken.size() > 0) to_return_wchar.push_back(wtoken);
    wtoken.clear();
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
    
