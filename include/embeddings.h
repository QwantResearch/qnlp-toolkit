#ifndef EMBEDDINGS_H
#define EMBEDDINGS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "fasttext/fasttext.h"
// #include "tokenizer.h"

using namespace std;
namespace qnlp {
class Embeddings {
    public:
        Embeddings (void);
        Embeddings (string &filename);
        void getWordVector(string &word, fasttext::Vector &wordVector);
        vector<float> getWordVector(string &word);
        void getSentenceVector(string &sentence, fasttext::Vector &sentenceVector);
        vector<float> getSentenceVector(string &sentence);
        std::vector <std::pair <fasttext::real, std::string > > queryWords(string &word, int nbest=10);
        std::vector <std::pair <fasttext::real, std::string > > querySentence(string &sentence);
        std::vector <std::pair <fasttext::real, std::string > > querySentenceNoBan(string &sentence);
        std::vector <std::pair <fasttext::real, std::string > > querySentence(vector< string > &sentence);
        std::vector <std::pair <fasttext::real, std::string > > querySentenceNoBan(vector< string > &sentence);
        std::vector <std::pair <fasttext::real, std::string > > querySentenceEvolved(string &sentence, bool &useWeights);
        std::vector <std::pair <fasttext::real, std::string > > querySentenceEvolved(vector< string > &sentence, bool &useWeights);
        std::vector <std::pair <fasttext::real, std::string > > queryWords(fasttext::Vector &wordVector, set<string> &banSet, int nbest=10);
        std::vector <std::pair <fasttext::real, std::string > > querySentence(fasttext::Vector &sentenceVector, set<string> &banSet, int nbest=10);
        std::vector <std::pair <fasttext::real, std::string > > classifySentence(std::vector< string > &sentence, fasttext::real threshold, int nbest=10);
        std::vector <std::pair <fasttext::real, std::string > > classifySentence(string &sentence, fasttext::real threshold, int nbest = 10);
        string printResults(std::vector <std::pair <fasttext::real, std::string > > results, int nbest=10);
        string printVector(fasttext::Vector vec);
        string printVector(vector<float> vec);
        int getVecDimension() const;
        float getCosineSimilarity(string &s1, string &s2);
        float getCosineSimilarity(fasttext::Vector vec1, fasttext::Vector vec2);
    private:
        fasttext::FastText _embmodel;
         std::unique_ptr<fasttext::DenseMatrix>  _wordVectors;
        std::shared_ptr<const fasttext::Dictionary> _dict;
};

}
#endif // EMBEDDINGS_H
