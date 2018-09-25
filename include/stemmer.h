#ifndef STEMMER_H
#define STEMMER_H

#include "libstemmer.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace qnlp {

class Stemmer {
    public:
        /** Constructor of the class Stemmer */
        Stemmer (const char * lang);
        string stem(string word);
        const sb_symbol* stem(const char* word);
        string stem_sentence(string sentence);
        ~Stemmer();
        void stem(istringstream & f_in, ostringstream & f_out);
    private:
        struct sb_stemmer * _stemmer;
}; // class Stemmer

} //namespace qnlp

#endif // STEMMER_H
