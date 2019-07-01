

#include "euclidean.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cmath>


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

EmbeddedVector::EmbeddedVector(const EmbeddedVector &evec):
  name_(evec.name_)
{
  values_ = evec.values_;
}

EmbeddedVector::EmbeddedVector(EmbeddedVector &&evec):
  name_(evec.name_)
{
  values_ = std::move(evec.values_);
}

EmbeddedVector
EmbeddedVector::toCentroid(vector<EmbeddedVector> vecs){

  int N = vecs.size();
  EmbeddedVector firstvec = vecs.at(0);
  vector<double> sum = firstvec.get_values();
  for(int i=1;i<vecs.size(); i++) {
    vector<double> next = vecs.at(i).get_values();
    for (int j=0;j<next.size();j++) {
      sum[j] = sum[j] + next[j];
    }
  }
  for (int j=0;j<sum.size();j++) {
    sum[j] /= static_cast<double>(N);
  }
  EmbeddedVector cent{"centroid",sum};
  return cent;
}

double
EmbeddedVector::distance(const EmbeddedVector &ev) const {
  double sum_of_squares = 0.0d;
  for (int i=0;i<values_.size(); i++) {
    double diff = values_.at(i) - ev.values_.at(i);
    sum_of_squares += diff * diff;
  }
  return sqrt(sum_of_squares);
}

void
Cluster::add_vector(EmbeddedVector &embvec){
   string name = embvec.get_name();
   string num = name.substr(1);// discard the first char, it is the category
   int n = std::stoi(num);
   embedded_vector_map_.insert(std::make_pair(n,std::move(embvec)));
 }

bool
Cluster::contains_gene(int g) const {
  const auto &p = embedded_vector_map_.find(g);
  return p != embedded_vector_map_.end();
}

int
Cluster::rank(int gene_id,vector<int> others) const {
  vector<EmbeddedVector> other_vectors;
  for (int o : others) {
    if (! contains_gene(o)) {
      //std::cerr << "[WARNING] could not find gene with id: " << o << "\n";
      continue;
    }
    const auto &p = embedded_vector_map_.find(o);
    other_vectors.push_back(p->second);
  }
  if (other_vectors.size() <2) {
    std::cerr << "[WARNING] size of other vectors: " << other_vectors.size() << "\n";
    return -1;
  }
  EmbeddedVector centroid = EmbeddedVector::toCentroid(other_vectors);
    const auto &p = embedded_vector_map_.find(gene_id);
    if (p == embedded_vector_map_.end()) {
      std::cerr << "[WARNING] could not find target: " << gene_id << "\n";
      return -1;
    }
  EmbeddedVector target = p->second;
  double target_distance = target.distance(centroid);
  int rank=1;
  for (auto p :   embedded_vector_map_) {
    int other_gene_id = p.first;
    EmbeddedVector other_ev = p.second;
    double other_distance = other_ev.distance(centroid);
    if (other_distance < target_distance) {
      rank++;
    }
  }
  return rank;
}

std::ostream& operator<<(std::ostream& ost, const Cluster& c){
  ost << "Cluster: " << c.name_ << " [n=" << c.vector_count() << "]";
  return ost;
}



/**
 * Ths assumption is that the name of the node will start
 * with a letter (g,d,p) which indicates the category of the node,
 * and that the remainder of the name is an integer.
 * This script will parse in the data and produce a map of Clusters,
 * with one Cluster for each initial letter.
 * @param path Path to the hn2v output file.
 */
Parser::Parser(const string & path): path_(path) {
  std::cout << "[INFO] Parsing " << path << "\n";
  std::ifstream infile(path);
    if (! infile.good()) {
      std::cerr <<"[ERROR] Could not open input file at "
        << path << "\n";
      std::exit(1);
    }
    std::string line;
    std::getline(infile,line); // discard first line
    while (std::getline(infile,line)) {
      //std::cout << line << "\n";
      char category = line.at(0);
      vector<string> v = splitspace(line);
      EmbeddedVector emvec{v};
      std::map<char,Cluster>::iterator it;
      it = clustermap_.find(category);
      if (it == clustermap_.end()) {
	Cluster cluster{};
	cluster.add_vector(emvec);
	clustermap_.emplace(category,cluster);
      } else {
	it->second.add_vector(emvec);
      }

    }
}

void
Parser::status(){
  std::cout << "exbed: " << path_ << "\n";
  for (const auto & p : clustermap_) {
    std::cout << p.first << ": " << p.second << "\n";
  }

}
