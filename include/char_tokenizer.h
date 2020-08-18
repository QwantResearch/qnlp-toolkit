#ifndef CHAR_TOKENIZER_H
#define CHAR_TOKENIZER_H

#include "tokenizer.h"

namespace qnlp {
    
    class Tokenizer_char: public Tokenizer {
        public:
          
            Tokenizer_char (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (syntax, lowercased, underscore, dash, aggressive, nopunct){lang="en";};
            Tokenizer_char (bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (syntax, lowercased, underscore, dash, aggressive, nopunct){lang="car";};
        protected:
//             bool process_lang(vector<std::__cxx11::wstring> & vecwtoken) override;
//             const vector<wstring> wlang_process = {L"'s", L"'t", L"'ll", L"'roll", L"'n'roll", L"n'roll", L"rock'n'roll",
//             };     
//             const vector<wstring> wlang_process_not = {L"don't", L"isn't", L"didn't",
//             };     
            vector<string> tokenize(string& str) override;

            
    };
}

#endif // CHAR_TOKENIZER_H
