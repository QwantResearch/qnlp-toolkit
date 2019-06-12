/***************************************************************************
* MIT License
* 
* Copyright (c) 2018 Christophe SERVAN, Qwant Research, 
* email: christophe[dot]servan[at]qwantresearch[dot]com
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
***************************************************************************/
#include "spm.h"

using namespace qnlp;

spm::spm(std::string& modelpath)
{
    const sentencepiece::util::Status status = _processor.Load(modelpath);
    if (!status.ok()) 
    {
        std::cerr << "Error while loading SentencePiece model: " << modelpath << std::endl;
        exit(1);
    }
}

std::vector< std::string > spm::segment(std::string& sentence)
{
    std::vector<std::string> to_return;
    _processor.Encode(sentence, &to_return);
    return to_return;
}

std::string spm::decode(std::vector<std::string>& vec_sentence)
{
    std::string to_return;
    const char specialChar[] = "\xe2\x96\x81";
    _processor.Decode(vec_sentence, &to_return);
    while((int)to_return.find(specialChar)>-1)
    {
        to_return=to_return.replace((int)to_return.find(specialChar),(int)strlen(specialChar)," ");
    }
    if (to_return[0]==' ')
    {
        to_return=to_return.substr(1,(int)to_return.length()-1);
    }
    return to_return;
}
std::string spm::segment_str(std::string& sentence)
{
    std::vector< std::string > to_process = segment(sentence);
    std::stringstream to_return;
    for (int i=0; i < (int)to_process.size(); i++)
    {
        if (i != 0) to_return << " " << to_process[i];
        else to_return  << to_process[i];
    }
    return to_return.str();
}
std::vector< std::string > spm::segment(std::vector< std::string >& sentence)
{
    std::vector<std::string> to_return;
    std::vector<std::string> l_tmp;
    for (int i=0; i < (int)sentence.size(); i++)
    {
        l_tmp.clear();
        _processor.Encode(sentence[i], &l_tmp);
        to_return.insert( to_return.end(), l_tmp.begin(), l_tmp.end() );
    }
    return to_return;
}
std::string spm::segment_str(std::vector< std::string >& sentence)
{
    std::vector< std::string > to_process = segment(sentence);
    std::stringstream to_return;
    for (int i=0; i < (int)to_process.size(); i++)
    {
        if (i != 0) to_return << " " << to_process[i];
        else to_return  << to_process[i];
    }
    return to_return.str();
}


