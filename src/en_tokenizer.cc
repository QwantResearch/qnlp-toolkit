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
                    if (tksize == 2 && (token[0]=='O' || token[0]=='o'))
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
                            if (token[0]=='I' || token[0]=='i')
                            {
                                sb->sputbackc('\'');
                                token=token.substr(0,(tksize)-1);
                            }
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
                        if (tksize > 2)
                        {
                            if (((token[0]=='Y' || token[0]=='y') && (token[1]=='O' || token[1]=='o') && (token[2]=='U' || token[2]=='u')) || 
                              ((token[0]=='S' || token[0]=='s') && (token[1]=='H' || token[1]=='h') && (token[2]=='E' || token[2]=='e')) ||
                              ((token[0]=='H' || token[0]=='h') && (token[1]=='E' || token[1]=='e'))) 
                            {
                                sb->sungetc();
                                sb->sputbackc('\'');
                                token=token.substr(0,(tksize)-1);
                                return true;
                            }                            
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
                if (c == 't' || c == 's' || c == 'm' || c == 'r')
                {
                    token.push_back(c);
                    char c_tmp=c;
                    if ((c = sb->sbumpc()) != EOF)
                    {
                        if (! seps(c) && c != 'e' )
                        {
                            sb->sungetc();
                            if (c != '\'' )
                            {
                                sb->sputbackc(c_tmp);
                                token=token.substr(0,((int)token.size())-1);
                            }
                            sb->sputbackc(c);
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



