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


vector<string> Tokenizer::tokenize_sentence(string& text)
{
    istringstream iss(text);
    vector<string> to_return;
    streambuf* sbuf = iss.rdbuf();
    string l_token;
    while(read (l_token,false, sbuf)) 
    {
        if(!l_token.empty()) 
        {
                to_return.push_back(l_token);
        }
    }
    if(!l_token.empty()) 
    {
            to_return.push_back(l_token);
    }
    return normalize(to_return);
}

string Tokenizer::tokenize_sentence_to_string(string& text)
{
    vector<string> tokenized=tokenize_sentence(text);
    ostringstream oss;
    string next;
    string pred;
    for (int l_inc=0; l_inc < (int) tokenized.size() ; l_inc++)
    {
        next=tokenized.at(l_inc);
        if ((l_inc == 0) || (pred == "\n") || (next == "\n")) oss << next;
        else oss << " " << next;
        pred=next;
    }
    return oss.str();
}

vector<string> Tokenizer::tokenize(streambuf* sbuf)
{
    vector<string> to_return;
    string l_token;
    while(read (l_token,false,sbuf)) 
    {
        if(!l_token.empty()) 
        {
                to_return.push_back(l_token);
        }
    }
    if(!l_token.empty()) 
    {
            to_return.push_back(l_token);
    }
    return normalize(to_return);
}

vector<string> Tokenizer::tokenize(string& str)
{
    vector<string> to_return;
    vector<unsigned short> utf16str;
    vector<wstring> to_return_wchar;
    wstring wtoken;
    utf8::utf8to16(str.begin(), str.end(), back_inserter(utf16str));
    auto utf16str_it=utf16str.begin();
    
    while (utf16str_it != utf16str.end())
    {
        unsigned char wc=wtoken[0];
        unsigned char cwc=(*utf16str_it);
//         if (seps(wc))
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
        if (cwc != u' ' && cwc != u'\n' && cwc != u'\t') wtoken.push_back(cwc);
        
        utf16str_it++;
    }
    if ((int)wtoken.size() > 0)
    to_return_wchar.push_back(wtoken);
    wtoken.clear();
    process_numbers(to_return_wchar);
    process_cots(to_return_wchar);
    process_dots(to_return_wchar);
    if (lowercased) process_lowercase(to_return_wchar);
    auto to_return_wchar_it=to_return_wchar.begin();
    while (to_return_wchar_it != to_return_wchar.end())
    {
        string utf8str;
        wstring utf16str=(*to_return_wchar_it);
        utf8::utf16to8(utf16str.begin(), utf16str.end(), back_inserter(utf8str));
        if ((int)utf8str.size() > 0) to_return.push_back(utf8str);
        to_return_wchar_it++;
    }
    return to_return;
}

string Tokenizer::tokenize_to_string(streambuf* sbuf)
{
    vector<string> tokenized=tokenize(sbuf);
    ostringstream oss;
    string pred;
    string next;
    string output;
    for (int l_inc=0; l_inc < (int) tokenized.size() ; l_inc++)
    {
        next=tokenized.at(l_inc);
        if ((l_inc == 0) || (pred == "\n") || (next == "\n")) oss << next;
        else oss << " " << next;
        pred=next;
    }
    output=oss.str();
    return normalize(output);
}




bool Tokenizer::read (string& token, bool newdoc, streambuf* sbuf) {
    char c;
    token.clear();
    newdoc = false;
    bool do_read = false;

    xmlDom dom;

    while ((c = sbuf->sbumpc()) != EOF) {
        if (syntax == XHTML) {
            if (parserXHTML(c, dom, sbuf) == 1) {
                if (dom.tag == flag) 
                    do_read = dom.status;
                newdoc = do_read;
            } // parserXHTML(c, dom) == 1
        } // syntax == XHTML

        if (do_read || syntax == PLAIN) {
            if (seps_wide(c))
            {
                if (!token.empty())
                {
                    // **** Processing of not empty token ****
                            if (proc(token,c,sbuf)) return true;
                }
                else // token.empty() == true
                {
                    // **** Processing of empty token ****
                            if (proc_empty(token,c,sbuf)) return true;
                } // !token.empty()
            }
            else // separatorRules(c) == true
            {
                if (lowercased)
                    c = ToLower(c);
                token.push_back(c);
            } // separatorRules (c)
        } // do_read || syntax == PLAIN
        if ( syntax == CARACTER)
        {
            if (lowercased) c = ToLower(c);
            token.push_back(c);
            if (c == ' ') token="▁";
            else token=c;
            return true;
        } // syntax == CARACTER
    } // while

    return false;
}

bool Tokenizer::proc (string& token, char& c, streambuf* sbuf) {
    if (!aggressive) {
        switch(c) {
            case '.':
                if (no_punct) return true;
                if (dot_proc(token,c,sbuf)) return true;
                else return false;
                break;

            case ',':
                if (no_punct) return true;
                if (comma_proc(token,c,sbuf)) return true;
                else return false;
                break;

            default:
                if (!no_punct) sbuf->sungetc();
                return true;
                break;
        }
        sbuf->sungetc();
        return true;

    } else {
        if (!no_punct) sbuf->sungetc();
        return true;
    }
}


bool Tokenizer::proc_empty (string& token, char& c, streambuf* sbuf) {
    switch(c) {
        case '.':
            if (!no_punct) token.push_back(c);
            if ((c = sbuf->sbumpc()) != EOF) {
                if (c == '.') {
                    if (!no_punct) token.push_back(c);
                    return false;

                } else {
                    sbuf->sungetc();
                    return true;
                }

            } else {
                return true;
            }

            break;

        default:
            if (c < 0) {
                token.push_back(c);
                if ((c = sbuf->sbumpc()) != EOF) {
                    if (c < 0) {
                        token.push_back(c);
                    } else {
                        c=sbuf->sungetc();
                        return true;
                    }
                }

                if ((c = sbuf->sbumpc()) != EOF) {
                    if (c < 0) {
                        token.push_back(c);
                    } else {
                        c = sbuf->sungetc();
                        return true;
                    }
                }

                return true;
            }

            if (!seps(c) || c == '\n') {
                token.push_back(c);
                return true;
            }

            break;
    }
    return false;
}

bool Tokenizer::dot_proc(string& token, char& c, streambuf* sbuf)
{
    token.push_back(c);
    int tksize=(int)token.size();
    if (is_nbr(token)) {
        if ((c = sbuf->sbumpc()) != EOF) {
            if (!seps(c)) {
                token.push_back(c);
                return false;
            } else {
                token = token.substr(0,tksize-1);
                sbuf->sungetc();
                sbuf->sputbackc('.');
                return true;
            }
        }
        if ((c = sbuf->sbumpc()) == EOF) 
        {
            c=sbuf->sungetc();
            sbuf->sputbackc('.');
            token=token.substr(0,tksize-1);
            return true;
        }
        return true;
    }
    else if (is_abrv(token)) 
    {
        if ((tksize >= 2 && token[tksize-2]<'\x05B' && token[tksize-2]>'\x040') || (tksize == 2 && (token[0]=='e' || token[0]=='i'  || token[0]=='c')))
        {
            if ((c = sbuf->sbumpc()) != EOF)
            {
                if (!seps_wide(c))
                {
                    
                    token.push_back(c);
                    return false;
                }
                else
                {
                    sbuf->sungetc();
                    return true;
                }
            }
            else
            {
                return true;
            }
        }
        return true;
    }
    else
    {
        c=sbuf->sungetc();
        token=token.substr(0,(tksize)-1);
        return true;
    }
    return true;
}

bool Tokenizer::comma_proc (string& token, char& c, streambuf* sbuf) {
    token.push_back(c);
    int tksize=(int)token.size();
    if (is_nbr(token)) {
        if ((c = sbuf->sbumpc()) != EOF) {
            if (!seps(c)) {
                token.push_back(c);
                return false;
            } else {
                token = token.substr(0,tksize-1);
                sbuf->sungetc();
                sbuf->sputbackc(',');
                return true;
            }
        }
        if ((c = sbuf->sbumpc()) == EOF) 
        {
            c=sbuf->sungetc();
            sbuf->sputbackc(',');
            token=token.substr(0,tksize-1);
            return true;
        }
        return true;

    } else {
        c = sbuf->sungetc();
        token = token.substr(0,tksize-1);
        return true;
    }

    return true;
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




int Tokenizer::parserXHTML(char& c, xmlDom& dom, streambuf* sbuf) {
    if (c == '<') {
        string starter;
        starter.push_back(c);

        // Catch starter
        while ((c = sbuf->sbumpc()) != EOF) {
            if (!(starter.size() > 0 && (c == '-' || c == '/' || c == '?' || c == '!'))) {
                break;
            }

            if (c == ' ' && starter.empty()) continue; // syntax errors
            starter.push_back(c);
        }

        string stopper;
        map<string,string>::const_iterator it = html_codex.find(starter);

        if (it != html_codex.end()) {
            stopper = it->second;
        } else {
            return 0;
        }

        if (dom.tag == "script" && starter != "</") return 0;

        bool ignore_content = false;
        if (starter == "<?" || starter == "<!" || starter == "<!--")
            ignore_content = true;

        sbuf->sungetc();

        string tag;
        string content;
        string tmp;
        bool get_tag = true;

        while ((c = sbuf->sbumpc()) != EOF) {
            if (c == '>' || c == '?' || c == '!' || c == '-') {
                tmp.push_back(c);
            } else {
                tmp.clear();
            }

            if (c == ' ') {
                if (tag.empty()) continue;
                get_tag = false;
            }

            if (stopChecker(stopper, tmp)) {
                dom.tag = tag;
                dom.content = content;
                dom.status = !(starter == "</");
                return 1;
            }

            if (!ignore_content) {
                if (get_tag) {
                    tag.push_back(c);
                } else {
                    content.push_back(c);
                }
            }
        }
    }

    return 0;
}

bool qnlp::Tokenizer::process_cots(vector<std::__cxx11::wstring>& vecwtoken)
{
    return true;
}

bool qnlp::Tokenizer::process_acronym(vector<std::__cxx11::wstring>& vecwtoken)
{
    auto vecwtoken_it=std::find(vecwtoken.begin(),vecwtoken.end(),L".");
    if (vecwtoken_it!=vecwtoken.end() && vecwtoken_it!=vecwtoken.begin())
    {
        auto vecwtoken_it_prev=vecwtoken_it-1;
        auto vecwtoken_it_end=vecwtoken.begin();
        auto vecwtoken_it_curr=vecwtoken_it;
        if ((int)(*vecwtoken_it_prev).size() == 1)
        {
            while (vecwtoken_it_curr!=vecwtoken.end() && vecwtoken_it_curr != vecwtoken_it_end && (int)(*vecwtoken_it_prev).size() == 1)
            {
                vecwtoken_it_end=vecwtoken_it_curr;
                vecwtoken_it_curr=std::find(vecwtoken_it_curr+1,vecwtoken.end(),L".");
                vecwtoken_it_prev=vecwtoken_it_curr-1;
                if ((int)(vecwtoken_it_curr-vecwtoken_it_end) > 2) break;
                if (((*vecwtoken_it_prev)[0] <= '\x05a' && (*vecwtoken_it_prev)[0]  > '\x040') || ((*vecwtoken_it_prev)[0] <= '\x07a' && (*vecwtoken_it_prev)[0]  > '\x060'))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            if (vecwtoken_it_end != vecwtoken_it)
            {
                wstring toConcatenate;
                for (vecwtoken_it_curr=vecwtoken_it-1; vecwtoken_it_curr <= vecwtoken_it_end; vecwtoken_it_curr++)
                {
                    
                    toConcatenate=toConcatenate+(*vecwtoken_it_curr);
                    (*vecwtoken_it_curr)=L"";
                }
                if ((int)toConcatenate.size() > 0)
                {
                    (*(vecwtoken_it-1))=toConcatenate;
                    return true;
                }
            }
            return false;
        }
        return false;
    }
    return false;
}

bool qnlp::Tokenizer::process_abrv(vector<std::__cxx11::wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    auto vecwtoken_it_prev=vecwtoken.begin();
    vecwtoken_it++;
    wstring toTest;
    while (vecwtoken_it != vecwtoken.end() )
    {
        toTest=(*vecwtoken_it_prev)+(*vecwtoken_it);
        if (std::find(wabrvs.begin(), wabrvs.end(), toTest) != wabrvs.end() && (*vecwtoken_it) == L".")
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
        continue;
    }
    while (process_acronym(vecwtoken))
    {
        continue;
    }
    while (process_numbers(vecwtoken))
    {
        continue;
    }
    vecwtoken=clean_vector(vecwtoken);
    return true;
}

bool qnlp::Tokenizer::process_numbers(vector<std::__cxx11::wstring>& vecwtoken)
{
    auto vecwtoken_it=vecwtoken.begin();
    auto vecwtoken_it_prev=vecwtoken.begin();
    auto vecwtoken_it_next=vecwtoken.begin();
    vecwtoken_it++;
    vecwtoken_it_next++;
    vecwtoken_it_next++;
    wstring toTest;
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
            unsigned char wc=(*wtoken_it);
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

vector<wstring> qnlp::Tokenizer::clean_vector(vector<wstring> vecwtoken)
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


void Tokenizer::add_seps(char& c, string& lang, string& token)
{
    return;
}

string Tokenizer::getlang()
{
    return lang;
}

