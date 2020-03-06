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
            bool process_lang(vector<std::__cxx11::wstring> & vecwtoken) override;
            const vector<wstring> wlang_process = {L"l'", L"L'", L"d'", L"D'", L"n'", L"N'", 
                L"aujourd'hui", L"'hui", L"Aujourd'hui", L"c'", L"C'", L"d'accord", L"D'accord", L"qu'", L"Qu'", L"t'", L"T'",
                L"s'", L"S'", L"n'", L"N'", L"'roll", L"'n'roll", L"n'roll", L"rock'n'roll",
            }; 
            
    };
}

#endif // FR_TOKENIZER_H
