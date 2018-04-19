#include "bpe.h"

#include <mutex>
#include <sstream>
#include <iostream>

#include "utf8/utf8.h"
#include "utils.h"

using namespace std;

std::vector<std::vector<std::string>> BPE::Preprocess(const std::vector<std::string> input) {
  return Encode(input);
}

std::vector<std::string> BPE::Postprocess(const std::vector<std::string> input) {
  std::vector<std::string> debped;
  std::stringstream currWord;
  for (const auto& word : input) {
    if (EndsWith(word, sep_)) {
      currWord << word.substr(0, word.size() - sep_.size());
    } else {
      currWord << word;
      debped.push_back(currWord.str());
      currWord.str("");
      currWord.clear();
    }
  }
  return debped;
}

BPE::BPE()
  : sep_("@@") {}

BPE::BPE(std::ifstream&& file,  const std::string sep)
  : sep_(sep) {
  std::string inputLine;
  size_t index = 0;
  while (std::getline(file, inputLine)) {
    std::vector<std::string> code;
    Split(inputLine, code);
    bpeCodes_[make_pair(code[0], code[1])] = index++;
  }
}

BPE::BPE(const std::string& path, const std::string sep)
  : BPE(std::ifstream(path), sep) {}

std::vector<std::string> BPE::Segment(const std::string& sentence) {
  std::vector<std::string> words, tokens;
  Split(sentence, words);

  for (auto& word : words) {
    if (word.empty()) continue;
    auto codes = Encode(word);
    for (size_t i = 0; i < codes.size() - 1; ++i) {
      tokens.emplace_back(codes[i]);
    }
    tokens.push_back(codes.back());
  }
  return tokens;
}

void BPE::PrintSegment(const std::string& sentence) {
  std::vector<std::string> words, tokens;
  Split(sentence, words);

  for (size_t wi = 0; wi < words.size(); ++wi) {
    if (words[wi].empty()) continue;
    auto codes = Encode(words[wi]);

    for (size_t i = 0; i < codes.size() - 1; ++i) {
      std::cout << codes[i] << " ";
    }
    std::cout << codes.back();
    if (wi == words.size() - 1) {
      std::cout << std::endl;
    } else {
      std::cout << " ";
    }
  }
}

std::set<BPE::BPEPair> BPE::GetPairs(const std::vector<std::string>& word) {
  std::set<BPE::BPEPair> pairSet;
  for (size_t i = 1; i < word.size(); ++i) {
    pairSet.emplace(word[i-1], word[i]);
  }
  return pairSet;
}

const BPE::BPEPair* BPE::FindBestBigram(const std::set<BPEPair>& pairs) {
  size_t minDist = bpeCodes_.size();
  auto best = bpeCodes_.begin();

  for (const auto& pair : pairs) {
    auto it = bpeCodes_.find(pair);
    if (it == bpeCodes_.end()) {
      continue;
    }
    if (it->second < minDist) {
      minDist = it->second;
      best = it;
    }
  }
  if (minDist == bpeCodes_.size()) {
    return nullptr;
  }
  else {
  return &(best->first);
  }
}

std::vector<std::string>& BPE::Encode(const std::string& word) {
  if (IsCached(word)) {
    return cache_[word];
  }

  std::vector<std::string> vWord = SplitWordIntoLetters(word);
  vWord.push_back("</w>");

  auto pairs = GetPairs(vWord);

  while (true) {
    const BPEPair* bigram = FindBestBigram(pairs);
    if (bigram == nullptr) {
      break;
    }

    std::vector<std::string> newWord;

    auto it = vWord.begin();
    while (it != vWord.end()) {
      auto jt = std::find(it, vWord.end(), bigram->first);
      for (auto i = it; i != jt; ++i) {
        newWord.push_back(*i);
      }

      if (jt == vWord.end()) {
        break;
      }
      it = jt;

      if (*it == bigram->first && (it+1) != vWord.end() && *(it+1) == bigram->second) {
        newWord.emplace_back(bigram->first + bigram->second);
        it += 2;
      } else {
        newWord.push_back(*it);
        it += 1;
      }
    }
    std::swap(vWord, newWord);
    if (newWord.size() == 1) {
      break;
    } else {
      pairs = GetPairs(vWord);
    }
  }

  if (vWord.back() == "</w>") {
    vWord.pop_back();
  }

  if (EndsWith(vWord.back(), "</w>")) {
    vWord.back().resize(vWord.back().size() - 4);
  }

  for (size_t i = 0;  i < vWord.size() - 1; ++i) {
    vWord[i] = vWord[i] + sep_;
  }

  std::mutex mtx;
  mtx.lock();
  cache_[word] = vWord;
  mtx.unlock();

  return cache_[word];
}

std::vector<std::vector<std::string>> BPE::Encode(const std::vector<std::string>& words) {
  std::vector<std::vector<std::string>> result;
  for (const auto& word : words) {
    auto& encoded = Encode(word);
    //result.insert(result.end(), encoded.begin(), encoded.end());
    result.push_back(encoded);
  }
  // std::cerr << "BPE: ";
  // for (auto& code: result) std::cerr << code << " " ;
  // std::cerr << std::endl;
  return result;
}


bool BPE::IsCached(const std::string& word) const {
  return cache_.find(word) != cache_.end();
}

std::vector<std::string> BPE::SplitWordIntoLetters(const std::string& word) const {
  char* charWord = (char*)word.c_str();
  auto b = charWord;
  auto e = charWord + strlen(charWord);

  std::vector<std::string> letters;
  int prevBegin = 0;
  while (b != e) {
    int end = utf8::next(b, e);
    std::vector<unsigned char> utf8result;
    utf8::utf32to8(&end,&end + 1, std::back_inserter(utf8result));
    letters.emplace_back(utf8result.begin(), utf8result.end());
  }
  return letters;
}

bool BPE::EndsWith(std::string const &fullString, std::string const suffix) const {
  if (fullString.length() >= suffix.length()) {
    return (0 == fullString.compare(fullString.length() - suffix.length(), suffix.length(), suffix));
  } else {
    return false;
  }
}


string BPE::apply_bpe(string &input)
{
//     cerr << input << endl;
    stringstream l_out;
    l_out.str("");
    vector<string> vec0;
    string l_tmp="";
    l_tmp.clear();
    for (int l_inc=0; l_inc < (int)input.size(); l_inc++)
    {
        if (input[l_inc] != ' ')
        {
            l_tmp.push_back(input[l_inc]);
        }
        else
        {
            if (!l_tmp.empty())
            {
                vec0.push_back(l_tmp);
                l_tmp.clear();
            }
        }
    }
    vector<vector<string>> vec=Preprocess(vec0);
    for (int i=0; i < (int)vec.size(); i++)
    {
        for(int j=0; j < (int)vec.at(i).size(); j++)
        {
              if (i == (int)vec.size()-1  && j == (int)vec.at(i).size()-1) l_out << vec.at(i).at(j);
              else l_out << vec.at(i).at(j)  << " ";
        }
    }
    return l_out.str();
}

vector<string> BPE::apply_bpe(vector<string> &input)
{
//     cerr << input << endl;
    vector<string> output;
    stringstream l_out;
    l_out.str("");
    vector<vector<string>> vec=Preprocess(input);
    for (int i=0; i < (int)vec.size(); i++)
    {
        for(int j=0; j < (int)vec.at(i).size(); j++)
        {
            output.push_back(vec.at(i).at(j));
        }
    }
    return output;
}

string BPE::apply_bpe_to_string(vector<string> &input)
{
    vector<string> output=apply_bpe(input);
    stringstream l_out;
    l_out.str("");
    for (int i=0; i < (int)output.size(); i++)
    {
        l_out << output[i];
    }
    return l_out.str();
}

