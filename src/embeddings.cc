#include "embeddings.h"

using namespace qnlp;

Embeddings::Embeddings(string& filename)
{
    
    _embmodel.loadModel(filename);
    _dict = _embmodel.getDictionary();
//      _wordVectors = new fasttext::Matrix(_dict->nwords(), _embmodel.getDimension());
     _wordVectors = std::unique_ptr<fasttext::DenseMatrix>(new fasttext::DenseMatrix(_dict->nwords(), _embmodel.getDimension()));
//     _embmodel.precomputeWordVectors((*_wordVectors));
}

Embeddings::Embeddings(void)
{
//     _embmodel= new fasttext::FastText();
//     _wordVectors= new fasttext::Matrix();
//     _dict = make_shared<fasttext::Dictionary>(); 
}

void Embeddings::getWordVector(string& word, fasttext::Vector &wordVector)
{
//     fasttext::Vector wordVectorToReturn(_embmodel.getDimension());
    _embmodel.getWordVector(wordVector, word);
//     wordVector=wordVectorToReturn;
//     return wordVectorToReturn;
}
void Embeddings::getSentenceVector(string& sentence, fasttext::Vector& sentenceVector)
{
// //     fasttext::Vector sentenceVector(_embmodel.getDimension());
    std::istringstream issSentence(sentence);
    _embmodel.getSentenceVector(issSentence, sentenceVector);
//     return sentenceVector;
}

vector< pair< fasttext::real, string > > Embeddings::queryWords(string& word,int nbest)
{
    return _embmodel.getNN(word,nbest);
//     fasttext::Vector wordVector(_embmodel.getDimension());
//     std::set<std::string> banSet;
//     banSet.clear();
//     banSet.insert(word);
//     _embmodel.getWordVector(wordVector, word);
//     return queryWords(wordVector,banSet,nbest);
  
}

vector< pair< fasttext::real, string > > Embeddings::queryWords(fasttext::Vector& wordVector, std::set<std::string> &banSet, int nbest)
{
    std::vector<std::pair<fasttext::real, std::string>> to_return;
    assert(_wordVectors);
//     to_return= _embmodel.findNN(*_wordVectors, wordVector, nbest, banSet);
    _embmodel.findNN(*_wordVectors, wordVector, nbest, banSet, to_return);
    return to_return;
}

vector< pair< fasttext::real, string > > Embeddings::querySentence(string& sentence)
{
    std::istringstream issSentence(sentence);
    fasttext::Vector wordVector(_embmodel.getDimension());
    std::set<std::string> banSet;
    banSet.clear();
    char c = ' ';
    string token="";
    int l_inc;
    for (l_inc=0; l_inc < (int) sentence.size(); l_inc++)
    {
        if (sentence[l_inc] == c)
        {
            if ((int)token.size() > 0)
            {
                banSet.insert(token);
                token.clear();
            }
        }
        else
        {
            token.push_back(sentence[l_inc]);
        }
    }
    if ((int)token.size() > 0)
    {
        banSet.insert(token);
    }
    _embmodel.getSentenceVector(issSentence, wordVector);
    return querySentence(wordVector,banSet);
}

vector< pair< fasttext::real, string > > Embeddings::querySentenceNoBan(string& sentence)
{
    std::istringstream issSentence(sentence);
    fasttext::Vector wordVector(_embmodel.getDimension());
    std::set<std::string> banSet;
    banSet.clear();

    _embmodel.getSentenceVector(issSentence, wordVector);
    return querySentence(wordVector,banSet);
}
vector< pair< fasttext::real, string > > Embeddings::querySentence(vector< string >& sentence)
{
    std::stringstream ssSentence("");
    int l_inc = 0;
    std::set<std::string> banSet;
    banSet.clear();
    for (l_inc = 0 ; l_inc < (int) sentence.size(); l_inc ++)
    {
        ssSentence << sentence[l_inc] << " ";
        banSet.insert(sentence[l_inc]);
    }
    fasttext::Vector wordVector(_embmodel.getDimension());
    _embmodel.getSentenceVector(ssSentence, wordVector);
    return querySentence(wordVector,banSet);
}
vector< pair< fasttext::real, string > > Embeddings::querySentenceNoBan(vector< string >& sentence)
{
    std::stringstream ssSentence("");
    int l_inc = 0;
    std::set<std::string> banSet;
    banSet.clear();
    for (l_inc = 0 ; l_inc < (int) sentence.size(); l_inc ++)
    {
        ssSentence << sentence[l_inc] << " ";
//         banSet.insert(sentence[l_inc]);
    }
    fasttext::Vector wordVector(_embmodel.getDimension());
    _embmodel.getSentenceVector(ssSentence, wordVector);
    return querySentence(wordVector,banSet);
}

vector< pair< fasttext::real, string > > Embeddings::querySentenceEvolved(string& sentence, bool& useWeights)
{
    char c=' ';
    int l_inc;
    vector<string> sentenceVector;
    sentenceVector.clear();
    string token;
    token.clear();
    for (l_inc=0; l_inc < (int) sentence.size(); l_inc++)
    {
        if (sentence[l_inc] == c)
        {
            if ((int)token.size() > 0)
            {
//                 cerr << token << "|"<<sentence[l_inc]<< endl;
                sentenceVector.push_back(token);
                token.clear();
            }
        }
        else
        {
            token.push_back(sentence[l_inc]);
        }
    }
    if ((int)token.size() > 0)
    {
        sentenceVector.push_back(token);
    }
//     vector<string> sentenceVector=str2vec(sentence,c);
    return querySentenceEvolved(sentenceVector,useWeights);
}

vector< pair< fasttext::real, string > > Embeddings::querySentenceEvolved(vector< string >& sentence, bool &useWeights)
{
    std::stringstream ssSentence("");
    int l_inc = 0;
    std::set<std::string> banSet;
//     fasttext::Vector wordVector(_embmodel.getDimension());
    fasttext::Vector sentenceVector(_embmodel.getDimension());
    fasttext::Vector wordVector(_embmodel.getDimension());
    vector< pair< fasttext::real, string > > results_words;
    fasttext::Vector sentenceVectorSum(_embmodel.getDimension());
    sentenceVectorSum.zero();
    
    banSet.clear();
    int l_inc_results=0;
    int nbest = 1;
    for (l_inc = 0 ; l_inc < (int) sentence.size(); l_inc ++)
    {
        ssSentence << sentence[l_inc] << " ";
        
        results_words = queryWords(sentence[l_inc]);
//         cerr << sentence[l_inc] << " | " << endl;
        for (l_inc_results = 0 ; l_inc_results < (int)results_words.size() && l_inc_results < nbest ; l_inc_results ++)
        {
            _embmodel.getWordVector(wordVector, results_words.at(l_inc_results).second);
            
//             cerr << "\t" << results_words.at(l_inc_results).second << results_words.at(l_inc_results).first << endl;
            if (useWeights)
            {
                sentenceVectorSum.addVector(wordVector,results_words.at(l_inc_results).first);
            }
            else
            {
                sentenceVectorSum.addVector(wordVector);
            }
        }
    }
    _embmodel.getSentenceVector(ssSentence, sentenceVector);
    sentenceVectorSum.addVector(sentenceVector);
//     sentenceVectorSum.mul(1.0/(1.0+(nbest*(float)sentence.size())));
    return querySentence(sentenceVectorSum,banSet);
}

vector< pair< fasttext::real, string > > Embeddings::querySentence(fasttext::Vector& sentenceVector, std::set<std::string> &banSet, int nbest)
{
    std::vector<std::pair<fasttext::real, std::string>> to_return;
    assert(_wordVectors);
//     to_return= 
    _embmodel.findNN(*_wordVectors, sentenceVector, nbest, banSet, to_return);
//     _embmodel.findNN((*_wordVectors), sentenceVector, nbest, banSet, to_return);
    return to_return;
}

string Embeddings::printResults(vector< pair< fasttext::real, string > > results, int nbest)
{
    stringstream ss;
    ss.str("");
    int l_cpt=0;
    for (auto& pair : results) {
      if (l_cpt >= nbest) break;
      ss << pair.second << " " << pair.first << std::endl;
      l_cpt++;
    }
    return ss.str();
}


string Embeddings::printVector(fasttext::Vector vec)
{
    stringstream ss;
    ss.str("");
    int l_inc;
    for (l_inc =0; l_inc< (int)vec.size()-1 ; l_inc++) 
    {
      ss << vec[l_inc] << " ";
    }
    ss << vec[(int)vec.size()-1];
    return ss.str();
}

string Embeddings::printVector(vector< float > vec)
{
    stringstream ss;
    ss.str("");
    int l_inc;
    for (l_inc =0; l_inc< (int)vec.size()-1 ; l_inc++) 
    {
      ss << vec[l_inc] << " ";
    }
    ss << vec[(int)vec.size()-1];
    return ss.str();
}


std::vector < std::pair < fasttext::real,std::string > > Embeddings::classifySentence(std::vector< string > &sentence, fasttext::real threshold, int nbest) 
{
    std::vector < std::pair < fasttext::real,std::string > > to_return;
    int l_inc = 0;
    std::stringstream ssSentence("");
    for (l_inc = 0 ; l_inc < (int) sentence.size(); l_inc ++)
    {
        ssSentence << sentence[l_inc] << " ";
    }
    _embmodel.predictLine(ssSentence, to_return, nbest, threshold);
    return to_return;
}

std::vector < std::pair < fasttext::real,std::string > > Embeddings::classifySentence(string &sentence, fasttext::real threshold, int nbest) 
{
    std::vector < std::pair < fasttext::real,std::string > > to_return;
    int l_inc = 0;
    std::stringstream ssSentence(sentence);
    _embmodel.predictLine(ssSentence, to_return, nbest, threshold);
    return to_return;
}

int Embeddings::getVecDimension() const
{
    return _embmodel.getDimension();
}

vector<float> Embeddings::getWordVector(string& word)
{
    vector<float> wordVectorToReturn(_embmodel.getDimension());
    fasttext::Vector wordVector(_embmodel.getDimension());
    _embmodel.getWordVector(wordVector, word);
    int  l_inc =0;
    for (l_inc =0 ; l_inc < (int)wordVector.size() ; l_inc++)
    {
        wordVectorToReturn[l_inc] = wordVector[l_inc];
    }
//     wordVector=wordVectorToReturn;
    return wordVectorToReturn;
}

vector< float > Embeddings::getSentenceVector(string& sentence)
{
    vector<float> wordVectorToReturn(_embmodel.getDimension());
    fasttext::Vector sentenceVector(_embmodel.getDimension());
    std::istringstream issSentence(sentence);
    _embmodel.getSentenceVector(issSentence, sentenceVector);
    int  l_inc =0;
    for (l_inc =0 ; l_inc < (int)sentenceVector.size() ; l_inc++)
    {
        wordVectorToReturn[l_inc] = sentenceVector[l_inc];
    }
//     wordVector=wordVectorToReturn;
    return wordVectorToReturn;
}


float Embeddings::getCosineSimilarity(fasttext::Vector vec1, fasttext::Vector vec2)
{
    if (vec1.size() != vec2.size())
    {
        return 0.0;
    }
    else
    {
        int l_inc=0; 
        float dot=0.0;
        float denom_1=0.0;
        float denom_2=0.0;
        for(l_inc = 0; l_inc < (int)vec1.size(); l_inc++) 
        {
            dot += vec1[l_inc] * vec2[l_inc] ;
            denom_1 += vec1[l_inc] * vec1[l_inc] ;
            denom_2 += vec2[l_inc] * vec2[l_inc] ;
        }
        return dot / (sqrt(denom_1) * sqrt(denom_2)) ;
    }
    return 0.0;
}       

float Embeddings::getCosineSimilarity(string& s1, string& s2)
{
    fasttext::Vector vec1(_embmodel.getDimension());
    fasttext::Vector vec2(_embmodel.getDimension());
    getWordVector(s1,vec1);
    getWordVector(s2,vec2);
//     return getCosineSimilarity(vec1,vec2);
    return 0.0;
}
