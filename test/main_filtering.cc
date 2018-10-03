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
bool l_gz=false;
bool l_analyse=false;
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
            "--analyse (-a)       analyse corpus length repartition\n"
            "--ratio (-r)         use a length ratio to filter bitext\n"
            "--input (-i)         generic coprus name to read\n"
            "--output (-o)        generic coprus name to write\n"
            "--source (-s)        source language (extention)\n"
            "--target (-t)        target language (extention)\n"
            "--minlength (-l)     min sentence length to filter\n"
            "--maxlength (-L)     min sentence length to filter\n"
            "--gzip (-g)          process gzip files (unavailable)\n"
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
    const char* const short_opts = "agr:i:o:s:l:L:t:h";
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
            {"gzip", 0, nullptr, 'g'},
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
        case 'a':
            l_analyse = true;
            break;
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

        case 'g':
            l_gz = true;
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
    bool l_ratio_bool;
    vector <vector <float>> l_vec_analysis(1000);
    cerr << "qnlp-filtering: processing " << fullinput_src << " & "<< fullinput_tgt << " to " << l_output << ", cutoff " << l_minlength << "-" << l_maxlength << ", ratio" << l_ratio << endl;
    if (input_src && input_tgt)
    {
        while (getline(input_src,line_src) && getline(input_tgt,line_tgt))
        {
            l_input_cpt++;
            if (l_input_cpt % 10000 == 0) cerr << ".";
            if (l_input_cpt % 100000 == 0) cerr << "(" << l_input_cpt << ")";
            vec_line_src.clear();
            vec_line_tgt.clear();
            Split(line_src,vec_line_src," ");
            Split(line_tgt,vec_line_tgt," ");
            length_src=(int)vec_line_src.size();
            length_tgt=(int)vec_line_tgt.size();
            l_ratio_bool = true;
            if (l_analyse)
            {
                if ((int)l_vec_analysis.at(length_src).size() == 0)
                {
                    l_vec_analysis.at(length_src).push_back(1);
                    l_vec_analysis.at(length_src).push_back((float)length_src);
                    l_vec_analysis.at(length_src).push_back((float)length_tgt);
                    if ((float)length_src/(float)length_tgt > l_ratio || (float)length_tgt/(float)length_src > l_ratio )
                    {
                        l_vec_analysis.at(length_src).push_back(1);
                    }
                    else
                    {
                        l_vec_analysis.at(length_src).push_back(0);
                    }
                      
                }
                else
                {
                    l_vec_analysis.at(length_src).at(0)=l_vec_analysis.at(length_src).at(0)+1;
                    l_vec_analysis.at(length_src).at(1)=l_vec_analysis.at(length_src).at(1)+(float)length_src;
                    l_vec_analysis.at(length_src).at(2)=l_vec_analysis.at(length_src).at(2)+(float)length_tgt;
                    if ((float)length_src/(float)length_tgt > l_ratio || (float)length_tgt/(float)length_src > l_ratio )
                    {
                        l_vec_analysis.at(length_src).at(3)=l_vec_analysis.at(length_src).at(3)+1;
                    }
                }
            }
            else
            {
                if (l_ratio != -1)
                {
                    if ((float)length_src/(float)length_tgt > l_ratio || (float)length_tgt/(float)length_src > l_ratio ) l_ratio_bool = false;
                }
                
                if (length_src <= l_maxlength && length_src >= l_minlength && length_tgt <= l_maxlength && length_tgt >= l_minlength && l_ratio_bool)
                {
                    output_src << line_src << endl;
                    output_tgt << line_tgt << endl;
                    l_output_cpt++;
                }
            }
        }
    }
    cerr << endl;
    if (l_analyse)
    {
        for (int i=0; i<(int)l_vec_analysis.size(); i++)
        {
            if ((int)l_vec_analysis.at(i).size() > 0)
            {
                output_src << i << "\t" << l_vec_analysis.at(i).at(0) << "\t" << l_vec_analysis.at(i).at(1) << "\t" << l_vec_analysis.at(i).at(2) << "\t" << l_vec_analysis.at(i).at(2)/l_vec_analysis.at(i).at(1) << "\t" << l_vec_analysis.at(i).at(3) << "\t" << l_vec_analysis.at(i).at(3)/l_vec_analysis.at(i).at(0) << endl;
                output_tgt << i << "\t" << l_vec_analysis.at(i).at(0) << "\t" << l_vec_analysis.at(i).at(1) << "\t" << l_vec_analysis.at(i).at(2) << "\t" << l_vec_analysis.at(i).at(2)/l_vec_analysis.at(i).at(1) << "\t" << l_vec_analysis.at(i).at(3) << "\t" << l_vec_analysis.at(i).at(3)/l_vec_analysis.at(i).at(0) << endl;
            }
        }
    }
    input_src.close();
    input_tgt.close();
    output_src.close();
    output_tgt.close();
    cout << "Input sentences: " << l_input_cpt << "  Output sentences: "<< l_output_cpt << endl;
    return EXIT_SUCCESS;
}
