#ifndef GENERALIZATION_H
#define GENERALIZATION_H

#include "utils.h"
#include <unordered_map>


using namespace std;

namespace qnlp {

class Generalization {
    public:
      Generalization();
      bool checknumbers(string& token);
      bool checkhours(string& token);
      vector<string> filter_numbers(vector< string >& sentence);
      vector<string> filter_hours(vector< string >& sentence);
//     private:

};
}

#endif // GENERALIZATION_H
