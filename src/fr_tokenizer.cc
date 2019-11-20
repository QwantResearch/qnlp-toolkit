#include "fr_tokenizer.h"

using namespace qnlp;

bool Tokenizer_fr::proc(string& token, char& c, streambuf* sbuf) {
    if (!aggressive)
    {
        if (is_nbr(token)) 
        {
            cerr << "is nbr " << token << endl;
            if ((int)token.size() >= 2 && token[(int)token.size()-2] <= '\x039' && token[(int)token.size()-2] >= '\x030' && token[(int)token.size()-1] == '.')
            {
                char l_char=token.substr((int)token.size()-1,1)[0];
                token=token.substr(0,(int)token.size()-1);
                c=sbuf->sungetc();
                c=sbuf->sungetc();
                sbuf->sputbackc(l_char);
                return true;
            }
        }
        switch(c)
        {
            case '\'':
                token.push_back(c);
                if ((int)token.size() == 2 && token[0]=='O') return false;
                if ((int)token.find("jourd") > -1) return false;
                if ((int)token.find("ock") > -1) return false;
                if ((int)token.find("-d") > -1) return false;
                if ((int)token.find("-l") > -1) return false;
                if ((int)token.find("squ") > -1) return true;
                if ((int)token.size() >= 2 && token[0]=='q' && token[1]=='u') return true;
                if ((int)token.size() == 2) return true;
                if ((int)token.size() >= 3) {token=token.substr(0,((int)token.size())-1);sbuf->sungetc();return true;}
                break;
            case '.':
                if (dot_proc(token,c,sbuf)) return true;
                else return false;
            case ',':
                if (comma_proc(token,c,sbuf)) return true;
                else return false;
                break;
            default:
                if (c < 0)
                {
                    if (c == -30 && (int)token.size() == 1)
                    {
                        token.push_back(c);
                        if ((c = sbuf->sbumpc()) != EOF)
                        {
                            if (!seps(c))
                            {
                                token.push_back(c);
                            }
                            else
                            {
                                token=token.substr(0,((int)token.size())-1);
                                sbuf->sungetc();
                                sbuf->sungetc();
                                sbuf->sputbackc(c);
                                return true;                                                      
                            }
                        }
                        if ((c = sbuf->sbumpc()) != EOF)
                        {
                            if (!seps(c))
                            {
                                token.push_back(c);
                            }
                            else
                            {
                                token=token.substr(0,((int)token.size())-1);
                                sbuf->sungetc();
                                sbuf->sungetc();
                                sbuf->sputbackc(c);
                                return true;                                                      
                            }
                        }
                        return true;
                    }
                    if (!no_punct) sbuf->sungetc();
                    return true;
                }
                if (!no_punct) sbuf->sungetc();
                return true;
                break;
        }
    }
    else
    {
        if (!no_punct) sbuf->sungetc();
        return true;
    }
    return false;
}


bool Tokenizer_fr::proc_empty(string& token, char& c, streambuf* sbuf){
    switch(c)
    {
        case '.':
            if (!no_punct) token.push_back(c);
            if ((c = sbuf->sbumpc()) != EOF)
            {
                if (c == '.')
                {
                    if (!no_punct) token.push_back(c);
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
            break;
        default:
            if (c < 0)
            {
                if (!no_punct) token.push_back(c);
                if ((c = sbuf->sbumpc()) != EOF)
                {
                    if (c < 0)
                    {
                        token.push_back(c);
                        if (token[0] == -62 && token[1] == -85 ) return true;
                        if (token[0] == -62 && token[1] == -96)
                        {
                            token="";
                            return false;
                        }
                    }
                    else
                    {
                        if (!no_punct) c=sbuf->sungetc();
                        return true;
                    }
                      
                      
                }
                if ((c = sbuf->sbumpc()) != EOF)
                {
                    if (c < 0)
                    {
                        if (!no_punct) token.push_back(c);
                    }
                    else
                    {
                        if (!no_punct) c=sbuf->sungetc();
                        return true;
                    }
                }
                return true;
            }
            if (!seps(c) || c=='\n') 
            {
                if (!no_punct) token.push_back(c);
                return true;
            }
            break;
    }
    return false;
}



