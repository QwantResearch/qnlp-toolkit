#ifndef EN_TOKENIZER_H
#define EN_TOKENIZER_H

#include "tokenizer.h"

namespace qnlp {
    
    class Tokenizer_en: public Tokenizer {
        public:
          
            Tokenizer_en (istream* in, int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true):
                Tokenizer(in, syntax, lowercased, underscore, dash, aggressive){};
            Tokenizer_en (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true):
                Tokenizer (syntax, lowercased, underscore, dash, aggressive){};
        protected:
            bool proc (string& token, char& c);
            bool proc_empty (string& token, char& c);
    };
}

#endif // EN_TOKENIZER_H
