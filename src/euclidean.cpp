

#include "euclidean.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>


// split a string on tabs
vector<string> splittab(const string& s)
{
   vector<string> tokens;
   string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, '\t')){
      tokens.push_back(token);
   }
   return tokens;
}

// split a string on whitespace
vector<string> splitspace(const string& s)
{
   vector<string> tokens;
   string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, ' ')){
      tokens.push_back(token);
   }
   return tokens;
}

// split a string on tabs
vector<string> splitsemicolon(const string& s)
{
   vector<string> tokens;
   string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, ';')){
      tokens.push_back(token);
   }
   return tokens;
}



// trim from start (in place)
static inline void ltrim(string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(string &s) {
    ltrim(s);
    rtrim(s);
}


EmbeddedVector::EmbeddedVector(vector<string> vals){
  if (vals.size()<2) {
    std::cerr << "[FATAL] Malformed input vector\n";
    std::exit(EXIT_FAILURE);
  }
  // the first field is the name
  name_ = vals.at(0);
  for (unsigned i=1;i<vals.size();++i) {
    double v = std::stod(vals.at(i));
    values_.push_back(v);
  }
}

 void
 Cluster::add_vector(const vector<string> &invec){
   



 }




/**
 * Ths assumption is that the name of the node will start
 * with a letter (g,d,p) which indicates the category of the node, 
 * and that the remainder of the name is an integer.
 * This script will parse in the data and produce a map of Clusters,
 * with one Cluster for each initial letter.
 * @param path Path to the hn2v output file.
 */
Parser::Parser(const string & path){
  std::cout << "[INFO] Parsing " << path << "\n";
  std::ifstream infile(path);
    if (! infile.good()) {
      std::cerr <<"[ERROR] Could not open input file at "
        << path << "\n";
      std::exit(1);
    }
    std::string line;
    while (std::getline(infile,line)) {
      //std::cout << line << "\n";
      char category = line.at(0);
      vector<string> v = splitspace(line);
      std::map<char,Cluster>::iterator it;
      it = clustermap_.find(category);
      if (it == clustermap_.end()) {
	clustermap_.emplace(category,Cluster{});
      }
      Cluster cluster = clustermap_[category];
      cluster.add_vector(v);
      
    }



}
