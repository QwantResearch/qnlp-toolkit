#include "en_tokenizer.h"

using namespace qnlp;

bool Tokenizer_en::proc(string& token, char& c, streambuf* sbuf) 
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
                sbuf->sungetc();
                sbuf->sungetc();
                return true;
            }
        }
        switch(c)
        {
            case '\'':
                token.push_back(c);
                tksize=(int)token.size();
                if ((c = sbuf->sbumpc()) != EOF)
                {
                    if (tksize == 2 && (token[0]=='O' || token[0]=='o'))
                    {
                        token.push_back(c);
                        return false;
                    }
                    if (tksize > 2 && c == 't' && token.at((tksize)-2) == 'n')
                    {
                        sbuf->sungetc();
                        sbuf->sputbackc('\'');
                        sbuf->sputbackc('n');
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
                            sbuf->sungetc();
                            if (token[0]=='I' || token[0]=='i')
                            {
                                sbuf->sputbackc('\'');
                                token=token.substr(0,(tksize)-1);
                            }
                            return true;
                        }
                        if (tksize > 2 && c=='s')
                        {
                            sbuf->sungetc();
                            sbuf->sputbackc('\'');
                            sbuf->sputbackc('s');
                            token=token.substr(0,(tksize)-1);
                            return true;
                        }
                        if (tksize > 2)
                        {
                            if (((token[0]=='Y' || token[0]=='y') && (token[1]=='O' || token[1]=='o') && (token[2]=='U' || token[2]=='u')) || 
                              ((token[0]=='S' || token[0]=='s') && (token[1]=='H' || token[1]=='h') && (token[2]=='E' || token[2]=='e')) ||
                              ((token[0]=='H' || token[0]=='h') && (token[1]=='E' || token[1]=='e'))) 
                            {
                                sbuf->sungetc();
                                sbuf->sputbackc('\'');
                                token=token.substr(0,(tksize)-1);
                                return true;
                            }                            
                        }
                        if (seps(c))
                        {
                            sbuf->sungetc();
                            sbuf->sputbackc('\'');
                            sbuf->sputbackc(c);
                            token=token.substr(0,((int)token.size())-1);
                            return true;
                        }
                        token.push_back(c);
                        // sbuf->sungetc();
                        return true;
                    }
                }
                // if (token.at(0) == '\'' 
                sbuf->sungetc();
                return true;
            case '.':
                if (dot_proc(token,c,sbuf)) return true;
                else return false;
                break;
            case ',':
                if (comma_proc(token,c,sbuf)) return true;
                else return false;
                break;
            default:
                sbuf->sungetc();
                return true;
                break;
        }
    }
    else
    {
        if (!no_punct) sbuf->sungetc();
        return true;
    }
}


bool Tokenizer_en::proc_empty(string& token, char& c, streambuf* sbuf)
{
    switch(c)
    {
        case '\'':
            token.push_back(c);
            if ((c = sbuf->sbumpc()) != EOF)
            {
                if (c == 't' || c == 's' || c == 'm' || c == 'r')
                {
                    token.push_back(c);
                    char c_tmp=c;
                    if ((c = sbuf->sbumpc()) != EOF)
                    {
                        if (! seps(c) && c != 'e' )
                        {
                            sbuf->sungetc();
                            if (c != '\'' )
                            {
                                sbuf->sputbackc(c_tmp);
                                token=token.substr(0,((int)token.size())-1);
                            }
                            sbuf->sputbackc(c);
                            return true;
                        }
                        else
                        {
                            if (c == 'e') token.push_back(c);
                        }
                        
                    }
                    return true;
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
                token.push_back(c);
                if ((c = sbuf->sbumpc()) != EOF)
                {
                    if (c < 0)
                    {
                        token.push_back(c);
                    }
                    else
                    {
                        c=sbuf->sungetc();
                        return true;
                    }
                      
                      
                }
                if ((c = sbuf->sbumpc()) != EOF)
                {
                    if (c < 0)
                    {
                        token.push_back(c);
                    }
                    else
                    {
                        c=sbuf->sungetc();
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



