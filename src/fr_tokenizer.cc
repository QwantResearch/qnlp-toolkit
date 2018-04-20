#include "fr_tokenizer.h"

using namespace qnlp;

bool Tokenizer_fr::proc(string& token, char& c) {
    if (!aggressive)
    {
        if (is_nbr(token)) 
        {
            if ((int)token.size() >= 2 && token[(int)token.size()-2] <= '\x039' && token[(int)token.size()-2] >= '\x030' && token[(int)token.size()-1] == '.')
            {
                char l_char=token.substr((int)token.size()-1,1)[0];
                token=token.substr(0,(int)token.size()-1);
                c=sb->sungetc();
                c=sb->sungetc();
                sb->sputbackc(l_char);
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
                if ((int)token.size() >= 3) {token=token.substr(0,((int)token.size())-1);sb->sungetc();return true;}
                break;
            case '.':
                if (dot_proc(token,c)) return true;
                else return false;
            case ',':
                if (comma_proc(token,c)) return true;
                else return false;
                break;
            default:
                if (c < 0)
                {
                    if (c == -30 && (int)token.size() == 1)
                    {
                        token.push_back(c);
                        if ((c = sb->sbumpc()) != EOF)
                        {
                            if (!seps(c))
                            {
                                token.push_back(c);
                            }
                            else
                            {
                                token=token.substr(0,((int)token.size())-1);
                                sb->sungetc();
                                sb->sungetc();
                                sb->sputbackc(c);
                                return true;                                                      
                            }
                        }
                        if ((c = sb->sbumpc()) != EOF)
                        {
                            if (!seps(c))
                            {
                                token.push_back(c);
                            }
                            else
                            {
                                token=token.substr(0,((int)token.size())-1);
                                sb->sungetc();
                                sb->sungetc();
                                sb->sputbackc(c);
                                return true;                                                      
                            }
                        }
                        return true;
                    }
                    sb->sungetc();
                    return true;
                }
                sb->sungetc();
                return true;
                break;
        }
    }
    else
    {
        sb->sungetc();
        return true;
    }
    return false;
}


bool Tokenizer_fr::proc_empty(string& token, char& c){
    switch(c)
    {
        case '.':
            token.push_back(c);
            if ((c = sb->sbumpc()) != EOF)
            {
                if (c == '.')
                {
                    token.push_back(c);
                    return false;
                }
                else
                {
                    sb->sungetc();
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
                token.push_back(c);
                if ((c = sb->sbumpc()) != EOF)
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
                        c=sb->sungetc();
                        return true;
                    }
                      
                      
                }
                if ((c = sb->sbumpc()) != EOF)
                {
                    if (c < 0)
                    {
                        token.push_back(c);
                    }
                    else
                    {
                        c=sb->sungetc();
                        return true;
                    }
                }
                return true;
            }
            if (!seps(c) || c=='\n') 
            {
                token.push_back(c);
                return true;
            }
            break;
    }
    return false;
}



