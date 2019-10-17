#ifndef FR_TOKENIZER_H
#define FR_TOKENIZER_H

#include "tokenizer.h"

namespace qnlp {
    
    class Tokenizer_fr: public Tokenizer {
        public:
          
            Tokenizer_fr (istream* in, int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer(in, syntax, lowercased, underscore, dash, aggressive, nopunct){lang="fr";};
            Tokenizer_fr (int syntax=PLAIN, bool lowercased=true, bool underscore=true, bool dash=true, bool aggressive=true, bool nopunct=true):
                Tokenizer (syntax, lowercased, underscore, dash, aggressive, nopunct){lang="fr";};
            
        protected:
            bool proc (string& token, char& c);
            bool proc_empty (string& token, char& c);
    };
}

#endif // FR_TOKENIZER_H
