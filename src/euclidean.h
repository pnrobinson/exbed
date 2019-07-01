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
  static EmbeddedVector toCentroid(vector<EmbeddedVector> vecs);
  EmbeddedVector(const EmbeddedVector &evec);
  EmbeddedVector(EmbeddedVector &&evec);
  EmbeddedVector(const string &name,const vector<double> vals):name_(name),values_(vals){}
  ~EmbeddedVector(){}

  string get_name() const { return name_; }
  vector<double> get_values() const { return values_; }
  int n_values() const { return values_.size(); }
  double distance(const EmbeddedVector &ev) const;




};






/**
 * A cluster of numerical vectors
 */
class Cluster {
 private:
  map<int,EmbeddedVector> embedded_vector_map_;
  string name_;

 public:
   Cluster(){}
   ~Cluster(){}
   Cluster(const Cluster &c) = default;
   Cluster(Cluster &&c)= default;
  Cluster &operator=(const Cluster &c) = default;
  Cluster &operator=(Cluster &&c)= default;
  void add_vector(EmbeddedVector &embvec);
  int vector_count() const { return embedded_vector_map_.size(); }

  int rank(int gene_id,vector<int> others) const;

  bool contains_gene(int g) const;


  friend std::ostream& operator<<(std::ostream& ost, const Cluster& c);
};

std::ostream& operator<<(std::ostream& ost, const Cluster& c);



class Parser {
 private:
  string path_;
  map<char,Cluster> clustermap_;


 public:
  Parser(const string & path);
  const Cluster get_cluster(char c) const { return clustermap_.find(c)->second; }


  void status();

};









#endif
