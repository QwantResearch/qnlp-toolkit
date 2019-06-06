#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
// #include <boost/program_options.hpp>
#include "tokenizer.h"
#include "fr_tokenizer.h"
#include "en_tokenizer.h"
#include "bpe.h"
#include "spm.h"
#include "stemmer.h"
#include "stopwords.h"
#include "utils.h"
#include "generalization.h"


using namespace std;
using namespace qnlp;

// typedef std::vector<uint32_t> value_test;


bool l_aggressive=false;
bool l_underscore=false;
bool l_cased=false;
bool l_dash=false;
bool l_stem=false;
bool l_generalize=false;
bool l_stopwords=false;
bool l_spm_model=false;
string l_lang="";
string l_BPE="";
int l_threads=4;

// HTable<value_test> _ht;

void usage()
{
    cout << 
            "--stem (-s)              stem outputs (default false)\n"
            "--dash (-d)              split using dashes (default false)\n"
            "--lowercased (-c)        put the sequence in lowercase (default false)\n"
            "--underscore (-u)        split using underscores (default false)\n"
            "--stopwords (-w)         remove stopwords (default false)\n"
            "--aggressive (-a)        equivalent to --dash and --underscore and every separators\n"
            "--BPE (-b)               Use Byte Pair Encoding preprocessing\n"
            "--spm (-m)               Use sentencepiece model for Byte Pair Encoding preprocessing\n"
            "--generalize (-g)        remove numbers and replace them with a tag XNUMBER\n"
            "--embmodel (-e)          Load fasttext embeddings/prediction model\n"
            "--qlassify (-q)          predict class according the model loaded (need embmodel)\n"
            "--qvectorize (-v)        give vector representation for the sentence/query (need embmodel)\n"
            "--lang <val> (-l)        set language (required)\n"
//             "--threads <val> (-t)     set number of threads (default 4)\n"
            "--help (-h)             Show this message\n";
    exit(1);
}

void ProcessArgs(int argc, char** argv)
{
    const char* const short_opts = "mgsvwqdcual:b:e:t:h";
    const option long_opts[] = {
            {"stem", 0, nullptr, 's'},
            {"generalize", 0, nullptr, 'g'},
            {"dash", 0, nullptr, 'd'},
            {"lowercased", 0, nullptr, 'c'},
            {"underscore", 0, nullptr, 'u'},
            {"aggressive", 0, nullptr, 'a'},
            {"qclassify", 0, nullptr, 'q'},
            {"qvectorize", 0, nullptr, 'v'},
            {"stopwords", 0, nullptr, 'w'},
            {"lang", 1, nullptr, 'l'},
            {"BPE", 1, nullptr, 'b'},
            {"spm", 0, nullptr, 'm'},
            {"embmodel", 1, nullptr, 'e'},
//             {"threads", 1, nullptr, 't'},
            {"help", 0, nullptr, 'h'},
            {nullptr, 0, nullptr, 0}
    };

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
        case 's':
            l_stem = true;
            break;

        case 'g':
            l_generalize = true;
            break;

        case 'm':
            l_spm_model = true;
            break;

        case 'd':
            l_dash = true;
            break;

        case 'c':
            l_cased = true;
            break;

        case 'u':
            l_underscore = true;
            break;

        case 'w':
            l_stopwords = true;
            break;

        case 'a':
            l_dash = true;
            l_underscore = true;
            l_aggressive = true;
            break;

        case 'l':
            l_lang = optarg;
            break;

        case 'b':
            l_BPE = optarg;
            break;

        case 'h': // -h or --help
        case '?': // Unrecognized option
        default:
            usage();
            break;
        }
    }
    if (l_lang == "")
    {
        cerr << "Error, you must set a lang" <<endl;
        usage();
        exit(1);
    }
}



string stemming(string input , bool l_stemming)
{
    vector<string> line_splited;
    string tmp_output;
    if (l_stemming)
    {
        Stemmer s(l_lang.c_str());
        return s.stem_sentence(input);
    }
    return input;
}
vector<string> stemming(vector<string> &input , bool l_stemming)
{
    if (l_stemming)
    {
        Stemmer s(l_lang.c_str());
        return s.stem_sentence_vector(input);
    }
    return input;
}

vector<string> filtering_stopwords(vector<string> &input , bool l_stopwords)
{
    if (l_stopwords)
    {
        Stopwords sw;
        return sw.filter_stopwords(input,l_lang);
    }
    return input;
}

vector<string> generalize(vector<string> &input , bool l_generalize)
{
    vector<string> tmp;
    if (l_generalize)
    {
        Generalization gen;
//         dcerr << "herre" <<endl;
        tmp=gen.filter_numbers(input);
        return gen.filter_hours(tmp);
    }
    return input;
}

int main ( int argc, char *argv[] )
{
    ProcessArgs(argc, argv);
    string l_output;
    vector<string> l_output_vec;
    string l_token_pred;
    stringstream l_out;
    string line;
    Tokenizer* l_tokenizer;
    BPE* bpemodel;
    spm* spmmodel;
    if (l_lang.compare("fr") == 0) 
    {
        l_tokenizer = new Tokenizer_fr(Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
//             l_output_vec = l_tokenizer_fr.tokenize_sentence(to_tokenize);
    }
    else if (l_lang.compare("en") == 0) 
    {
        l_tokenizer = new Tokenizer_en(Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
//             l_output_vec = l_tokenizer_en.tokenize_sentence(to_tokenize);
    }
    else if (l_lang.compare("car") == 0) 
    {
        l_tokenizer = new Tokenizer(Tokenizer::CARACTER, l_cased,l_underscore,l_dash, l_aggressive);
//             l_output_vec = l_tokenizer.tokenize_sentence(to_tokenize);
    }
    else
    {
        l_tokenizer = new Tokenizer(Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
    }
    if ((int)l_BPE.size() != 0)
    {
        if (! l_spm_model)
        {
            bpemodel = new BPE(l_BPE);
        }
        else
        {
            spmmodel = new spm(l_BPE);
        }
    }
    while (std::getline(std::cin, line))
    {
        string to_tokenize=line;
        l_output_vec = l_tokenizer->tokenize_sentence(to_tokenize);
        l_output_vec = stemming(l_output_vec,l_stem);
        l_output_vec = filtering_stopwords(l_output_vec,l_stopwords);
        l_output_vec = generalize(l_output_vec,l_generalize);
        if ((int)l_BPE.size() != 0)
        {
            if (! l_spm_model)
            {
//                BPE = new bpemodel(l_BPE);
                l_output=bpemodel->apply_bpe_to_string(l_output_vec);
            }
            else
            {
                l_output=spmmodel->segment_str(l_output_vec);
            }
            
        }
        else
        {
            l_output=qnlp::Join(l_output_vec," ");      
        }
        cout << l_output << endl;
    }
    delete(l_tokenizer);
    return EXIT_SUCCESS;
}
