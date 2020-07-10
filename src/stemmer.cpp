#include "stemmer.h"

qnlp::Stemmer::Stemmer(const char* lang)
{
//       const char * language = "english";
      const char * charenc = NULL;

    _stemmer = sb_stemmer_new(lang ,charenc);
    if (_stemmer == 0) cerr << "STEMMER ERROR: Unrecognized language"<< endl;
}

const sb_symbol* qnlp::Stemmer::stem(const char* word)
{
    const sb_symbol* to_stem = reinterpret_cast<const unsigned char*>(word);
    return sb_stemmer_stem(_stemmer, to_stem, (int)sizeof(word));
}

string qnlp::Stemmer::stem(string& word)
{
    stringstream ss;
    const sb_symbol* to_stem = reinterpret_cast<const unsigned char*>(word.c_str());
    istringstream l_iss(word);
    ostringstream l_oss;
    l_oss << sb_stemmer_stem(_stemmer, to_stem , (int)word.size());
    return l_oss.str();
}
string qnlp::Stemmer::stem_sentence(string& sentence)
{
    vector<string> sentence_splited;
    string to_return;
    Split(sentence,sentence_splited," ");
    for (int i=0; i<(int)sentence_splited.size(); i++)
    {
        if (i != 0) to_return.append(" ");
        to_return.append(stem(sentence_splited.at(i)));
    }
    return to_return;
}

vector<string> qnlp::Stemmer::stem_sentence_vector(vector<string>& sentence)
{
    vector<string>  to_return;
    for (int i=0; i<(int)sentence.size(); i++)
    {
        to_return.push_back(stem(sentence.at(i)));
    }
    return to_return;
}

qnlp::Stemmer::~Stemmer()
{
    sb_stemmer_delete(_stemmer);
}

void qnlp::Stemmer::stem(istringstream & f_in, ostringstream & f_out)
{
    int lim = 10;
    sb_symbol * b = (sb_symbol *) malloc(lim * sizeof(sb_symbol));
    int pretty=2;
//         unsigned 
        char ch; 
        {
            int i = 0;
            int inlen = 0;
            while (f_in.get(ch))
            {
                if (i == lim) {
                    sb_symbol * newb;
                    newb = (sb_symbol *)
                            realloc(b, (lim + lim) * sizeof(sb_symbol));
                    if (newb == 0) return ;
                    b = newb;
                    lim = lim + lim;
                }
                // Update count of utf-8 characters.
                inlen += 1;
                // force lower case:
                ch = tolower(ch);
                b[i] = ch;
                i++;
            }

            {
                const sb_symbol * stemmed = sb_stemmer_stem(_stemmer, b, i);
                if (stemmed == NULL)
                {
                    cerr << "Out of memory" << endl;
                    exit(1);
                }
                f_out << stemmed;
            }
        }
}


