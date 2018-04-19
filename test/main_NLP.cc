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


using namespace std;
using namespace qnlp;

// typedef std::vector<uint32_t> value_test;


bool l_aggressive=false;
bool l_underscore=false;
bool l_cased=false;
bool l_dash=false;
string l_lang="";
string l_BPE="";
int l_threads=4;

// HTable<value_test> _ht;

void usage()
{
    cout << 
            "--dash (-d)              split using dashes (default false)\n"
            "--lowercased (-c)        put the sequence in lowercase (default false)\n"
            "--underscore (-u)        split using underscores (default false)\n"
            "--aggressive (-a)        equivalent to --dash and --underscore and every separators\n"
            "--BPE (-B)        equivalent to --dash and --underscore and every separators\n"
            "--lang <val> (-l)        set language (required)\n"
//             "--threads <val> (-t)     set number of threads (default 4)\n"
            "--help (-h)             Show this message\n";
    exit(1);
}

void ProcessArgs(int argc, char** argv)
{
    const char* const short_opts = "dcual:t:h";
    const option long_opts[] = {
            {"dash", 0, nullptr, 'd'},
            {"lowercased", 0, nullptr, 'c'},
            {"underscore", 0, nullptr, 'u'},
            {"aggressive", 0, nullptr, 'a'},
            {"lang", 1, nullptr, 'l'},
            {"BPE", 1, nullptr, 'B'},
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
        case 'd':
            l_dash = true;
            break;

        case 'c':
            l_cased = true;
            break;

        case 'u':
            l_underscore = true;
            break;

        case 'a':
            l_dash = true;
            l_underscore = true;
            l_aggressive = true;
            break;

        case 'l':
            l_lang = optarg;
            break;

        case 'B':
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

int main ( int argc, char *argv[] )
{
    ProcessArgs(argc, argv);
    string l_output;
    vector<string> l_output_vec;
    string l_token_pred;
    stringstream l_out;
    
    if ((int)l_BPE.size() == 0)
    {
        if (l_lang.compare("fr") == 0) 
        {
            Tokenizer_fr l_tokenizer_fr(&cin,Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
            l_output = l_tokenizer_fr.tokenize_to_string();
        }
        else if (l_lang.compare("en") == 0) 
        {
            Tokenizer_en l_tokenizer_en(&cin,Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
            l_output = l_tokenizer_en.tokenize_to_string();
        }
        else
        {
            Tokenizer l_tokenizer(&cin,Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
            l_output = l_tokenizer.tokenize_to_string();
        }
//         if ((int)l_BPE.size() > 0)
//         {
//             BPE bpemodel(l_BPE);
//     //         l_out << " ||| ";
//             l_output = bpemodel.apply_bpe(l_output);
//         }
    }
    else
    {
        if (l_lang.compare("fr") == 0) 
        {
            Tokenizer_fr l_tokenizer_fr(&cin,Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
            l_output_vec = l_tokenizer_fr.tokenize();
        }
        else if (l_lang.compare("en") == 0) 
        {
            Tokenizer_en l_tokenizer_en(&cin,Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
            l_output_vec = l_tokenizer_en.tokenize();
        }
        else
        {
            Tokenizer l_tokenizer(&cin,Tokenizer::PLAIN, l_cased,l_underscore,l_dash, l_aggressive);
            l_output_vec = l_tokenizer.tokenize();
        }
            BPE bpemodel(l_BPE);
            l_output=bpemodel.apply_bpe_to_string(l_output_vec);
    }
    cout << l_output;
    return EXIT_SUCCESS;
}
