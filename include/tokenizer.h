#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <boost/locale.hpp>

using namespace std;

namespace qnlp {

class Tokenizer {
    public:
        enum {PLAIN, XHTML};

        /** Constructor of the class tokenizer */
        Tokenizer (istream* in, int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true):
            in(in), syntax(syntax), lowercased(lowercased), underscore(underscore), dash(dash), aggressive(aggressive)
            {sb = in->rdbuf();}

        Tokenizer (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true):
            syntax(syntax), lowercased(lowercased), underscore(underscore), dash(dash), aggressive(aggressive)
            {istringstream iss("");sb = iss.rdbuf();}

        vector<string> tokenize_sentence(string &text);
        string tokenize_sentence_to_string(string &text);
        vector<string> tokenize(void);
        string tokenize_to_string(void);
        string normalize(string &token);
        vector<string> normalize(vector<string> &vecToken);

        bool read (string &token, bool newdoc);

        void setParam(bool lowercased, bool underscore, bool dash, bool aggressive) {
            this->lowercased = lowercased;
            this->underscore = underscore;
            this->dash = dash;
            this->aggressive = aggressive;
        }

        void setLowercased(bool lowercased) 
            {this->lowercased =lowercased;}

        void setUnderscore(bool underscore)
            {this->underscore = underscore;}

        void setDash(bool dash)
            {this->dash = dash;}

        void setAggressive(bool aggressive) 
            {this->aggressive = aggressive;}

        void setSyntax (int syntax)
            {this->syntax = syntax;}

        void setSyntaxFlag (string& flag)
            {this->flag = flag;}

        struct xmlDom {
            string tag;
            string content;
            int status;
        };

    protected:
        virtual bool proc (string& token, char& c);
        virtual bool proc_empty (string& token, char& c);

        istream* in;
        streambuf* sb;
        int syntax;

        bool lowercased; // set it to true if you want your output to be lowercased
        bool dash; // set it to true if you want to split words with dash
        bool underscore; // set it to true if you want to split words with underscores
        bool aggressive; // set it to true if you want to split words with everyseparators
        bool do_read;

        bool seps_wide (char& c);
        bool seps (char& c);

        void add_seps (char& c, string& lang, string& token);

        bool stopChecker (string& ref, string& leq);
        bool is_abrv (string& token);
        bool is_nbr (string& token);
        bool dot_proc (string& token, char& c);
        bool comma_proc (string& token, char& c);
        
        string flag;
        int parserXHTML (char& c, xmlDom& dom);

        const map<string,string> html_codex = { {"<",">"}, {"<!--","-->"}, {"<!", ">"},
            {"<?", "?>"}, {"</", ">"} };

        const vector<string> abrvs = {"Mme.","Mmes.","Mlle.","Mlles.","MM.","M.","Mr.",
            "Vve.","Dr.","Drs.","Pr.","Prs.","Me.","Mes.","Mgr.","Art.","Fig.","art.",
            "fig.","etc.","e.g.","i.e.","cf.","av.","bc.", "J.C.", "J.-C."};

}; // class Tokenizer

} //namespace qnlp

#endif // TOKENIZER_H
