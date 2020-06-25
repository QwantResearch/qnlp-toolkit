#ifndef FR_TOKENIZER_H
#define FR_TOKENIZER_H

#include "tokenizer.h"

namespace qnlp {
    
    class Tokenizer_fr: public Tokenizer 
    {
        public:
          
            Tokenizer_fr (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (syntax, lowercased, underscore, dash, aggressive, nopunct){lang="fr";}; // soon deprecated
            Tokenizer_fr (bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (lowercased, underscore, dash, aggressive, nopunct){lang="fr";};
            
        protected:
            bool process_lang(vector<wstring> & vecwtoken) override;
            bool process_cots(vector<wstring>& vecwtoken) override; 
            const vector<wstring> wlang_process = {
//                 L"l'", L"L'", L"d'", L"D'", L"n'", L"N'", L"c'", L"C'", L"t'", L"T'", L"j'", L"J'", L"qu'", L"Qu'", L"s'", L"S'", L"jusqu'", L"Jusqu'", L"lorsqu'", L"Lorsqu'",
                L"aujourd'hui", L"'hui", L"Aujourd'hui", L"d'accord", L"D'accord", 
                L"-dire", L"à-dire", L"-à-dire", L"est-à-dire", L"'est-à-dire", L"c'est-à-dire", L"C'est-à-dire", 
                L"prud'", L"Prud'",L"prud'hommes", L"Prud'hommes", L"prud'homal", L"prud'homale", L"prud'homales", L"prud'homaux", L"Prud'homal", L"Prud'homale", L"Prud'homales", L"Prud'homaux"
                L"'roll", L"'n'roll", L"n'roll", L"rock'n'roll",
            }; 
            
    };
}

#endif // FR_TOKENIZER_H
