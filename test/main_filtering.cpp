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
using namespace qnlp;

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
float l_maxpc=-1;
int l_minlength=-1;
int l_maxlength=-1;

// HTable<value_test> _ht;

void usage()
{
    cout << 
            "--analyse (-a)       analyse corpus length repartition\n"
            "--Automation (-A)    analyse corpus length repartition and automatically cutting according the percentage filtered\n"
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
    const char* const short_opts = "agr:i:o:s:l:L:A:t:h";
    const option long_opts[] = {
            {"ratio", 1, nullptr, 'r'},
            {"input", 1, nullptr, 'i'},
            {"output", 1, nullptr, 'o'},
            {"source", 1, nullptr, 's'},
            {"target", 1, nullptr, 't'},
            {"minlength", 1, nullptr, 'l'},
            {"maxlength", 1, nullptr, 'L'},
            {"Automation", 1, nullptr, 'A'},
//             {"embmodel", 1, nullptr, 'e'},
//             {"threads", 1, nullptr, 't'},
            {"analyse", 0, nullptr, 'a'},
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

        case 'A':
            l_maxpc = atof(optarg);
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
        cerr << "Input file:\t" <<l_input << endl << "Output file:\t" <<  l_output << endl << "Source language:\t" <<  l_src << endl << "Target language:\t" <<  l_tgt << endl << "Minimum length:\t" <<  l_minlength << endl << "Maximum length:\t" <<  l_maxlength << endl;
        usage();
        exit(1);
    }
}


int main ( int argc, char *argv[] )
{
    ProcessArgs(argc, argv);
    int max_length=1000;
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
    if (l_maxpc != -1 )
    {
        fulloutput_src=l_output+"."+l_src+".analysis";
        fulloutput_tgt=l_output+"."+l_tgt+".analysis";
        cerr << "qnlp-filtering: analysing " << fullinput_src << " & "<< fullinput_tgt << endl;
    }
    else
    {
          cerr << "qnlp-filtering: processing " << fullinput_src << " & "<< fullinput_tgt << " to " << l_output << ", cutoff " << l_minlength << "-" << l_maxlength << ", ratio " << l_ratio << endl;
    }
    ofstream output_src(fulloutput_src,ios::out);
    ofstream output_tgt(fulloutput_tgt,ios::out);
    long l_input_cpt = 0;
    long l_output_cpt = 0;
    bool l_ratio_bool;
    vector <vector <float>> l_vec_analysis(max_length);
    vector <vector <float>> l_vec_analysis_rev(max_length);
    vector <float> l_vec_cut_off(max_length,0.0);
    vector <float> l_vec_cut_off_rev(max_length,0.0);
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
            if (length_src < max_length && length_tgt < max_length)
            {
                if (l_maxpc != -1 )
                {
                    if ((int)l_vec_analysis.at(length_src).size() == 0)
                    {
                        l_vec_analysis.at(length_src).push_back(1);
                        l_vec_analysis.at(length_src).push_back((float)length_src);
                        l_vec_analysis.at(length_src).push_back((float)length_tgt);
                        for (l_ratio = 1.0 ; l_ratio < 3.0 ; l_ratio=l_ratio+0.1)
                        {
                            if ((float)length_src/(float)length_tgt > l_ratio || (float)length_tgt/(float)length_src > l_ratio )
                            {
                                l_vec_analysis.at(length_src).push_back(1);
                            }
                            else
                            {
                                l_vec_analysis.at(length_src).push_back(0);
                            }
                        }
                    }
                    else
                    {
                        l_vec_analysis.at(length_src).at(0)=l_vec_analysis.at(length_src).at(0)+1;
                        l_vec_analysis.at(length_src).at(1)=l_vec_analysis.at(length_src).at(1)+(float)length_src;
                        l_vec_analysis.at(length_src).at(2)=l_vec_analysis.at(length_src).at(2)+(float)length_tgt;
                        int j=3;
                        for (l_ratio = 1.0 ; l_ratio < 3.0 ; l_ratio=l_ratio+0.1)
                        {
                            if ((float)length_src/(float)length_tgt > l_ratio || (float)length_tgt/(float)length_src > l_ratio )
                            {
                                l_vec_analysis.at(length_src).at(j)=l_vec_analysis.at(length_src).at(j)+1;
                            }
                            j++;
                        }
                    }
                    if ((int)l_vec_analysis_rev.at(length_tgt).size() == 0)
                    {
                        l_vec_analysis_rev.at(length_tgt).push_back(1);
                        l_vec_analysis_rev.at(length_tgt).push_back((float)length_tgt);
                        l_vec_analysis_rev.at(length_tgt).push_back((float)length_src);
                        for (l_ratio = 1.0 ; l_ratio < 3.0 ; l_ratio=l_ratio+0.1)
                        {
                            if ((float)length_tgt/(float)length_src > l_ratio || (float)length_src/(float)length_tgt > l_ratio )
                            {
                                l_vec_analysis_rev.at(length_tgt).push_back(1);
                            }
                            else
                            {
                                l_vec_analysis_rev.at(length_tgt).push_back(0);
                            }
                        }
                    }
                    else
                    {
                        l_vec_analysis_rev.at(length_tgt).at(0)=l_vec_analysis_rev.at(length_tgt).at(0)+1;
                        l_vec_analysis_rev.at(length_tgt).at(1)=l_vec_analysis_rev.at(length_tgt).at(1)+(float)length_tgt;
                        l_vec_analysis_rev.at(length_tgt).at(2)=l_vec_analysis_rev.at(length_tgt).at(2)+(float)length_src;
                        int j=3;
                        for (l_ratio = 1.0 ; l_ratio < 3.0 ; l_ratio=l_ratio+0.1)
                        {
                            if ((float)length_tgt/(float)length_src > l_ratio || (float)length_src/(float)length_tgt > l_ratio )
                            {
                                l_vec_analysis_rev.at(length_tgt).at(j)=l_vec_analysis_rev.at(length_tgt).at(j)+1;
                            }
                            j++;
                        }
                    }
                }
                else if (l_analyse)
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
                    if ((int)l_vec_analysis_rev.at(length_tgt).size() == 0)
                    {
                        l_vec_analysis_rev.at(length_tgt).push_back(1);
                        l_vec_analysis_rev.at(length_tgt).push_back((float)length_tgt);
                        l_vec_analysis_rev.at(length_tgt).push_back((float)length_src);
                        if ((float)length_tgt/(float)length_src > l_ratio || (float)length_src/(float)length_tgt > l_ratio )
                        {
                            l_vec_analysis_rev.at(length_tgt).push_back(1);
                        }
                        else
                        {
                            l_vec_analysis_rev.at(length_tgt).push_back(0);
                        }
                    }
                    else
                    {
                        l_vec_analysis_rev.at(length_tgt).at(0)=l_vec_analysis_rev.at(length_tgt).at(0)+1;
                        l_vec_analysis_rev.at(length_tgt).at(1)=l_vec_analysis_rev.at(length_tgt).at(1)+(float)length_tgt;
                        l_vec_analysis_rev.at(length_tgt).at(2)=l_vec_analysis_rev.at(length_tgt).at(2)+(float)length_src;
                        if ((float)length_tgt/(float)length_src > l_ratio || (float)length_src/(float)length_tgt > l_ratio )
                        {
                            l_vec_analysis.at(length_tgt).at(3)=l_vec_analysis.at(length_tgt).at(3)+1;
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
    }
    cerr << endl;
    if (l_analyse || l_maxpc > -1)
    {
        for (int i=0; i<(int)l_vec_analysis.size(); i++)
        {
            if ((int)l_vec_analysis.at(i).size() > 0)
            {
                output_src << i << "\t" << l_vec_analysis.at(i).at(0) << "\t" << l_vec_analysis.at(i).at(1) << "\t" << l_vec_analysis.at(i).at(2) << "\t" << l_vec_analysis.at(i).at(2)/l_vec_analysis.at(i).at(1) << "\t" ;
                int j=3;
                while (j<(int)l_vec_analysis.at(i).size())
                {
                    output_src << l_vec_analysis.at(i).at(j) << "\t" << l_vec_analysis.at(i).at(j)/l_vec_analysis.at(i).at(0) << "\t";
                    if ((l_vec_analysis.at(i).at(j)/l_vec_analysis.at(i).at(0) < l_maxpc) && (l_vec_cut_off.at(i) == 0))
                    {
                        
                        l_vec_cut_off.at(i)=((float)(j-3)+10.0)/10.0;
                    }
                    j++;
                }
                if (l_vec_cut_off.at(i)==0) l_vec_cut_off.at(i)=max_length;
                output_src << endl;
            }
        }
        for (int i=0; i<(int)l_vec_cut_off.size(); i++)
        {
            if (l_vec_cut_off.at(i) != 0.0)
            {
                output_src << i << "|" << l_vec_cut_off.at(i) << "\t" ;
            }
        }
        output_src << endl;
        for (int i=0; i<(int)l_vec_analysis_rev.size(); i++)
        {
            if ((int)l_vec_analysis_rev.at(i).size() > 0)
            {
                output_tgt << i << "\t" << l_vec_analysis_rev.at(i).at(0) << "\t" << l_vec_analysis_rev.at(i).at(1) << "\t" << l_vec_analysis_rev.at(i).at(2) << "\t" << l_vec_analysis_rev.at(i).at(2)/l_vec_analysis_rev.at(i).at(1) << "\t" ;
                int j=3;
                while (j<(int)l_vec_analysis_rev.at(i).size())
                {
                    output_tgt << l_vec_analysis_rev.at(i).at(j) << "\t" << l_vec_analysis_rev.at(i).at(j)/l_vec_analysis_rev.at(i).at(0) << "\t";
                    if ((l_vec_analysis_rev.at(i).at(j)/l_vec_analysis_rev.at(i).at(0) < l_maxpc) && (l_vec_cut_off_rev.at(i) == 0))
                    {
                        
                        l_vec_cut_off_rev.at(i)=((float)(j-3)+10.0)/10.0;
                    }
                    j++;
                }
                if (l_vec_cut_off_rev.at(i)==0) l_vec_cut_off_rev.at(i)=max_length;
                output_tgt << endl;
            }
        }
        for (int i=0; i<(int)l_vec_cut_off_rev.size(); i++)
        {
            if (l_vec_cut_off_rev.at(i) != 0.0)
            {
                output_tgt << i << "|" << l_vec_cut_off_rev.at(i) << "\t" ;
            }
        }
        output_tgt << endl;
    }
    input_src.close();
    input_tgt.close();
    output_src.close();
    output_tgt.close();
    if (l_maxpc > -1)
    {
        cerr << "qnlp-filtering: processing " << fullinput_src << " & "<< fullinput_tgt << " to " << l_output << ", cutoff " << l_minlength << "-" << l_maxlength << ", automatic ratio " << endl;
        ifstream input_new_src(fullinput_src,ios::in);
        ifstream input_new_tgt(fullinput_tgt,ios::in);
        string fulloutput_new_src=l_output+"."+l_src;
        string fulloutput_new_tgt=l_output+"."+l_tgt;
        ofstream output_new_src(fulloutput_new_src,ios::out);
        ofstream output_new_tgt(fulloutput_new_tgt,ios::out);
        l_input_cpt=0;
        if (input_new_src && input_new_tgt)
        {
            while (getline(input_new_src,line_src) && getline(input_new_tgt,line_tgt))
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
                if (length_src < max_length && length_tgt < max_length)
                {
                    l_ratio = l_vec_cut_off.at(length_src);
                    if (l_ratio > l_vec_cut_off_rev.at(length_tgt)) l_ratio = l_vec_cut_off_rev.at(length_tgt);
                    if ((float)length_src/(float)length_tgt > l_ratio || (float)length_tgt/(float)length_src > l_ratio ) l_ratio_bool = false;
                    if (length_src <= l_maxlength && length_src >= l_minlength && length_tgt <= l_maxlength && length_tgt >= l_minlength && l_ratio_bool)
                    {
                        output_new_src << line_src << endl;
                        output_new_tgt << line_tgt << endl;
                        l_output_cpt++;
                    }
                }
            }
        }
        input_new_src.close();
        input_new_tgt.close();
        output_new_src.close();
        output_new_tgt.close();
        cerr << endl;
    }      
    cout << "Input sentences: " << l_input_cpt << "  Output sentences: "<< l_output_cpt << " (" << 100.0*(float)l_output_cpt/(float)l_input_cpt << "%)" << endl;
    return EXIT_SUCCESS;
}
