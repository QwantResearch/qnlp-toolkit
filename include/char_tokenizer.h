#ifndef CHAR_TOKENIZER_H
#define CHAR_TOKENIZER_H

#include "tokenizer.h"

namespace qnlp {
    
    class Tokenizer_char: public Tokenizer {
        public:
          
            Tokenizer_char (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (syntax, lowercased, underscore, dash, aggressive, nopunct){lang="en";};
            Tokenizer_char (bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (lowercased, underscore, dash, aggressive, nopunct){lang="car";};
        protected:
            bool process_lang(vector<std::wstring> & vecwtoken) override {return false;};
            bool process_cots(vector<std::wstring> & vecwtoken) override {return false;};
            const vector<wstring> wlang_process = {
            };     
            const vector<wstring> wlang_process_not = {
            };     
            vector<string> tokenize(string& str) override;

            
    };
}

#endif // CHAR_TOKENIZER_H
