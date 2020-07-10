#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <boost/locale.hpp>
#include "utils.h"
using namespace std;

namespace qnlp {

class Tokenizer {
    public:
        enum {PLAIN, XHTML, CARACTER};

        /** Constructor of the class tokenizer */
        Tokenizer (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool noPunct=true):
            syntax(syntax), lowercased(lowercased), underscore(underscore), dash(dash), aggressive(aggressive), no_punct(noPunct) // soon deprecated
            {lang="gen";cot_regex=new regex("[ ]*'[ ]*");}
        Tokenizer (bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool noPunct=true):
            lowercased(lowercased), underscore(underscore), dash(dash), aggressive(aggressive), no_punct(noPunct)
            {lang="gen";cot_regex=new regex("[ ]*'[ ]*");}
        ~Tokenizer() {delete cot_regex ;}
        string tokenize_sentence_to_string(string & str);
        string detokenize_sentence_to_string(string & str);
        virtual vector<string> tokenize(string & str);
        vector<string> tokenize_sentence(string & str) {return tokenize(str);};
        string normalize(string &token);
        vector<string> normalize(vector<string> &vecToken);
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
        virtual bool process_lang (vector<wstring>& vecwtoken);
        virtual bool process_cots(vector<wstring>& vecwtoken); 
        const vector<wstring> wlang_process;
        
        string lang;

        int syntax;

        bool lowercased; // set it to true if you want your output to be lowercased
        bool dash; // set it to true if you want to split words with dash
        bool underscore; // set it to true if you want to split words with underscores
        bool aggressive; // set it to true if you want to split words with everyseparators
        bool no_punct; // set it to true if you want to remove everyseparators implies to activate the aggressive mode 

        bool seps_wide (char& c);
        bool seps (char& c);
        bool seps_wide (unsigned char& c);
        bool seps (unsigned char& c);
        bool seps_wide (unsigned int& c);
        bool seps (unsigned int& c);

        bool seps_wide (unsigned short& c);
        bool seps (unsigned short& c);

        void add_seps (char& c, string& lang, string& token);

        bool stopChecker (string& ref, string& leq);
        bool is_abrv (string& token);
        bool is_nbr (string& token);
        bool is_nbr (wstring& wtoken);
        bool is_separator (wstring& wtoken);
        bool is_separator (string& token);
        bool process_numbers(vector<wstring>& vecwtoken);
        
        bool process_dots(vector<wstring>& vecwtoken);
        bool process_acronym(vector<wstring>& vecwtoken);
        bool process_ldots(vector<wstring>& vecwtoken);
        bool process_final_dots(vector<wstring>& vecwtoken);
        bool process_abrv(vector<wstring>& vecwtoken);
        bool process_lowercase(vector<wstring>& vecwtoken);
        bool print_vector(vector<wstring>& vecwtoken);
        vector<wstring> clean_vector(vector<wstring>& vecwtoken);
        
        
        string flag;
        const map<string,string> html_codex = { {"<",">"}, {"<!--","-->"}, {"<!", ">"},
            {"<?", "?>"}, {"</", ">"} };

        const vector<string> abrvs = {"Mme.","Mmes.","Mlle.","Mlles.","MM.","M.","Mr.",
            "Vve.","Dr.","Drs.","Pr.","Prs.","Me.","Mes.","Mgr.","Art.","Fig.","art.",
            "fig.","etc.","e.g.","i.e.","cf.","av.","bc.", "J.C.", "J.-C."};
        const vector<wstring> wabrvs = {L"Mme.",L"Mmes.",L"Mlle.",L"Mlles.",L"MM.",L"Mr.", 
            L"Vve.",L"Dr.",L"Drs.",L"Pr.",L"Prs.",L"Me.",L"Mes.",L"Mgr.",L"Art.",L"Fig.",L"art.",
            L"fig.",L"etc.",L"e.g.",L"i.e.",L"cf.",L"av.",L"bc.",L"J.C.",L"J.-C.",L".-C",L"J.-C",
            L"J.S.",L"J.-S.",L".-S",L"J.-S",
            L"vs.", L"Vs.", L"v.",
            L"st.", L"St.",
            L"inc.", L"Inc.",
            L".g",L"e.g",L".e",L"i.e",L"p.ex.",L"p.ex",L".ex",L"P.ex.",L"P.ex",L".ex",L"P.EX.",L"P.EX",L".EX",
            L"R&D",L"&D",
            L"Jr.", L"Sr.",L"O'",L"Bros.",
            L"pm.", L"am.", L"p.m.", L"a.m.", L".m", L"p.m", L"a.m",
        };
        
        std::regex * cot_regex;
//             ,L"M."

}; // class Tokenizer

} //namespace qnlp

#endif // TOKENIZER_H
