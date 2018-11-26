#include "en_tokenizer.h"

using namespace qnlp;

bool Tokenizer_en::proc(string& token, char& c) 
{
    int tksize=(int)token.size();
    if (!aggressive)
    {
        if (token.at(0) == '\'' && tksize == 1)
        {
            if (c == 't')
            {
                token.push_back(c);
                return false;
            }
            else
            {
                token=token.substr(0,1);
                sb->sungetc();
                sb->sungetc();
                return true;
            }
        }
        switch(c)
        {
            case '\'':
                token.push_back(c);
                tksize=(int)token.size();
                if ((c = sb->sbumpc()) != EOF)
                {
                    if (tksize == 2 && token[0]=='O')
                    {
                        token.push_back(c);
                        return false;
                    }
                    if (tksize > 2 && c == 't' && token.at((tksize)-2) == 'n')
                    {
                        sb->sungetc();
                        sb->sputbackc('\'');
                        sb->sputbackc('n');
                        if (token.at((tksize)-3) == 'a')
                        {
                                token=token.substr(0,(tksize)-1);
                        }
                        else
                        {
                                token=token.substr(0,(tksize)-2);
                        }
                        return true;
                    }
                    else
                    {
                        if (tksize == 2 && token[0]!='n')
                        {
                            sb->sungetc();
                            return true;
                        }
                        if (tksize > 2 && c=='s')
                        {
                            sb->sungetc();
                            sb->sputbackc('\'');
                            sb->sputbackc('s');
                            token=token.substr(0,(tksize)-1);
                            return true;
                        }
                        if (seps(c))
                        {
                            sb->sungetc();
                            sb->sputbackc('\'');
                            sb->sputbackc(c);
                            token=token.substr(0,((int)token.size())-1);
                            return true;
                        }
                        token.push_back(c);
                        // sb->sungetc();
                        return true;
                    }
                }
                // if (token.at(0) == '\'' 
                sb->sungetc();
                return true;
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
                return true;
                break;
        }
    }
    else
    {
        sb->sungetc();
        return true;
    }
}


bool Tokenizer_en::proc_empty(string& token, char& c)
{
    switch(c)
    {
        case '\'':
            token.push_back(c);
            if ((c = sb->sbumpc()) != EOF)
            {
                if (c == 't' || c == 's')
                {
                    token.push_back(c);
                    char c_tmp=c;
                    if ((c = sb->sbumpc()) != EOF)
                    {
                        if (! seps(c))
                        {
                            sb->sungetc();
                            sb->sputbackc(c_tmp);
                            token=token.substr(0,((int)token.size())-1);
                            return true;
                        }
                    }
                    return true;
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
//                                                     return false;
                    }
                    else
                    {
                        c=sb->sungetc();
//                                         token=token.substr(0,((int)token.size())-1);
                        return true;
                    }
                      
                      
                }
                if ((c = sb->sbumpc()) != EOF)
                {
                    if (c < 0)
                    {
                        token.push_back(c);
//                                                     return false;
                    }
                    else
                    {
                        c=sb->sungetc();
//                                         token=token.substr(0,((int)token.size())-1);
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



