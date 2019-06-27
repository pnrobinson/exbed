#ifndef EUCLIDEAN_H
#define EUCLIDEAN_H

#include <vector>
#include <map>
#include <string>


using std::string;
using std::map;
using std::vector;



class EmbeddedVector {
 private:
  string name_;
  vector<double> values_;

 public:
  EmbeddedVector(vector<string> vals);
  EmbeddedVector(const EmbeddedVector &evec);
  EmbeddedVector(EmbeddedVector &&evec);
  ~EmbeddedVector(){}

  string get_name() const { return name_; }
  vector<double> get_values() const { return values_; }


  

};






/**
 * A cluster of numerical vectors 
 */
class Cluster {
 private:
  map<int,EmbeddedVector> embedded_vector_map_;
  string name_;

 public:
  void add_vector(EmbeddedVector &embvec);
  int vector_count() const { return embedded_vector_map_.size(); }


  friend std::ostream& operator<<(std::ostream& ost, const Cluster& c);
};

std::ostream& operator<<(std::ostream& ost, const Cluster& c);



class Parser {
 private:
  string path_;
  map<char,Cluster> clustermap_;


 public:
  Parser(const string & path);


  void status();

};









#endif
