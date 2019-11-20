#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <boost/locale.hpp>
#include "utils.h"
using namespace std;

namespace qnlp {

class Tokenizer {
    public:
        enum {PLAIN, XHTML, CARACTER};

        /** Constructor of the class tokenizer */
        Tokenizer (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool noPunct=true):
            syntax(syntax), lowercased(lowercased), underscore(underscore), dash(dash), aggressive(aggressive), no_punct(noPunct)
            {lang="gen";}

        vector<string> tokenize_sentence(string &text);
        string tokenize_sentence_to_string(string &text);
        vector<string> tokenize(streambuf* sbuf);
        string tokenize_to_string(streambuf* sbuf);
        string normalize(string &token);
        vector<string> normalize(vector<string> &vecToken);

        bool read (string &token, bool newdoc, streambuf* sbuf);

        void setParam(bool lowercased, bool underscore, bool dash, bool aggressive, bool noPunct) {
            this->lowercased = lowercased;
            this->underscore = underscore;
            this->dash = dash;
            this->aggressive = aggressive;
            this->no_punct = noPunct;
        }

        void setLowercased(bool lowercased) 
            {this->lowercased =lowercased;}

        void setUnderscore(bool underscore)
            {this->underscore = underscore;}

        void setDash(bool dash)
            {this->dash = dash;}

        void setAggressive(bool aggressive) 
            {this->aggressive = aggressive;}

        void setNoPunct(bool noPunct) 
            {this->no_punct = noPunct;}

        void setSyntax (int syntax)
            {this->syntax = syntax;}

        void setSyntaxFlag (string& flag)
            {this->flag = flag;}

        struct xmlDom {
            string tag;
            string content;
            int status;
        };
        string getlang();

    protected:
        virtual bool proc (string& token, char& c, streambuf* sbuf);
        virtual bool proc_empty (string& token, char& c, streambuf* sbuf);
        string lang;

        int syntax;

        bool lowercased; // set it to true if you want your output to be lowercased
        bool dash; // set it to true if you want to split words with dash
        bool underscore; // set it to true if you want to split words with underscores
        bool aggressive; // set it to true if you want to split words with everyseparators
        bool no_punct; // set it to true if you want to remove everyseparators implies to activate the aggressive mode 

        bool seps_wide (char& c);
        bool seps (char& c);

        void add_seps (char& c, string& lang, string& token);

        bool stopChecker (string& ref, string& leq);
        bool is_abrv (string& token);
        bool is_nbr (string& token);
        bool dot_proc (string& token, char& c, streambuf* sbuf);
        bool comma_proc (string& token, char& c, streambuf* sbuf);
        
        string flag;
        int parserXHTML (char& c, xmlDom& dom, streambuf* sbuf);

        const map<string,string> html_codex = { {"<",">"}, {"<!--","-->"}, {"<!", ">"},
            {"<?", "?>"}, {"</", ">"} };

        const vector<string> abrvs = {"Mme.","Mmes.","Mlle.","Mlles.","MM.","M.","Mr.",
            "Vve.","Dr.","Drs.","Pr.","Prs.","Me.","Mes.","Mgr.","Art.","Fig.","art.",
            "fig.","etc.","e.g.","i.e.","cf.","av.","bc.", "J.C.", "J.-C."};

}; // class Tokenizer

} //namespace qnlp

#endif // TOKENIZER_H
