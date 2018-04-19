#include "en_tokenizer.h"

using namespace qnlp;

bool Tokenizer_en::proc(string& token, char& c) {
    if (!aggressive) {
        if (token.at(0) == '\'' && token.size() == 1) {
            if (c == 't') {
                token.push_back(c);
                return false;

            } else {
                token = token.substr(0,1);
                sb->sungetc();
                sb->sungetc();
                return true;
            }
        }

        switch(c) {
            case '\'':
                token.push_back(c);
                if ((c = sb->sbumpc()) != EOF && token.size() > 2) {
                    if (c == 't' && token.at(token.size()-2) == 'n') {
                        sb->sungetc();
                        sb->sputbackc('\'');
                        sb->sputbackc('n');

                        if (token.at(token.size()-3) == 'a')
                            token=token.substr(0,token.size()-1);
                        else
                            token=token.substr(0,token.size()-2);

                        return true;
                    } else {
                        token.push_back(c);
                        return true;
                    }
                }
                sb->sungetc();
                return true;

            case '.':
                if (dot_proc(token,c)) return true;
                else return false;

            case ',':
                if (comma_proc(token,c)) return true;
                else return false;

            default:
                sb->sungetc();
                return true;
        }

    } else {
        sb->sungetc();
        return true;
    }
}


bool Tokenizer_en::proc_empty(string& token, char& c)
{
    switch(c) {
        case '\'':
            token.push_back(c);
            if ((c = sb->sbumpc()) != EOF) {
                if (c == 't' || c == 's') {
                    token.push_back(c);
                    return false;
                } else {
                    sb->sungetc();
                    return true;
                }
            } else {
                return true;
            }

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
                        c=sb->sungetc();
                        return true;
                    }
                }

                return true;
            }

            if (!seps(c) || c=='\n') {
                token.push_back(c);
                return true;
            }

            break;
    }    

    return false;
}


