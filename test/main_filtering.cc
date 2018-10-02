#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
// #include <boost/program_options.hpp>
// #include "tokenizer.h"
// #include "fr_tokenizer.h"
// #include "en_tokenizer.h"
// #include "bpe.h"
#include "utils.h"


using namespace std;
// using namespace qnlp;

// typedef std::vector<uint32_t> value_test;


// bool l_aggressive=false;
// bool l_underscore=false;
// bool l_cased=false;
// bool l_dash=false;
// bool l_stem=false;
string l_input="";
string l_output="";
string l_src="";
string l_tgt="";
float l_ratio=-1;
int l_minlength=-1;
int l_maxlength=-1;

// HTable<value_test> _ht;

void usage()
{
    cout << 
            "--ratio (-r)              stem outputs (default false)\n"
            "--input (-i)              split using dashes (default false)\n"
            "--output (-o)        put the sequence in lowercase (default false)\n"
            "--source (-s)        split using underscores (default false)\n"
            "--target (-t)        equivalent to --dash and --underscore and every separators\n"
            "--minlength (-l)        split using underscores (default false)\n"
            "--maxlength (-L)        equivalent to --dash and --underscore and every separators\n"
//             "--BPE (-b)               Use Byte Pair Encoding preprocessing\n"
//             "--embmodel (-e)          Load fasttext embeddings/prediction model\n"
//             "--qlassify (-q)          predict class according the model loaded (need embmodel)\n"
//             "--qvectorize (-v)        give vector representation for the sentence/query (need embmodel)\n"
//             "--lang <val> (-l)        set language (required)\n"
//             "--threads <val> (-t)     set number of threads (default 4)\n"
            "--help (-h)             Show this message\n";
    exit(1);
}

void ProcessArgs(int argc, char** argv)
{
    const char* const short_opts = "r:i:o:s:t:h";
    const option long_opts[] = {
            {"ratio", 1, nullptr, 'r'},
            {"input", 1, nullptr, 'i'},
            {"output", 1, nullptr, 'o'},
            {"source", 1, nullptr, 's'},
            {"target", 1, nullptr, 't'},
            {"minlength", 1, nullptr, 'l'},
            {"maxlength", 1, nullptr, 'L'},
//             {"embmodel", 1, nullptr, 'e'},
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
        case 'r':
            l_ratio = atof(optarg);
            break;

        case 'L':
            l_maxlength = atol(optarg);
            break;

        case 'l':
            l_minlength = atol(optarg);
            break;

        case 'i':
            l_input = optarg;
            break;
            
        case 'o':
            l_output = optarg;
            break;

        case 's':
            l_src = optarg;
            break;
            
        case 't':
            l_tgt = optarg;
            break;

        case 'h': // -h or --help
        case '?': // Unrecognized option
        default:
            usage();
            break;
        }
    }
    if (l_input == "" || l_output == "" || l_src == "" || l_tgt == "" || l_minlength < 0 || l_maxlength < 0)
    {
        cerr << "Error" <<endl;
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
    string line_src;
    string line_tgt;
    int length_src;
    int length_tgt;
    vector<string> vec_line_src;
    vector<string> vec_line_tgt;
    string fullinput_src=l_input+"."+l_src;
    string fullinput_tgt=l_input+"."+l_tgt;
    ifstream input_src(fullinput_src,ios::in);
    ifstream input_tgt(fullinput_tgt,ios::in);
    string fulloutput_src=l_output+"."+l_src;
    string fulloutput_tgt=l_output+"."+l_tgt;
    ofstream output_src(fulloutput_src,ios::out);
    ofstream output_tgt(fulloutput_tgt,ios::out);
    long l_input_cpt = 0;
    long l_output_cpt = 0;
    if (input_src && input_tgt)
    {
        getline(input_src,line_src);
        l_input_cpt++;
        Split(line_src,vec_line_src," ");
        getline(input_tgt,line_tgt);
        Split(line_tgt,vec_line_tgt," ");
        length_src=(int)vec_line_src.size();
        length_tgt=(int)vec_line_tgt.size();
        bool l_ratio_bool = true;
        if (l_ratio != -1)
        {
            if ((float)length_src/(float)length_tgt > l_ratio || (float)length_tgt/(float)length_src > l_ratio ) l_ratio_bool = false;
        }
        if (length_src < l_maxlength && length_src > l_minlength && length_tgt < l_maxlength && length_tgt > l_minlength && l_ratio_bool)
        {
            output_src << line_src;
            output_tgt << line_tgt;
            l_output_cpt++;
        }
    }
    input_src.close();
    input_tgt.close();
    output_src.close();
    output_tgt.close();
    cout << "Input sentences: " << l_input_cpt << "  Output sentences: "<< l_output_cpt << endl;
    return EXIT_SUCCESS;
}
