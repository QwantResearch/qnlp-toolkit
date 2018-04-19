#include "tokenizer.h"

using namespace qnlp;


vector<string> Tokenizer::tokenize_sentence(string& text)
{
    istringstream iss(text);
    vector<string> to_return;
    sb = iss.rdbuf();
    string l_token;
    while(read (l_token,false)) 
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
    return to_return;
}

string Tokenizer::tokenize_sentence_to_string(string& text)
{
    vector<string> tokenized=tokenize_sentence(text);
    ostringstream oss;
    string pred;
    for (int l_inc=0; l_inc < (int) tokenized.size() ; l_inc++)
    {
        if ((l_inc == 0) || (pred == "\n")) oss << tokenized.at(l_inc);
        else oss << " " << tokenized.at(l_inc);
        pred=tokenized.at(l_inc);
    }
    return oss.str();
}

vector<string> Tokenizer::tokenize(void)
{
    vector<string> to_return;
    string l_token;
    while(read (l_token,false)) 
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
    return to_return;
}

string Tokenizer::tokenize_to_string(void)
{
    vector<string> tokenized=tokenize();
    ostringstream oss;
    string pred;
    for (int l_inc=0; l_inc < (int) tokenized.size() ; l_inc++)
    {
        if ((l_inc == 0) || (pred == "\n")) oss << tokenized.at(l_inc);
        else oss << " " << tokenized.at(l_inc);
        pred=tokenized.at(l_inc);
    }
    return oss.str();
}

bool Tokenizer::read (string& token, bool newdoc) {
    char c;
    token.clear();
    newdoc = false;

    xmlDom dom;

    while ((c = sb->sbumpc()) != EOF) {
//         cerr << "|"<< token << "|"<< endl;
//         cerr << "|"<< c << "|"<< endl;

        if (syntax == XHTML) {
            if (parserXHTML(c, dom) == 1) {
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
                            if (proc(token,c)) return true;
                }
                else // token.empty() == true
                {
                    // **** Processing of empty token ****
                            if (proc_empty(token,c)) return true;
                } // !token.empty()
            }
            else // separatorRules(c) == true
            {
                if (lowercased)
                    c = tolower(c);
                token.push_back(c);
            } // separatorRules (c)
        } // do_read || syntax == PLAIN
    } // while

    return false;
}

bool Tokenizer::proc (string& token, char& c) {
    if (!aggressive) {
        switch(c) {
            case '.':
                if (dot_proc(token,c)) return true;
                else return false;
                break;

            case ',':
                if (comma_proc(token,c)) return true;
                else return false;
                break;

            default:
                sb->sungetc();
                break;
        }
        sb->sungetc();
        return true;

    } else {
        sb->sungetc();
        return true;
    }
}


bool Tokenizer::proc_empty (string& token, char& c) {
    switch(c) {
        case '.':
            token.push_back(c);
            if ((c = sb->sbumpc()) != EOF) {
                if (c == '.') {
                    token.push_back(c);
                    return false;

                } else {
                    sb->sungetc();
                    return true;
                }

            } else {
                return true;
            }

            break;

        default:
            if (c < 0) {
                token.push_back(c);
                if ((c = sb->sbumpc()) != EOF) {
                    if (c < 0) {
                        token.push_back(c);
                    } else {
                        c=sb->sungetc();
                        return true;
                    }
                }

                if ((c = sb->sbumpc()) != EOF) {
                    if (c < 0) {
                        token.push_back(c);
                    } else {
                        c = sb->sungetc();
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


bool Tokenizer::dot_proc(string& token, char& c) {
    token.push_back(c);

    size_t tklen = token.size();
    if (tklen < 3) return false;

    if (is_nbr(token)) {
        if (token[tklen-3] <= 0x39 
            && token[tklen-3] >= 0x30 
            && token[tklen-2] == '.' && 
            seps(token[tklen-1])){
            
            c = sb->sungetc();
            c = sb->sungetc();

            sb->sputbackc(token[tklen-1]);

            token = token.substr(0,tklen-2);

            return true;
        }
        return false;

    } else if (is_abrv(token)) {
        if ((token[tklen-2] < 0x5B && token[tklen-2] > 0x40) || (tklen == 2 && (token[0]=='e' || token[0]=='i'  || token[0]=='c'))){
            if ((c = sb->sbumpc()) != EOF){
                if (!seps_wide(c)){
                    token.push_back(c);
                    return false;
                } else {
                    sb->sungetc();
                    return true;
                }

            } else {
                return true;
            }
        }
        return true;

    } else {
        c = sb->sungetc();
        token = token.substr(0, tklen-1);
        return true;
    }

    return true;
}

bool Tokenizer::comma_proc (string& token, char& c) {
    token.push_back(c);
    
    if (is_nbr(token)) {
        if ((c = sb->sbumpc()) != EOF) {
            if (!seps(c)) {
                token.push_back(c);
                return false;
            } else {
                token = token.substr(0,token.size()-1);
                sb->sungetc();
                sb->sputbackc(',');
                return true;
            }
        }
        return true;

    } else {
        c = sb->sungetc();
        token = token.substr(0,token.size()-1);
        return true;
    }

    return true;
}


bool Tokenizer::is_abrv (string& token) {
    size_t tklen = token.size();

    if (token.find(".") != tklen-1) return true;

    int l_i = 0;
    while (l_i < abrvs.size()) {
        if (token.find(abrvs.at(l_i)) > 0) return true;
        l_i++;
    }

    if (tklen > 1) {
        if (token[tklen-2] == '.' && token[tklen-1] == '.') return false;
        if (token.find(".") == tklen-1) return false;
        if ((token[tklen-2] < 0x5B && token[tklen-2] > 0x40) || (tklen == 2 && (token[0]=='e' || token[0]=='i' || token[0]=='c'))) return true;
    }
    return false;
}

bool Tokenizer::is_nbr(string& token) {
    size_t tklen = token.size();

    int l_i =0;
    while (l_i < tklen) {
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
//         return (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e');
        return (c >= '\x03a' && c <= '\x040') || (c >= '\x05b' && c <= '\x060') || (c >= '\x07b' && c <= '\x07e');
    }
}

int Tokenizer::parserXHTML(char& c, xmlDom& dom) {
    if (c == '<') {
        string starter;
        starter.push_back(c);

        // Catch starter
        while ((c = sb->sbumpc()) != EOF) {
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

        sb->sungetc();

        string tag;
        string content;
        string tmp;
        bool get_tag = true;

        while ((c = sb->sbumpc()) != EOF) {
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

void Tokenizer::add_seps(char& c, string& lang, string& token)
{
    return;
}


// bool Tokenizer::dot_processing(string& token, char& c)
// {
//     token.push_back(c);
//     if (test_nbr(token)) 
//     {
//         if ((int)token.size() > 2 && token[(int)token.size()-3] <= '\x039' && token[(int)token.size()-3] >= '\x030' && token[(int)token.size()-2] == '.' && separatorRulesInline(token[(int)token.size()-1]))
//         {
//             
//             c=_sb->sungetc();
//             c=_sb->sungetc();
//             _sb->sputbackc(token[(int)token.size()-1]);
//             token=token.substr(0,(int)token.size()-2);
//             return true;
//         }
//         return false;
//     }
//     else if (test_abrv(token)) 
//     {
//         if ((token.size() >= 2 && token[token.size()-2]<'\x05B' && token[token.size()-2]>'\x040') || (token.size() == 2 && (token[0]=='e' || token[0]=='i'  || token[0]=='c')))
//         {
//             if ((c = _sb->sbumpc()) != EOF)
//             {
//                 if (!separatorRules(c))
//                 {
//                     
//                     token.push_back(c);
//                     return false;
//                 }
//                 else
//                 {
//                     _sb->sungetc();
//                     return true;
//                 }
//             }
//             else
//             {
//                 return true;
//             }
//         }
//         return true;
//     }
//     else
//     {
//         c=_sb->sungetc();
//         token=token.substr(0,((int)token.size())-1);
//         return true;
//     }
//     return true;
// }
// 
// bool Tokenizer::comma_processing(string& token, char& c)
// {
//     token.push_back(c);
//     if (test_nbr(token)) 
//     {
//         if ((c = _sb->sbumpc()) != EOF)
//         {
//             if (!separatorRulesInline(c))
//             {
//                 token.push_back(c);
//                 return false;
//             }
//             else
//             {
//                 token=token.substr(0,((int)token.size())-1);
//                 _sb->sungetc();
//                 _sb->sputbackc(',');
//                 return true;
//             }
//         }
//         return true;
//     }
//     else
//     {
//         c=_sb->sungetc();
//         token=token.substr(0,((int)token.size())-1);
//         return true;
//     }
//     return true;
// }
// 
// bool Tokenizer::test_nbr(string& token)
// {
//     int l_i =0;
//     while (l_i < (int)token.size())
//     {
//         if (l_i == 0 && token[0] == '-') { l_i++; continue;} 
//         if ((token[l_i] <= '\x039' && token[l_i] >= '\x030') || token[l_i] == '.'  || token[l_i] == ',')
//         {
//             l_i++;
//         }
//         else
//         {
//             return false;
//         }
//         l_i++;
//     }
//     return true;
// }
