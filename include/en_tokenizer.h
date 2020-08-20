#ifndef QNLP_EN_TOKENIZER_H
#define QNLP_EN_TOKENIZER_H

#include "tokenizer.h"

namespace qnlp {
    
    class Tokenizer_en: public Tokenizer {
        public:
          
            Tokenizer_en (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (syntax, lowercased, underscore, dash, aggressive, nopunct){lang="en";};
            Tokenizer_en (bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (lowercased, underscore, dash, aggressive, nopunct){lang="en";};
        protected:
            bool process_lang(vector<wstring> & vecwtoken) override;
            const vector<wstring> wlang_process = {L"'s", L"'t", L"'ll", L"'roll", L"'n'roll", L"n'roll", L"rock'n'roll", L"n'b",  L"n'B", L"'n'b",  L"'n'B", L"r'n'b",  L"R'n'B", 
            };     
            const vector<wstring> wlang_process_not = {L"don't", L"isn't", L"didn't",
            };     
    };
}

#endif // QNLP_EN_TOKENIZER_H
