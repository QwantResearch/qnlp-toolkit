#ifndef EN_TOKENIZER_H
#define EN_TOKENIZER_H

#include "tokenizer.h"

namespace qnlp {
    
    class Tokenizer_en: public Tokenizer {
        public:
          
            Tokenizer_en (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (syntax, lowercased, underscore, dash, aggressive, nopunct){lang="en";};
        protected:
            bool proc (string& token, char& c, streambuf* sbuf);
            bool proc_empty (string& token, char& c, streambuf* sbuf);
    };
}

#endif // EN_TOKENIZER_H
